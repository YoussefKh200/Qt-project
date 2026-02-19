#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// User data structure
struct User {
    QString nom;
    QString prenom;
    QString tel;
    QString mail;
    QString mdp;
    QString salaire;
    QString role;
    QString etat;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int currentEditingRow = -1;  // Track which row is being edited (-1 = adding new)

    void setupConnections();
    void addUserToTable(const User &user);
    void loadUserToForm(int row);
    void clearForm();
    void updateButtonStates();
    void onAddUserClicked();
    void onModifyUserClicked();
    void onDeleteUserClicked();
    void onTableRowSelected();
    void onValidateUserClicked();
    void exportToPDF();
    void onSearchTextChanged(const QString &text);
    
};

#endif // MAINWINDOW_H
