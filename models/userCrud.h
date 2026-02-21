#ifndef USERCRUD_H
#define USERCRUD_H

#include <QString>
#include <QList>

// User data structure
struct UserData {
    int id;
    QString nom;
    QString prenom;
    QString tel;
    QString mail;
    QString mdp;
    QString salaire;
    QString role;
    QString etat;
    
    UserData() : id(-1) {}
};

class UserCrud
{
public:
    UserCrud();
    ~UserCrud();

    // CRUD operations
    bool addUser(const UserData &user, QString &error);
    bool updateUser(const UserData &user, QString &error);
    bool deleteUser(int id, QString &error);
    QList<UserData> getAllUsers();
    QList<UserData> searchUsers(const QString &searchText);
    UserData getUserById(int id);
    
    // Validation & Security
    static QString validateUser(const UserData &user);
    static QString hashPassword(const QString &password);
    static bool verifyPassword(const QString &password, const QString &hash);
    
    QString getLastError() const { return m_lastError; }
    
private:
    bool executeQuery(class QSqlQuery &query);
    int getNextId(QString &error);
    UserData readUserFromQuery(class QSqlQuery &query);
    QString sanitizeInput(const QString &input);
    QString m_lastError;
};

#endif // USERCRUD_H
