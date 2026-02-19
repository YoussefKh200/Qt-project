#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
#include <QIcon>
#include <QSize>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QPageSize>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Initialize database connection
    Connection conn;
    if (conn.createconnect()) {
        qDebug() << "Database connection successful!";
    } else {
        QMessageBox::critical(this, "Database Error", 
                            "Failed to connect to the database.\nPlease check your connection settings.");
        qDebug() << "Database connection failed!";
    }
    
    QPixmap pixModify(":/img/modify.png");
    ui->user_modify->setPixmap(pixModify);
    QPixmap pixDelete(":/img/delete.png");
    ui->user_delete->setPixmap(pixDelete);

    // Page par défaut au lancement
    ui->stackedWidget->setCurrentWidget(ui->pageUser);
    
    // Clear the default sample data from table
    ui->tableWidget_3->setRowCount(0);
    
    setupConnections();
    updateButtonStates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // Navigation buttons
    connect(ui->btnUser, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageUser);
    });

    connect(ui->btnClient, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageClient);
    });

    connect(ui->btnCommande, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageCommande);
    });

    connect(ui->btnFournisseur, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageFournisseur);
    });

    connect(ui->btnMateriaux, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMateriaux);
    });

    // Form buttons
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::onValidateUserClicked);

    // Export PDF button
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::exportToPDF);

    // Search functionality
    connect(ui->lineEditSearch__2, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    ui->lineEditSearch__2->setPlaceholderText("🔍 Rechercher par nom, prénom, tél ou mail...");
    ui->lineEditSearch__2->clear();  // Clear the default text

    // Image buttons (Labels acting as buttons)
    ui->user_modify->setCursor(Qt::PointingHandCursor);
    ui->user_delete->setCursor(Qt::PointingHandCursor);

    // Table selection
    connect(ui->tableWidget_3, &QTableWidget::cellClicked, this, &MainWindow::onTableRowSelected);
    connect(ui->tableWidget_3, &QTableWidget::itemSelectionChanged, this, &MainWindow::updateButtonStates);
}

void MainWindow::clearForm()
{
    ui->lineEdit_7->clear();  // nom
    ui->lineEdit_8->clear();  // prenom
    ui->lineEdit_9->clear();  // tel
    ui->lineEdit_10->clear(); // mail
    ui->lineEdit_11->clear(); // mdp
    ui->lineEdit_13->clear(); // salaire
    ui->comboBox->setCurrentIndex(0);  // role
    ui->checkBox->setChecked(true);    // etat (actif by default)
    ui->checkBox_2->setChecked(false);
    
    currentEditingRow = -1;
}

void MainWindow::addUserToTable(const User &user)
{
    int row = ui->tableWidget_3->rowCount();
    ui->tableWidget_3->insertRow(row);

    // Add user data to each column
    ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(user.nom));
    ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(user.prenom));
    ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(user.tel));
    ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(user.mail));
    ui->tableWidget_3->setItem(row, 4, new QTableWidgetItem(user.mdp));
    ui->tableWidget_3->setItem(row, 5, new QTableWidgetItem(user.salaire));
    ui->tableWidget_3->setItem(row, 6, new QTableWidgetItem(user.role));
    ui->tableWidget_3->setItem(row, 7, new QTableWidgetItem(user.etat));

    // Create action buttons widget for column 8
    QWidget *actionWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(actionWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);

    // Create modify button with image
    QPushButton *btnModify = new QPushButton();
    btnModify->setIcon(QIcon(":/img/modify.png"));
    btnModify->setToolTip("Modifier");
    btnModify->setIconSize(QSize(16, 16));
    btnModify->setMaximumWidth(24);
    btnModify->setCursor(Qt::PointingHandCursor);

    // Create delete button with image
    QPushButton *btnDelete = new QPushButton();
    btnDelete->setIcon(QIcon(":/img/delete.png"));
    btnDelete->setToolTip("Supprimer");
    btnDelete->setIconSize(QSize(16, 16));
    btnDelete->setMaximumWidth(24);
    btnDelete->setCursor(Qt::PointingHandCursor);

    layout->addWidget(btnModify);
    layout->addWidget(btnDelete);

    // Set the action widget in column 8
    ui->tableWidget_3->setCellWidget(row, 8, actionWidget);

    // Connect buttons to slots using lambda to capture the current row
    connect(btnModify, &QPushButton::clicked, this, [this, row]() {
        if (row >= 0 && row < ui->tableWidget_3->rowCount()) {
            loadUserToForm(row);
            qDebug() << "Modify row:" << row;
        }
    });

    connect(btnDelete, &QPushButton::clicked, this, [this, row]() {
        if (row >= 0 && row < ui->tableWidget_3->rowCount()) {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                "Êtes-vous sûr de vouloir supprimer cet utilisateur?",
                QMessageBox::Yes | QMessageBox::No);
            
            if (reply == QMessageBox::Yes) {
                ui->tableWidget_3->removeRow(row);
                clearForm();
                updateButtonStates();
                QMessageBox::information(this, "Succès", "Utilisateur supprimé avec succès!");
                qDebug() << "Deleted row:" << row;
            }
        }
    });

    updateButtonStates();
    clearForm();
}

void MainWindow::loadUserToForm(int row)
{
    if (row < 0 || row >= ui->tableWidget_3->rowCount()) return;

    ui->lineEdit_7->setText(ui->tableWidget_3->item(row, 0)->text());  // nom
    ui->lineEdit_8->setText(ui->tableWidget_3->item(row, 1)->text());  // prenom
    ui->lineEdit_9->setText(ui->tableWidget_3->item(row, 2)->text());  // tel
    ui->lineEdit_10->setText(ui->tableWidget_3->item(row, 3)->text()); // mail
    ui->lineEdit_11->setText(ui->tableWidget_3->item(row, 4)->text()); // mdp
    ui->lineEdit_13->setText(ui->tableWidget_3->item(row, 5)->text()); // salaire
    
    QString role = ui->tableWidget_3->item(row, 6)->text();
    ui->comboBox->setCurrentText(role);
    
    QString etat = ui->tableWidget_3->item(row, 7)->text();
    if (etat == "actif") {
        ui->checkBox->setChecked(true);
        ui->checkBox_2->setChecked(false);
    } else {
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setChecked(true);
    }
    
    currentEditingRow = row;
}

void MainWindow::updateButtonStates()
{
    // Enable/disable modify and delete buttons based on selection
    bool hasSelection = ui->tableWidget_3->currentRow() >= 0;
    ui->user_modify->setEnabled(hasSelection);
    ui->user_delete->setEnabled(hasSelection);
    
    // Update opacity for visual feedback
    ui->user_modify->setStyleSheet(hasSelection ? "" : "opacity: 0.5;");
    ui->user_delete->setStyleSheet(hasSelection ? "" : "opacity: 0.5;");
}

void MainWindow::onValidateUserClicked()
{
    // Validate form fields
    if (ui->lineEdit_7->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le nom");
        return;
    }

    if (ui->lineEdit_8->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le prénom");
        return;
    }

    if (ui->lineEdit_9->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le téléphone");
        return;
    }

    // Validate TEL: must be exactly 8 digits
    QString tel = ui->lineEdit_9->text();
    if (tel.length() != 8) {
        QMessageBox::warning(this, "Erreur", "Le téléphone doit contenir exactement 8 chiffres");
        return;
    }
    
    bool telOk;
    tel.toLongLong(&telOk);
    if (!telOk) {
        QMessageBox::warning(this, "Erreur", "Le téléphone doit contenir uniquement des chiffres");
        return;
    }

    if (ui->lineEdit_10->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le mail");
        return;
    }

    // Validate MAIL: must contain @ and valid domain
    QString mail = ui->lineEdit_10->text();
    if (!mail.contains("@") || !mail.contains(".")) {
        QMessageBox::warning(this, "Erreur", "Le mail doit être au format valide (ex: exemple@gmail.com)");
        return;
    }
    
    int atIndex = mail.indexOf("@");
    int dotIndex = mail.lastIndexOf(".");
    if (atIndex <= 0 || dotIndex <= atIndex + 1 || dotIndex == mail.length() - 1) {
        QMessageBox::warning(this, "Erreur", "Le mail doit être au format valide (ex: exemple@gmail.com)");
        return;
    }

    if (ui->lineEdit_11->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le mot de passe");
        return;
    }

    if (ui->lineEdit_13->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le salaire");
        return;
    }

    // Validate SALAIRE: must be a valid number (int or float)
    QString salaire = ui->lineEdit_13->text();
    bool ok;
    salaire.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Le salaire doit être un nombre valide (ex: 1500 ou 1500.50)");
        return;
    }

    // Validate ROLE: must be selected
    if (ui->comboBox->currentIndex() < 0 || ui->comboBox->currentText().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un rôle");
        return;
    }

    // Validate ETAT: at least one checkbox must be checked
    if (!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un état (actif ou non actif)");
        return;
    }

    User user;
    user.nom = ui->lineEdit_7->text();
    user.prenom = ui->lineEdit_8->text();
    user.tel = ui->lineEdit_9->text();
    user.mail = ui->lineEdit_10->text();
    user.mdp = ui->lineEdit_11->text();
    user.salaire = ui->lineEdit_13->text();
    user.role = ui->comboBox->currentText();
    user.etat = ui->checkBox->isChecked() ? "actif" : "non actif";

    if (currentEditingRow >= 0) {
        // Update existing user
        ui->tableWidget_3->item(currentEditingRow, 0)->setText(user.nom);
        ui->tableWidget_3->item(currentEditingRow, 1)->setText(user.prenom);
        ui->tableWidget_3->item(currentEditingRow, 2)->setText(user.tel);
        ui->tableWidget_3->item(currentEditingRow, 3)->setText(user.mail);
        ui->tableWidget_3->item(currentEditingRow, 4)->setText(user.mdp);
        ui->tableWidget_3->item(currentEditingRow, 5)->setText(user.salaire);
        ui->tableWidget_3->item(currentEditingRow, 6)->setText(user.role);
        ui->tableWidget_3->item(currentEditingRow, 7)->setText(user.etat);
        QMessageBox::information(this, "Succès", "Utilisateur modifié avec succès!");
    } else {
        // Add new user
        addUserToTable(user);
        QMessageBox::information(this, "Succès", "Utilisateur ajouté avec succès!");
    }

    clearForm();
    updateButtonStates();
}

void MainWindow::onTableRowSelected()
{
    int row = ui->tableWidget_3->currentRow();
    if (row >= 0) {
        loadUserToForm(row);
    }
    updateButtonStates();
}

void MainWindow::onModifyUserClicked()
{
    int row = ui->tableWidget_3->currentRow();
    if (row >= 0) {
        loadUserToForm(row);
        qDebug() << "Modify row:" << row;
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un utilisateur à modifier");
    }
}

void MainWindow::onDeleteUserClicked()
{
    int row = ui->tableWidget_3->currentRow();
    if (row >= 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir supprimer cet utilisateur?",
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            ui->tableWidget_3->removeRow(row);
            clearForm();
            updateButtonStates();
            QMessageBox::information(this, "Succès", "Utilisateur supprimé avec succès!");
            qDebug() << "Deleted row:" << row;
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un utilisateur à supprimer");
    }
}

void MainWindow::exportToPDF()
{
    // Check if table has any data
    if (ui->tableWidget_3->rowCount() == 0) {
        QMessageBox::warning(this, "Erreur", "Aucun utilisateur à exporter");
        return;
    }

    // Open file dialog to save PDF
    QString fileName = QFileDialog::getSaveFileName(this,
        "Exporter PDF", "",
        "PDF Files (*.pdf);;All Files (*)");

    if (fileName.isEmpty()) {
        return;  // User cancelled
    }

    // Create PDF document
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize::A4);
    
    QPainter painter;
    if (!painter.begin(&pdfWriter)) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF");
        return;
    }

    // Set up fonts
    QFont titleFont("Arial", 38, QFont::Bold);
    QFont headerFont("Arial", 24, QFont::Bold);
    QFont dataFont("Arial", 22);

    // Title
    painter.setFont(titleFont);
    painter.drawText(20, 50, "Liste des Utilisateurs");

    // Table setup
    painter.setFont(headerFont);
    int y = 240;
    int x = 20;
    
    // Calculate column widths based on page width - make table much wider
    int pageWidth = 790;  // A4 page width with minimal margins
    QVector<int> colWidths = {150, 150, 140, 140, 180, 150, 140, 140};
    
    QStringList headers = {"Nom", "Prénom", "Tél", "Mail", "MDP", "Salaire", "Rôle", "État"};
    
    // Draw header row with background and better styling
    painter.fillRect(x, y - 40, pageWidth, 80, QColor(70, 130, 180));  // Steel blue header
    painter.setPen(Qt::white);
    
    int currentX = x;
    for (int col = 0; col < 8; col++) {
        painter.drawText(currentX + 5, y - 30, colWidths[col], 40, Qt::AlignLeft | Qt::AlignVCenter, headers[col]);
        painter.drawLine(currentX + colWidths[col], y - 30, currentX + colWidths[col], y + 10);
        currentX += colWidths[col];
    }
    
    painter.setPen(Qt::black);
    painter.drawLine(x, y + 10, x + pageWidth, y + 10);  // Bottom line

    // Table data
    painter.setFont(dataFont);
    y += 20;
    int rowHeight = 52;

    for (int row = 0; row < ui->tableWidget_3->rowCount(); row++) {
        currentX = x;
        
        // Alternate row colors for better readability
        if (row % 2 == 0) {
            painter.fillRect(x, y, pageWidth, rowHeight, QColor(245, 245, 245));  // Light gray
        } else {
            painter.fillRect(x, y, pageWidth, rowHeight, QColor(255, 255, 255));  // White
        }
        
        for (int col = 0; col < 8; col++) {
            QTableWidgetItem* item = ui->tableWidget_3->item(row, col);
            QString text = item ? item->text() : "";
            
            // Truncate text if too long
            if (text.length() > 15) {
                text = text.left(12) + "...";
            }
            
            painter.drawText(currentX + 5, y, colWidths[col], rowHeight, Qt::AlignLeft | Qt::AlignVCenter, text);
            painter.drawLine(currentX + colWidths[col], y, currentX + colWidths[col], y + rowHeight);
            currentX += colWidths[col];
        }
        
        painter.drawLine(x, y + rowHeight, x + pageWidth, y + rowHeight);
        y += rowHeight;

        // Add new page if needed
        if (y > 700) {
            pdfWriter.newPage();
            y = 30;
            
            // Redraw header on new page
            painter.setFont(headerFont);
            painter.fillRect(x, y - 30, pageWidth, 40, QColor(70, 130, 180));
            painter.setPen(Qt::white);
            
            currentX = x;
            for (int col = 0; col < 8; col++) {
                painter.drawText(currentX + 5, y - 30, colWidths[col], 40, Qt::AlignLeft | Qt::AlignVCenter, headers[col]);
                painter.drawLine(currentX + colWidths[col], y - 30, currentX + colWidths[col], y + 10);
                currentX += colWidths[col];
            }
            
            painter.setPen(Qt::black);
            painter.drawLine(x, y + 10, x + pageWidth, y + 10);
            y += 20;
            painter.setFont(dataFont);
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "PDF exporté avec succès!");
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    QString searchText = text.trimmed().toLower();
    
    // If search is empty, show all rows
    if (searchText.isEmpty() || searchText.startsWith("🔍")) {
        for (int i = 0; i < ui->tableWidget_3->rowCount(); i++) {
            ui->tableWidget_3->setRowHidden(i, false);
        }
        return;
    }
    
    // Filter rows based on nom, prenom, tel, mail (columns 0, 1, 2, 3)
    for (int i = 0; i < ui->tableWidget_3->rowCount(); i++) {
        bool matches = false;
        
        // Check nom (column 0)
        QTableWidgetItem* nomItem = ui->tableWidget_3->item(i, 0);
        if (nomItem && nomItem->text().toLower().contains(searchText)) {
            matches = true;
        }
        
        // Check prenom (column 1)
        QTableWidgetItem* prenomItem = ui->tableWidget_3->item(i, 1);
        if (prenomItem && prenomItem->text().toLower().contains(searchText)) {
            matches = true;
        }
        
        // Check tel (column 2)
        QTableWidgetItem* telItem = ui->tableWidget_3->item(i, 2);
        if (telItem && telItem->text().toLower().contains(searchText)) {
            matches = true;
        }
        
        // Check mail (column 3)
        QTableWidgetItem* mailItem = ui->tableWidget_3->item(i, 3);
        if (mailItem && mailItem->text().toLower().contains(searchText)) {
            matches = true;
        }
        
        ui->tableWidget_3->setRowHidden(i, !matches);
    }
}
