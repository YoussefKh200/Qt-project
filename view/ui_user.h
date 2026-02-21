/********************************************************************************
** Form generated from reading UI file 'user.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_H
#define UI_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *pageUser;
    QGroupBox *groupBox_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QPushButton *pushButton_12;
    QLabel *label_17;
    QLineEdit *lineEdit_13;
    QLabel *label_18;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QComboBox *comboBox;
    QLabel *lblStatCircle;
    QTableWidget *tableWidget_3;
    QLineEdit *lineEdit_12;
    QTableView *tableView_4;
    QPushButton *pushButton_13;
    QLineEdit *searchBar;
    QComboBox *comboBox_4;
    QTableView *tableView_2;
    QPushButton *btnUser;
    QPushButton *btnClient;
    QPushButton *btnCommande;
    QPushButton *btnFournisseur;
    QPushButton *btnMateriaux;
    QPushButton *btnSignout;
    QPushButton *btnParametre;
    QLabel *user_modify;
    QLabel *user_delete;
    QWidget *pageFournisseur;
    QWidget *pageCommande;
    QWidget *pageMateriaux;
    QWidget *pageClient;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserWindow)
    {
        if (UserWindow->objectName().isEmpty())
            UserWindow->setObjectName("UserWindow");
        UserWindow->resize(1424, 820);
        centralwidget = new QWidget(UserWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-30, 0, 1531, 891));
        pageUser = new QWidget();
        pageUser->setObjectName("pageUser");
        groupBox_2 = new QGroupBox(pageUser);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(300, 70, 281, 361));
        groupBox_2->setStyleSheet(QString::fromUtf8("/* \330\247\331\204\330\245\330\267\330\247\330\261 \330\247\331\204\330\271\330\247\331\205 */\n"
"QGroupBox {\n"
"    background-color: #F2EADF;      /* beige \331\201\330\247\330\252\330\255 */\n"
"    border: 1px solid #C9B8A3;      /* \330\250\331\206\331\212 \331\201\330\247\330\252\330\255 */\n"
"    border-radius: 14px;\n"
"    margin-top: 25px;               /* \330\250\331\204\330\247\330\265\330\251 \331\204\331\204\330\271\331\206\331\210\330\247\331\206 */\n"
"    font-weight: bold;\n"
"    color: #5A3E2B;                 /* \330\250\331\206\331\212 \330\272\330\247\331\205\331\202 */\n"
"}\n"
"\n"
"/* \330\271\331\206\331\210\330\247\331\206 \330\247\331\204\331\200 GroupBox */\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 6px 14px;\n"
"    background-color: #D6B48A;      /* \330\250\331\206\331\212 \330\256\330\264\330\250\331\212 */\n"
"    border-radius: 10px;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Labels */\n"
"QLabel {\n"
""
                        "    color: #5A3E2B;\n"
"    font-weight: normal;\n"
"}\n"
"\n"
"/* Inputs */\n"
"QLineEdit,\n"
"QDateEdit,\n"
"QSpinBox {\n"
"    background-color: white;\n"
"    border: 1px solid #C9B8A3;\n"
"    border-radius: 6px;\n"
"    padding: 4px;\n"
"    color: #333;\n"
"}\n"
"\n"
"/* Focus */\n"
"QLineEdit:focus,\n"
"QDateEdit:focus,\n"
"QSpinBox:focus {\n"
"    border: 1px solid #B08968;\n"
"}\n"
"\n"
"/* CheckBox */\n"
"QCheckBox {\n"
"    color: #5A3E2B;\n"
"}\n"
"\n"
"/* Bouton \330\257\330\247\330\256\331\204 \330\247\331\204\331\201\331\210\330\261\331\205 (\331\204\331\210 \330\252\330\255\330\250 \330\252\330\255\330\267 Valider \330\257\330\247\330\256\331\204 \330\247\331\204\331\200 GroupBox) */\n"
"QPushButton {\n"
"    background-color: #8FAADC;\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #7A98C8;\n"
"}\n"
"QGroupBox {\n"
"    background-color: #f3eadf;\n"
"    border: 1px solid #d2b48c;\n"
""
                        "    border-radius: 14px;\n"
"    padding: 12px;\n"
"}\n"
"\n"
""));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 50, 63, 20));
        label_10->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 80, 63, 20));
        label_11->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 110, 63, 20));
        label_12->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 140, 63, 20));
        label_13->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 170, 63, 20));
        label_14->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 200, 63, 20));
        label_15->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(80, 50, 113, 26));
        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(80, 80, 113, 26));
        lineEdit_9 = new QLineEdit(groupBox_2);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(80, 110, 113, 26));
        lineEdit_10 = new QLineEdit(groupBox_2);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(80, 140, 113, 26));
        lineEdit_11 = new QLineEdit(groupBox_2);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(80, 170, 113, 26));
        pushButton_12 = new QPushButton(groupBox_2);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(140, 320, 93, 29));
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #a04f2f;\n"
"    color: white;\n"
"    border-radius: 12px;\n"
"    padding: 6px 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #178817;\n"
"}\n"
""));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 230, 63, 20));
        label_17->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        lineEdit_13 = new QLineEdit(groupBox_2);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(80, 200, 113, 26));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 260, 63, 20));
        label_18->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #4A2F1A;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(70, 260, 76, 21));
        checkBox_2 = new QCheckBox(groupBox_2);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(70, 280, 76, 21));
        comboBox = new QComboBox(groupBox_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(80, 230, 65, 24));
        lblStatCircle = new QLabel(pageUser);
        lblStatCircle->setObjectName("lblStatCircle");
        lblStatCircle->setGeometry(QRect(390, 620, 152, 152));
        lblStatCircle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tableWidget_3 = new QTableWidget(pageUser);
        if (tableWidget_3->columnCount() < 10)
            tableWidget_3->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font;
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::CallStart));
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        __qtablewidgetitem3->setIcon(icon);
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::MailForward));
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        __qtablewidgetitem4->setIcon(icon1);
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        tableWidget_3->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        if (tableWidget_3->rowCount() < 2)
            tableWidget_3->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_3->setVerticalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 6, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 7, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 8, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 2, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 3, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 4, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 5, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 6, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 7, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_3->setItem(1, 8, __qtablewidgetitem27);
        tableWidget_3->setObjectName("tableWidget_3");
        tableWidget_3->setGeometry(QRect(590, 140, 821, 301));
        tableWidget_3->setStyleSheet(QString::fromUtf8("/* \330\247\331\204\330\254\330\257\331\210\331\204 \330\247\331\204\331\203\331\204 */\n"
"QTableWidget {\n"
"    background-color: #FFFFFF;\n"
"    border: 1px solid #C9B8A3;\n"
"    border-radius: 10px;\n"
"    gridline-color: #E0D6C8;\n"
"    font-size: 12px;\n"
"    selection-background-color: #8FAADC;\n"
"    selection-color: white;\n"
"}\n"
"\n"
"/* Header \331\205\330\252\330\247\330\271 \330\247\331\204\330\243\330\271\331\205\330\257\330\251 */\n"
"QHeaderView::section {\n"
"    background-color: #EFE6DA;   /* beige */\n"
"    color: #5A3E2B;              /* \330\250\331\206\331\212 \330\272\330\247\331\205\331\202 */\n"
"    padding: 6px;\n"
"    border: 1px solid #C9B8A3;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* \330\247\331\204\330\256\331\204\330\247\331\212\330\247 */\n"
"QTableWidget::item {\n"
"    padding: 6px;\n"
"    border: none;\n"
"    color: #333;\n"
"}\n"
"\n"
"/* Hover \330\271\331\204\331\211 \330\247\331\204\330\263\330\267\330\261 */\n"
"QTableWidget::item:hover {\n"
"    backg"
                        "round-color: #F3EFEA;\n"
"}\n"
"\n"
"/* \330\247\331\204\330\263\330\267\330\261 \330\247\331\204\331\205\330\256\330\252\330\247\330\261 */\n"
"QTableWidget::item:selected {\n"
"    background-color: #8FAADC;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Corner (\330\250\331\212\331\206 headers) */\n"
"QTableCornerButton::section {\n"
"    background-color: #EFE6DA;\n"
"    border: 1px solid #C9B8A3;\n"
"}\n"
"\n"
"/* Scrollbar \330\271\331\205\331\210\330\257\331\212 */\n"
"QScrollBar:vertical {\n"
"    background: #F2EADF;\n"
"    width: 10px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #C9B8A3;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #B08968;\n"
"}\n"
""));
        tableWidget_3->setColumnCount(10);
        lineEdit_12 = new QLineEdit(pageUser);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(50, 0, 1651, 61));
        lineEdit_12->setStyleSheet(QString::fromUtf8("#lineEdit_12{\n"
"    background-color: #ffffff;     /* keep it clean white */\n"
"    color: #333333;                /* text color */\n"
"    font: bold 18px \"Arial\";       /* Arial, bold, size 14 */\n"
"    qproperty-alignment: 'AlignCenter'; /* centers the text inside */\n"
"    border: 2px solid #ccc;        /* optional border */\n"
"    border-radius: 6px;            /* rounded corners */\n"
"    padding: 6px 10px;             /* spacing */\n"
"}"));
        tableView_4 = new QTableView(pageUser);
        tableView_4->setObjectName("tableView_4");
        tableView_4->setGeometry(QRect(290, 30, 1381, 771));
        tableView_4->setStyleSheet(QString::fromUtf8("\n"
"background-color: #EFE6DA;"));
        pushButton_13 = new QPushButton(pageUser);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(1310, 470, 111, 31));
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #b85c38;\n"
"    color: white;\n"
"    border-radius: 12px;\n"
"    padding: 6px 10px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #a04f2f;\n"
"}\n"
""));
        searchBar = new QLineEdit(pageUser);
        searchBar->setObjectName("searchBar");
        searchBar->setGeometry(QRect(600, 70, 471, 41));
        searchBar->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	color: rgb(0, 0, 0);\n"
"    background-color: #f6efe8;\n"
"    border: 1px solid #d2b48c;\n"
"    border-radius: 14px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"}\n"
""));
        comboBox_4 = new QComboBox(pageUser);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(1150, 90, 191, 31));
        comboBox_4->setStyleSheet(QString::fromUtf8("\n"
"comboBox_3 {\n"
"    background-color: #f6efe8;\n"
"    border: 1px solid #d2b48c;\n"
"    border-radius: 14px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"}"));
        tableView_2 = new QTableView(pageUser);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(50, 0, 241, 801));
        tableView_2->setStyleSheet(QString::fromUtf8("\n"
"background-color: #D6B48A;"));
        btnUser = new QPushButton(pageUser);
        btnUser->setObjectName("btnUser");
        btnUser->setGeometry(QRect(70, 170, 191, 41));
        btnUser->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(111, 163, 200);\n"
"    color: white;\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}"));
        btnClient = new QPushButton(pageUser);
        btnClient->setObjectName("btnClient");
        btnClient->setGeometry(QRect(70, 230, 191, 41));
        btnClient->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(255, 250, 242);\n"
"	color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}"));
        btnCommande = new QPushButton(pageUser);
        btnCommande->setObjectName("btnCommande");
        btnCommande->setGeometry(QRect(70, 290, 191, 41));
        btnCommande->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(255, 250, 242);\n"
"	color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}"));
        btnFournisseur = new QPushButton(pageUser);
        btnFournisseur->setObjectName("btnFournisseur");
        btnFournisseur->setGeometry(QRect(70, 350, 191, 41));
        btnFournisseur->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(255, 250, 242);\n"
"	color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}"));
        btnMateriaux = new QPushButton(pageUser);
        btnMateriaux->setObjectName("btnMateriaux");
        btnMateriaux->setGeometry(QRect(70, 410, 191, 41));
        btnMateriaux->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(255, 250, 242);\n"
"	color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}"));
        btnSignout = new QPushButton(pageUser);
        btnSignout->setObjectName("btnSignout");
        btnSignout->setGeometry(QRect(70, 740, 191, 41));
        btnSignout->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(255, 250, 242);\n"
"	color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}"));
        btnParametre = new QPushButton(pageUser);
        btnParametre->setObjectName("btnParametre");
        btnParametre->setGeometry(QRect(70, 680, 191, 41));
        btnParametre->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(255, 250, 242);\n"
"	color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}"));
        user_modify = new QLabel(pageUser);
        user_modify->setObjectName("user_modify");
        user_modify->setGeometry(QRect(1420, 320, 31, 16));
        user_delete = new QLabel(pageUser);
        user_delete->setObjectName("user_delete");
        user_delete->setGeometry(QRect(1460, 320, 31, 16));
        stackedWidget->addWidget(pageUser);
        tableView_4->raise();
        tableView_2->raise();
        groupBox_2->raise();
        lblStatCircle->raise();
        tableWidget_3->raise();
        lineEdit_12->raise();
        pushButton_13->raise();
        searchBar->raise();
        comboBox_4->raise();
        btnUser->raise();
        btnClient->raise();
        btnCommande->raise();
        btnFournisseur->raise();
        btnMateriaux->raise();
        btnSignout->raise();
        btnParametre->raise();
        user_modify->raise();
        user_delete->raise();
        pageFournisseur = new QWidget();
        pageFournisseur->setObjectName("pageFournisseur");
        stackedWidget->addWidget(pageFournisseur);
        pageCommande = new QWidget();
        pageCommande->setObjectName("pageCommande");
        stackedWidget->addWidget(pageCommande);
        pageMateriaux = new QWidget();
        pageMateriaux->setObjectName("pageMateriaux");
        stackedWidget->addWidget(pageMateriaux);
        pageClient = new QWidget();
        pageClient->setObjectName("pageClient");
        stackedWidget->addWidget(pageClient);
        UserWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(UserWindow);
        statusbar->setObjectName("statusbar");
        UserWindow->setStatusBar(statusbar);

        retranslateUi(UserWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserWindow)
    {
        UserWindow->setWindowTitle(QCoreApplication::translate("UserWindow", "UserWindow", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("UserWindow", "Ajouter / Modifier client ", nullptr));
        label_10->setText(QCoreApplication::translate("UserWindow", "nom", nullptr));
        label_11->setText(QCoreApplication::translate("UserWindow", "Prenom", nullptr));
        label_12->setText(QCoreApplication::translate("UserWindow", "tel", nullptr));
        label_13->setText(QCoreApplication::translate("UserWindow", "Mail", nullptr));
        label_14->setText(QCoreApplication::translate("UserWindow", "MDP", nullptr));
        label_15->setText(QCoreApplication::translate("UserWindow", "salaire", nullptr));
        lineEdit_11->setText(QString());
        pushButton_12->setText(QCoreApplication::translate("UserWindow", "VALIDER", nullptr));
        label_17->setText(QCoreApplication::translate("UserWindow", "role", nullptr));
        lineEdit_13->setText(QString());
        label_18->setText(QCoreApplication::translate("UserWindow", "etat", nullptr));
        checkBox->setText(QCoreApplication::translate("UserWindow", "actif", nullptr));
        checkBox_2->setText(QCoreApplication::translate("UserWindow", "non actif", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("UserWindow", "chef", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("UserWindow", "ouvrier", nullptr));

        lblStatCircle->setStyleSheet(QCoreApplication::translate("UserWindow", "font-size: 30pt; font-weight: bold; color: #4b3621; border: 6px solid #829f60; border-radius: 70px; background-color: #f2e9de; min-width: 140px; min-height: 140px; max-width: 140px; max-height: 140px;", nullptr));
        lblStatCircle->setText(QCoreApplication::translate("UserWindow", "85%", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UserWindow", "tel", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("UserWindow", "Mail", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_3->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("UserWindow", "MDP", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_3->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("UserWindow", "salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_3->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("UserWindow", "role", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_3->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("UserWindow", "etat", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_3->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("UserWindow", "action", nullptr));

        const bool __sortingEnabled = tableWidget_3->isSortingEnabled();
        tableWidget_3->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_3->item(0, 1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("UserWindow", "ahmed", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_3->item(0, 2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("UserWindow", "Ben ali", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_3->item(0, 3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("UserWindow", "22123345", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_3->item(0, 4);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("UserWindow", "Ahed@gmail.com", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_3->item(0, 5);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("UserWindow", "12/01/2026", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_3->item(0, 6);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("UserWindow", "fidele", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_3->item(0, 7);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("UserWindow", "chef", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_3->item(0, 8);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("UserWindow", "actif", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_3->item(1, 1);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("UserWindow", "Sara", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_3->item(1, 2);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("UserWindow", "trabelsi", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_3->item(1, 3);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("UserWindow", "56435746", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_3->item(1, 4);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("UserWindow", "Sara@gmail.com", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_3->item(1, 5);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("UserWindow", "25/01/2026", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_3->item(1, 6);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("UserWindow", "occasionnel", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_3->item(1, 7);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("UserWindow", "ouvrier", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_3->item(1, 8);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("UserWindow", "non actif", nullptr));
        tableWidget_3->setSortingEnabled(__sortingEnabled);

        lineEdit_12->setText(QCoreApplication::translate("UserWindow", "Gestion des Employes", nullptr));
        pushButton_13->setText(QCoreApplication::translate("UserWindow", "\360\237\223\204Exporter PDF", nullptr));
        searchBar->setText(QCoreApplication::translate("UserWindow", "Recherche", nullptr));
        searchBar->setPlaceholderText(QCoreApplication::translate("UserWindow", "Telephone", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("UserWindow", "tri par nom", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("UserWindow", "khg", nullptr));

        btnUser->setText(QCoreApplication::translate("UserWindow", "Gestion des Utilisateurs", nullptr));
        btnClient->setText(QCoreApplication::translate("UserWindow", "Gestion des Clients", nullptr));
        btnCommande->setText(QCoreApplication::translate("UserWindow", "Gestion des Commandes", nullptr));
        btnFournisseur->setText(QCoreApplication::translate("UserWindow", "Gestion des Fournisseurs", nullptr));
        btnMateriaux->setText(QCoreApplication::translate("UserWindow", "Gestion des Materiaux", nullptr));
        btnSignout->setText(QCoreApplication::translate("UserWindow", "Se d\303\251connecter", nullptr));
        btnParametre->setText(QCoreApplication::translate("UserWindow", "Param\303\250tres", nullptr));
        user_modify->setText(QString());
        user_delete->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserWindow: public Ui_UserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_H
