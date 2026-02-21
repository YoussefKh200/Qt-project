#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include <QString>
#include "../models/userCrud.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class UserWindow;
}
QT_END_NAMESPACE

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

private:
    Ui::UserWindow *ui;
    UserCrud *userCrud;
    int currentEditingRow;

    // UI Setup and Display
    void setupConnections();
    void loadAllUsersFromDB();
    void clearForm();
    void updateButtonStates();
    
    // Table Operations
    void addUserToTable(const UserData &user);
    void loadUserToForm(int row);
    
    // Event Handlers
    void onValidateUserClicked();
    void onModifyUserClicked();
    void onDeleteUserClicked();
    void onTableRowSelected();
    void onSearchTextChanged(const QString &text);
    
    // Export
    void exportToPDF();
    
    // Helper
    UserData getUserDataFromForm() const;
};

#endif // USER_H
