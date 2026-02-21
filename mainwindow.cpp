#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>
#include <QDateEdit>
#include <QDate>
#include <QIcon>
#include <QDebug>
#include <QStackedWidget>
#include <QPainter>
#include <QPainterPath>

// Simple inner class to draw the statistics graph
class StatWidget : public QWidget {
public:
    explicit StatWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setMinimumHeight(150);
        // Ensure the widget triggers paint events
        setAttribute(Qt::WA_StyledBackground, false);
    }
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        int w = width();
        int h = height();

        // 1. Background Gradient
        QLinearGradient bgGrad(0, h, 0, 0);
        bgGrad.setColorAt(0, QColor("#F0E6DC")); // Beige bottom
        bgGrad.setColorAt(1, Qt::white);         // White top
        p.fillRect(rect(), bgGrad);

        // 2. Axes
        p.setPen(QPen(QColor("#D7C4BB"), 2));
        p.drawLine(30, h - 20, w - 10, h - 20); // X Axis
        p.drawLine(30, h - 20, 30, 10);         // Y Axis

        // 3. Data Points (Approximating the screenshot curve)
        QVector<QPointF> points;
        float xStep = (w - 60) / 4.0; // 5 points
        float yBase = h - 20;         // Y=0 line
        float hGraph = h - 40;        // Max height available
        float yMax = 300.0;           // Max value scale

        // Fake Data: 50 -> 120 -> 180 -> 240 -> 260
        float values[] = {50, 120, 180, 240, 260};
        
        for(int i=0; i<5; i++) {
            float x = 30 + i * xStep;
            float y = yBase - (values[i] / yMax) * hGraph;
            points.append(QPointF(x, y));
        }

        // 4. Draw Area under curve
        QPainterPath path;
        path.moveTo(points.first());
        for (int i = 1; i < points.size(); ++i) {
             path.lineTo(points[i]);
        }
        
        QPainterPath fillPath = path;
        fillPath.lineTo(points.last().x(), yBase);
        fillPath.lineTo(points.first().x(), yBase);
        fillPath.closeSubpath();

        QColor fillColor("#A0522D");
        fillColor.setAlpha(50); // Transparent brown
        p.fillPath(fillPath, fillColor);

        // 5. Draw Curve Line
        p.setPen(QPen(QColor("#A0522D"), 2));
        p.drawPath(path);

        // 6. Draw Dots
        p.setBrush(QColor("#A0522D"));
        for (const QPointF &pt : points) {
            p.drawEllipse(pt, 4, 4);
        }

        // 7. Text Labels
        p.setPen(QColor("#555"));
        QFont font("Segoe UI", 8);
        p.setFont(font);
        
        QStringList xLabels = {"Fév.", "Mars", "Avr.", "Mai", "Juil."};
        for(int i=0; i<xLabels.size(); ++i) {
             p.drawText(QRect(30 + i * xStep - 20, h - 18, 40, 20), Qt::AlignCenter, xLabels[i]);
        }
        
        // Y Labels
        p.drawText(QRect(0, yBase - 10, 25, 20), Qt::AlignRight, "50");
        p.drawText(QRect(0, yBase - (150/yMax)*hGraph - 10, 25, 20), Qt::AlignRight, "150");
        p.drawText(QRect(0, yBase - (250/yMax)*hGraph - 10, 25, 20), Qt::AlignRight, "250");
        
        // Max value label near the top point
        p.setPen(QColor("#A0522D"));
        p.drawText(points.last().x() + 5, points.last().y(), "260");
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Main Widget and Layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setCentralWidget(centralWidget);

    // --- Sidebar (Left) ---
    QFrame *sidebar = new QFrame(this);
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(250);
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(20, 40, 20, 40);
    sidebarLayout->setSpacing(20);

    // Logo (Placeholder)
    QLabel *logoLabel = new QLabel("SMART\nCARPENTRY", sidebar);
    logoLabel->setObjectName("logoLabel");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #A0522D;");
    sidebarLayout->addWidget(logoLabel);

    // Main Content (Right) is now a Stacked Widget
    stackedWidget = new QStackedWidget(this);

    // Sidebar Buttons
    QStringList menuItems = {
        "Gestion des clients", "Gestion des commandes", "Gestion des employe"
    };

    for (int i = 0; i < menuItems.size(); ++i) {
        QPushButton *btn = new QPushButton(menuItems[i], sidebar);
        btn->setObjectName("menuButton");
        btn->setCursor(Qt::PointingHandCursor);
        sidebarLayout->addWidget(btn);

        connect(btn, &QPushButton::clicked, [this, i]() {
           switchPage(i);
        });
    }

    sidebarLayout->addStretch();

    QPushButton *quitBtn = new QPushButton("quitee", sidebar);
    quitBtn->setObjectName("quitButton");
    quitBtn->setCursor(Qt::PointingHandCursor);
    sidebarLayout->addWidget(quitBtn);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);

    // --- Page 0: Gestion des clients ---
    QWidget *clientsPage = new QWidget();
    clientsPage->setObjectName("contentArea"); // Reuse ID for background styling
    QVBoxLayout *contentLayout = new QVBoxLayout(clientsPage);
    contentLayout->setContentsMargins(30, 20, 30, 20);
    contentLayout->setSpacing(20);

    // Header Frame
    QFrame *headerFrame = new QFrame(clientsPage);
    QHBoxLayout *headerLayout = new QHBoxLayout(headerFrame);
    QLabel *pageTitle = new QLabel("Gestion des clients", headerFrame);
    pageTitle->setObjectName("pageTitle");
    pageTitle->setAlignment(Qt::AlignCenter);
    headerLayout->addWidget(pageTitle);
    contentLayout->addWidget(headerFrame);

    // Work Area (Form + Table)
    QHBoxLayout *workLayout = new QHBoxLayout();
    contentLayout->addLayout(workLayout);

    // Form Section
    QFrame *formFrame = new QFrame(clientsPage);
    formFrame->setObjectName("formFrame");
    formFrame->setFixedWidth(300);
    QVBoxLayout *formLayout = new QVBoxLayout(formFrame);

    QLabel *formHeader = new QLabel("Ajouter / Modifier client", formFrame);
    formHeader->setObjectName("formHeader");
    formHeader->setAlignment(Qt::AlignCenter);
    formLayout->addWidget(formHeader);

    QFormLayout *inputLayout = new QFormLayout();
    inputLayout->setLabelAlignment(Qt::AlignLeft); 
    
    QLineEdit *nomEdit = new QLineEdit(formFrame);
    QLineEdit *prenomEdit = new QLineEdit(formFrame);
    QLineEdit *telEdit = new QLineEdit(formFrame);
    QLineEdit *mailEdit = new QLineEdit(formFrame);
    QLineEdit *idEdit = new QLineEdit(formFrame);
    QDateEdit *dateEdit = new QDateEdit(formFrame);
    dateEdit->setDate(QDate(2000, 1, 1));
    dateEdit->setDisplayFormat("dd/MM/yyyy");

    inputLayout->addRow("Nom", nomEdit);
    inputLayout->addRow("Prenom", prenomEdit);
    inputLayout->addRow("Tel", telEdit);
    inputLayout->addRow("Mail", mailEdit);
    inputLayout->addRow("ID", idEdit);
    inputLayout->addRow("Date", dateEdit);

    formLayout->addLayout(inputLayout);
    
    QPushButton *validerBtn = new QPushButton("VALIDER", formFrame);
    validerBtn->setObjectName("validerButton");
    validerBtn->setCursor(Qt::PointingHandCursor);
    formLayout->addStretch();
    formLayout->addWidget(validerBtn);
    
    workLayout->addWidget(formFrame);

    // Table Section
    QVBoxLayout *tableSectionLayout = new QVBoxLayout();
    
    // Search & Tools
    QHBoxLayout *toolsLayout = new QHBoxLayout();
    QLineEdit *searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Rechercher par nom ou contact");
    QComboBox *sortCombo = new QComboBox();
    sortCombo->addItem("tri par nom");
    QPushButton *exportBtn = new QPushButton("Exporter PDF");
    exportBtn->setObjectName("exportButton");
    exportBtn->setIcon(QIcon::fromTheme("document-save")); // Placeholder icon

    toolsLayout->addWidget(searchEdit);
    toolsLayout->addWidget(sortCombo);
    toolsLayout->addWidget(exportBtn);
    
    tableSectionLayout->addLayout(toolsLayout);

    // Table
    QTableWidget *table = new QTableWidget(2, 6);
    table->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "tel", "Mail", "Date"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setAlternatingRowColors(true);
    
    // Mock Data
    table->setItem(0, 0, new QTableWidgetItem("1"));
    table->setItem(0, 1, new QTableWidgetItem("ahmed"));
    table->setItem(0, 2, new QTableWidgetItem("Ben ali"));
    table->setItem(0, 3, new QTableWidgetItem("22123345"));
    table->setItem(0, 4, new QTableWidgetItem("Ahed@gmail.com"));
    table->setItem(0, 5, new QTableWidgetItem("12/01/2026"));

    table->setItem(1, 0, new QTableWidgetItem("2"));
    table->setItem(1, 1, new QTableWidgetItem("Sara"));
    table->setItem(1, 2, new QTableWidgetItem("trabelsi"));
    table->setItem(1, 3, new QTableWidgetItem("56435746"));
    table->setItem(1, 4, new QTableWidgetItem("Sara@gmail.com"));
    table->setItem(1, 5, new QTableWidgetItem("25/01/2026"));

    tableSectionLayout->addWidget(table);

    workLayout->addLayout(tableSectionLayout);


    // --- Bottom Bar ---
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    contentLayout->addLayout(bottomLayout);

    // Graph/Analysis Section (Matches Screenshot)
    QFrame *graphFrame = new QFrame();
    // graphFrame->setFixedSize(400, 200); 
    graphFrame->setObjectName("graphFrame");
    graphFrame->setStyleSheet("background-color: #F5EFE6; border-radius: 10px;");
    
    QVBoxLayout *graphLayout = new QVBoxLayout(graphFrame);
    
    QLabel *graphTitle = new QLabel("Évolution du score de clients fidèles", graphFrame);
    graphTitle->setAlignment(Qt::AlignCenter);
    graphTitle->setStyleSheet("font-weight: bold; color: #555; font-size: 16px; margin-bottom: 5px;");
    graphLayout->addWidget(graphTitle);

    // Custom Chart Widget
    StatWidget *chart = new StatWidget(graphFrame);
    graphLayout->addWidget(chart);

    bottomLayout->addWidget(graphFrame, 2); // Stretch factor 2

    bottomLayout->addSpacing(20);

    // Bottom Action Buttons
    QHBoxLayout *actionBtnsLayout = new QHBoxLayout();
    
    QPushButton *addBtn = new QPushButton("Ajouter");
    QPushButton *delBtn = new QPushButton("Supprimer");
    QPushButton *editBtn = new QPushButton("Modifier");
    
    addBtn->setObjectName("actionButton");
    delBtn->setObjectName("actionButton");
    editBtn->setObjectName("actionButton");

    actionBtnsLayout->addWidget(addBtn);
    actionBtnsLayout->addWidget(delBtn);
    actionBtnsLayout->addWidget(editBtn); // Order: Add, Del, Edit (Screenshot seems to be Add, Supprimer, Modifier)

    bottomLayout->addLayout(actionBtnsLayout, 1); // Stretch factor 1


    // Add Clients Page as index 0
    stackedWidget->addWidget(clientsPage);

    // --- Page 1: Gestion des commandes (Placeholder) ---
    QWidget *commandesPage = new QWidget();
    commandesPage->setObjectName("contentArea"); // Reuse styling
    QVBoxLayout *cmdLayout = new QVBoxLayout(commandesPage);
    QLabel *cmdLabel = new QLabel("PAGE GESTION DES COMMANDES", commandesPage);
    cmdLabel->setAlignment(Qt::AlignCenter);
    cmdLabel->setStyleSheet("font-size: 30px; color: #A0522D; font-weight: bold;");
    cmdLayout->addWidget(cmdLabel);
    stackedWidget->addWidget(commandesPage);

    // --- Page 2: Gestion des Employes ---
    QWidget *employeePage = new QWidget();
    employeePage->setObjectName("contentArea"); // Reuse ID for background styling
    QVBoxLayout *empContentLayout = new QVBoxLayout(employeePage);
    empContentLayout->setContentsMargins(30, 20, 30, 20);
    empContentLayout->setSpacing(20);

    // Header Frame
    QFrame *empHeaderFrame = new QFrame(employeePage);
    QHBoxLayout *empHeaderLayout = new QHBoxLayout(empHeaderFrame);
    QLabel *empPageTitle = new QLabel("Gestion des Employes", empHeaderFrame);
    empPageTitle->setObjectName("pageTitle");
    empPageTitle->setAlignment(Qt::AlignCenter);
    empHeaderLayout->addWidget(empPageTitle);
    empContentLayout->addWidget(empHeaderFrame);

    // Work Area (Form + Table)
    QHBoxLayout *empWorkLayout = new QHBoxLayout();
    empContentLayout->addLayout(empWorkLayout);

    // Form Section
    QFrame *empFormFrame = new QFrame(employeePage);
    empFormFrame->setObjectName("formFrame");
    empFormFrame->setFixedWidth(300);
    QVBoxLayout *empFormLayout = new QVBoxLayout(empFormFrame);

    QLabel *empFormHeader = new QLabel("Ajouter / Modifier client", empFormFrame); // Matching screenshot text
    empFormHeader->setObjectName("formHeader");
    empFormHeader->setAlignment(Qt::AlignCenter);
    empFormLayout->addWidget(empFormHeader);

    QFormLayout *empInputLayout = new QFormLayout();
    empInputLayout->setLabelAlignment(Qt::AlignLeft); 
    
    QLineEdit *empNomEdit = new QLineEdit(empFormFrame);
    QLineEdit *empPrenomEdit = new QLineEdit(empFormFrame);
    QLineEdit *empIdEmplEdit = new QLineEdit(empFormFrame);
    QLineEdit *empMailEdit = new QLineEdit(empFormFrame);
    QLineEdit *empSalaireEdit = new QLineEdit(empFormFrame);
    QDateEdit *empDateEdit = new QDateEdit(empFormFrame);
    empDateEdit->setDate(QDate(2000, 1, 1));
    empDateEdit->setDisplayFormat("dd/MM/yyyy");

    // Matches the screenshot labels: nom, Prenom, idEmpl, Mail, salaire, Date
    empInputLayout->addRow("nom", empNomEdit);
    empInputLayout->addRow("Prenom", empPrenomEdit);
    empInputLayout->addRow("idEmpl", empIdEmplEdit);
    empInputLayout->addRow("Mail", empMailEdit);
    empInputLayout->addRow("salaire", empSalaireEdit);
    empInputLayout->addRow("Date", empDateEdit);

    empFormLayout->addLayout(empInputLayout);
    
    QPushButton *empValiderBtn = new QPushButton("VALIDER", empFormFrame);
    empValiderBtn->setObjectName("validerButton");
    empValiderBtn->setCursor(Qt::PointingHandCursor);
    empFormLayout->addStretch();
    empFormLayout->addWidget(empValiderBtn);
    
    empWorkLayout->addWidget(empFormFrame);

    // Table Section
    QVBoxLayout *empTableSectionLayout = new QVBoxLayout();
    
    // Search & Tools
    QHBoxLayout *empToolsLayout = new QHBoxLayout();
    QLineEdit *empSearchEdit = new QLineEdit();
    empSearchEdit->setPlaceholderText("Rechercher par nom ou contact");
    QComboBox *empSortCombo = new QComboBox();
    empSortCombo->addItem("tri par nom");
    
    empToolsLayout->addWidget(empSearchEdit);
    empToolsLayout->addWidget(empSortCombo);
    
    empTableSectionLayout->addLayout(empToolsLayout);

    // Table
    QTableWidget *empTable = new QTableWidget(2, 6);
    // Columns from screenshot: ID, Nom, Prenom, tel, Mail, Date
    empTable->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "tel", "Mail", "Date"});
    empTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    empTable->verticalHeader()->setVisible(false);
    empTable->setAlternatingRowColors(true);
    
    // Mock Data for Employees
    empTable->setItem(0, 0, new QTableWidgetItem("1"));
    empTable->setItem(0, 1, new QTableWidgetItem("ahmed"));
    empTable->setItem(0, 2, new QTableWidgetItem("Ben ali"));
    empTable->setItem(0, 3, new QTableWidgetItem("22123345"));
    empTable->setItem(0, 4, new QTableWidgetItem("Ahed@gmail.com"));
    empTable->setItem(0, 5, new QTableWidgetItem("12/01/2026"));

    empTable->setItem(1, 0, new QTableWidgetItem("2"));
    empTable->setItem(1, 1, new QTableWidgetItem("Sara"));
    empTable->setItem(1, 2, new QTableWidgetItem("trabelsi"));
    empTable->setItem(1, 3, new QTableWidgetItem("56435746"));
    empTable->setItem(1, 4, new QTableWidgetItem("Sara@gmail.com"));
    empTable->setItem(1, 5, new QTableWidgetItem("25/01/2026"));

    empTableSectionLayout->addWidget(empTable);

    empWorkLayout->addLayout(empTableSectionLayout);


    // --- Bottom Bar ---
    QHBoxLayout *empBottomLayout = new QHBoxLayout();
    empContentLayout->addLayout(empBottomLayout);

    // Circular Progress 
    QFrame *empCircleFrame = new QFrame();
    empCircleFrame->setFixedSize(120, 120);
    empCircleFrame->setObjectName("circleFrame");
    QVBoxLayout *empCircleLayout = new QVBoxLayout(empCircleFrame);
    QLabel *empPercentLabel = new QLabel("85%", empCircleFrame);
    empPercentLabel->setAlignment(Qt::AlignCenter);
    empPercentLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #333; border: none;");
    empCircleLayout->addWidget(empPercentLabel);

    empBottomLayout->addWidget(empCircleFrame);
    empBottomLayout->addStretch();

    // Bottom Action Buttons
    QPushButton *empAddBtn = new QPushButton("Ajouter");
    QPushButton *empEditBtn = new QPushButton("Modifier");
    QPushButton *empDelBtn = new QPushButton("Supprimer");
    
    empAddBtn->setObjectName("actionButton");
    editBtn->setObjectName("actionButton");
    delBtn->setObjectName("actionButton");
    
    empBottomLayout->addWidget(empAddBtn);
    empBottomLayout->addWidget(empEditBtn);
    empBottomLayout->addWidget(empDelBtn);

    QPushButton *empExportBtn = new QPushButton("Exporter PDF");
    empExportBtn->setObjectName("exportButton");
    empBottomLayout->addWidget(empExportBtn);

    stackedWidget->addWidget(employeePage);
    stackedWidget->setCurrentIndex(0); // Ensure we start on Clients page




    // --- STYLESHEET ---
    this->setStyleSheet(
        // General
        "QWidget { font-family: 'Segoe UI', sans-serif; font-size: 14px; }"
        
        // Sidebar
        "#sidebar { background-color: #E6D6C4; border-right: 1px solid #c0c0c0; }"
        "#logoLabel { margin-bottom: 20px; }"
        
        // Sidebar Menu Buttons
        "#menuButton { "
        "   background-color: #F5EFE6; "
        "   border: 1px solid #D7C4BB; "
        "   border-radius: 15px; "
        "   padding: 8px; "
        "   color: #333; "
        "   font-weight: bold; "
        "   text-align: center; "
        "}"
        "#menuButton:hover { background-color: #FFF; }"
        "#menuButton:pressed { background-color: #5DADE2; color: white; }"
        // Highlight one button like in image (Gestion des clients) - simulating selected state
        "#menuButton[text='Gestion des clients'] { background-color: #5DADE2; color: white; }"

        // Quit Button (Orange/Red)
        "#quitButton { "
        "   background-color: #C15933; "
        "   color: white; "
        "   border-radius: 15px; "
        "   padding: 8px 30px;"
        "   font-weight: bold; "
        "}"

        // Main Content Area
        "#contentArea { background-color: #FFFFFF; }"
        "#pageTitle { font-size: 18px; font-weight: bold; color: #333; margin-bottom: 10px; }"

        // Form Frame
        "#formFrame { background-color: #F5EFE6; border-radius: 15px; padding: 15px; }"
        "#formHeader { "
        "   background-color: #D2B48C; "
        "   color: white; "
        "   border-radius: 10px; "
        "   padding: 5px; "
        "   font-weight: bold; "
        "   margin-bottom: 10px; "
        "}"
        "QLabel { font-weight: bold; color: #444; }"
        "QLineEdit, QDateEdit { "
        "   border: 1px solid #CCC; "
        "   border-radius: 5px; "
        "   padding: 4px; "
        "   background-color: white; "
        "}"

        // Validate Button (Brown)
        "#validerButton { "
        "   background-color: #A0522D; "
        "   color: white; "
        "   border-radius: 10px; "
        "   padding: 8px 15px; "
        "   font-weight: bold; "
        "}"

        // Table Tools
        "QComboBox, QLineEdit { height: 25px; }"
        "#exportButton { "
        "   background-color: #C15933; "
        "   color: white; "
        "   border-radius: 5px; "
        "   padding: 5px 15px; "
        "   font-weight: bold; "
        "}"

        // Table
        "QTableWidget { gridline-color: #DDD; selection-background-color: #5DADE2; }"
        "QHeaderView::section { "
        "   background-color: #F0E6DC; "
        "   padding: 5px; "
        "   border: 1px solid #DDD; "
        "   font-weight: bold; "
        "}"

        // Bottom Action Buttons
        "#actionButton { "
        "   background-color: #A0522D; "
        "   color: white; "
        "   border-radius: 10px; "
        "   padding: 10px 30px; " /* Bigger padding */
        "   font-weight: bold; "
        "   font-size: 14px; "
        "}"
        "#actionButton:hover { background-color: #8B4513; }"

        // Circular Progress (Fake)
        "#circleFrame { "
        "   background-color: #F5EFE6; "
        "   border: 4px solid #6B8E23; " /* Olive green ring like 85% */
        "   border-radius: 60px; " /* Half of size 120 */
        "}"
    );

    this->setWindowTitle("Smart Carpentry Manager");
    this->resize(1000, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchPage(int index)
{
    if(stackedWidget) {
        stackedWidget->setCurrentIndex(index);
    }
}

