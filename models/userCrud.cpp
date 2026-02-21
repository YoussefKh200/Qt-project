#include "userCrud.h"
#include "../connection/connection.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCryptographicHash>
#include <QUuid>
#include <QRegularExpression>

UserCrud::UserCrud() : m_lastError("")
{
}

UserCrud::~UserCrud()
{
}

// ============= Security Methods =============

QString UserCrud::hashPassword(const QString &password)
{
    if (password.isEmpty()) {
        return "";
    }
    
    // Generate random salt (16 bytes)
    QString salt = QUuid::createUuid().toString().replace("{", "").replace("}", "").replace("-", "").left(16);
    
    // Combine password + salt
    QString combined = password + salt;
    
    // Hash with SHA256
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(combined.toUtf8());
    QString hashedPassword = hash.result().toHex();
    
    // Return: hash$salt format
    return hashedPassword + "$" + salt;
}

bool UserCrud::verifyPassword(const QString &password, const QString &hash)
{
    if (password.isEmpty() || hash.isEmpty()) {
        return false;
    }
    
    // Extract salt from hash
    QStringList parts = hash.split("$");
    if (parts.size() != 2) {
        return false;
    }
    
    QString storedHash = parts[0];
    QString salt = parts[1];
    
    // Hash the provided password with the same salt
    QString combined = password + salt;
    QCryptographicHash hashCheck(QCryptographicHash::Sha256);
    hashCheck.addData(combined.toUtf8());
    QString computedHash = hashCheck.result().toHex();
    
    return computedHash == storedHash;
}

QString UserCrud::sanitizeInput(const QString &input)
{
    // Remove leading/trailing whitespace and limit length
    QString sanitized = input.trimmed();
    
    // Limit input length to prevent buffer issues
    if (sanitized.length() > 500) {
        sanitized = sanitized.left(500);
    }
    
    return sanitized;
}

bool UserCrud::executeQuery(QSqlQuery &query)
{
    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Query error:" << m_lastError;
        return false;
    }
    return true;
}

UserData UserCrud::readUserFromQuery(QSqlQuery &query)
{
    UserData user;
    user.id = query.value(0).toInt();
    user.nom = query.value(1).toString();
    user.prenom = query.value(2).toString();
    user.tel = query.value(3).toString();
    user.mail = query.value(4).toString();
    user.mdp = query.value(5).toString();
    user.salaire = query.value(6).toString();
    user.role = query.value(7).toString();
    user.etat = query.value(8).toString();
    return user;
}

QString UserCrud::validateUser(const UserData &user)
{
    // Basic fields
    if (user.nom.trimmed().isEmpty()) return "Le nom ne peut pas être vide";
    if (user.prenom.trimmed().isEmpty()) return "Le prénom ne peut pas être vide";
    if (user.mdp.isEmpty()) return "Le mot de passe ne peut pas être vide";
    if (user.mdp.length() < 8) return "Le mot de passe doit contenir au moins 8 caractères";
    if (user.role.isEmpty()) return "Le rôle doit être sélectionné";
    if (user.etat.isEmpty()) return "L'état doit être sélectionné";
    
    // Phone validation (8 digits)
    if (user.tel.isEmpty()) return "Le téléphone ne peut pas être vide";
    if (user.tel.length() != 8 || !user.tel.toULongLong(nullptr, 10)) 
        return "Le téléphone doit contenir exactement 8 chiffres";
    
    // Email validation
    if (user.mail.isEmpty()) return "Le mail ne peut pas être vide";
    if (!user.mail.contains("@") || !user.mail.contains(".")) 
        return "Le mail doit être au format valide (ex: exemple@gmail.com)";
    int atIndex = user.mail.indexOf("@");
    int dotIndex = user.mail.lastIndexOf(".");
    if (atIndex <= 0 || dotIndex <= atIndex + 1 || dotIndex == user.mail.length() - 1)
        return "Le mail doit être au format valide (ex: exemple@gmail.com)";
    
    // Salary validation
    if (user.salaire.isEmpty()) return "Le salaire ne peut pas être vide";
    bool ok;
    double salary = user.salaire.toDouble(&ok);
    if (!ok || salary < 0) return "Le salaire doit être un nombre valide (ex: 1500 ou 1500.50)";
    
    return "";
}

bool UserCrud::addUser(const UserData &user, QString &error)
{
    error = validateUser(user);
    if (!error.isEmpty()) {
        m_lastError = error;
        return false;
    }
    
    int newId = getNextId(error);
    if (newId <= 0) {
        error = "Erreur lors de la création de l'ID utilisateur";
        m_lastError = error;
        return false;
    }

    // Hash password before storing
    QString hashedPassword = hashPassword(user.mdp);

    QSqlQuery query;
    query.prepare("INSERT INTO USERS (ID_USER, NOM, PRENOM, TEL, MAIL, MDP, SALAIRE, ROLE, ETAT) "
                  "VALUES (:id, :nom, :prenom, :tel, :mail, :mdp, :salaire, :role, :etat)");

    query.bindValue(":id", newId);
    query.bindValue(":nom", sanitizeInput(user.nom));
    query.bindValue(":prenom", sanitizeInput(user.prenom));
    query.bindValue(":tel", user.tel.trimmed());  // Already validated to be digits
    query.bindValue(":mail", sanitizeInput(user.mail));
    query.bindValue(":mdp", hashedPassword);  // Store hashed password
    query.bindValue(":salaire", user.salaire.toDouble());
    query.bindValue(":role", sanitizeInput(user.role));
    query.bindValue(":etat", sanitizeInput(user.etat));
    
    if (executeQuery(query)) {
        qDebug() << "User added successfully with ID" << newId;
        return true;
    }
    error = "Erreur lors de l'ajout de l'utilisateur";
    return false;
}

int UserCrud::getNextId(QString &error)
{
    QSqlQuery query;
    
    // Try predefined sequence names (safe - hardcoded)
    QStringList sequences = {"USERS_SEQ", "ID_USER_SEQ", "SEQ_USERS", "USERS_ID_SEQ", "SEQ_USERS_ID"};

    for (const QString &seqName : sequences) {
        // Only allow alphanumeric and underscore in sequence names
        if (!seqName.contains(QRegularExpression("^[A-Za-z_][A-Za-z0-9_]*$"))) {
            continue;
        }
        
        // Use parameterized approach where possible (Oracle sequences don't support params)
        QString sql = "SELECT " + seqName + ".NEXTVAL FROM DUAL";
        if (query.exec(sql) && query.next()) {
            return query.value(0).toInt();
        }
        query.clear();
    }

    // Fallback: get max ID and create sequence
    QSqlQuery maxQuery;
    if (!maxQuery.exec("SELECT NVL(MAX(ID_USER),0)+1 FROM USERS")) {
        error = "Erreur lors de la récupération de l'ID";
        m_lastError = error;
        return -1;
    }
    
    int nextId = 1;
    if (maxQuery.next()) {
        nextId = maxQuery.value(0).toInt();
    }

    // Try to create sequence (non-critical if fails)
    QSqlQuery createQuery;
    QString createSql = "CREATE SEQUENCE USERS_SEQ START WITH " + QString::number(nextId) + " INCREMENT BY 1 NOCACHE NOCYCLE";
    createQuery.exec(createSql);  // Ignore error if sequence already exists
    
    return nextId;
}

bool UserCrud::updateUser(const UserData &user, QString &error)
{
    if (user.id <= 0) {
        error = "ID utilisateur invalide";
        m_lastError = error;
        return false;
    }
    
    error = validateUser(user);
    if (!error.isEmpty()) {
        m_lastError = error;
        return false;
    }
    
    // Hash password before storing
    QString hashedPassword = hashPassword(user.mdp);
    
    QSqlQuery query;
    query.prepare("UPDATE USERS SET NOM=:nom, PRENOM=:prenom, TEL=:tel, MAIL=:mail, "
                  "MDP=:mdp, SALAIRE=:salaire, ROLE=:role, ETAT=:etat WHERE ID_USER=:id");
    query.bindValue(":id", user.id);
    query.bindValue(":nom", sanitizeInput(user.nom));
    query.bindValue(":prenom", sanitizeInput(user.prenom));
    query.bindValue(":tel", user.tel.trimmed());
    query.bindValue(":mail", sanitizeInput(user.mail));
    query.bindValue(":mdp", hashedPassword);  // Store hashed password
    query.bindValue(":salaire", user.salaire.toDouble());
    query.bindValue(":role", sanitizeInput(user.role));
    query.bindValue(":etat", sanitizeInput(user.etat));
    
    if (executeQuery(query)) {
        qDebug() << "User updated successfully";
        return true;
    }
    error = "Erreur lors de la mise à jour de l'utilisateur";
    return false;
}

bool UserCrud::deleteUser(int id, QString &error)
{
    if (id <= 0) {
        error = "ID utilisateur invalide";
        m_lastError = error;
        return false;
    }
    
    QSqlQuery query;
    query.prepare("DELETE FROM USERS WHERE ID_USER=:id");
    query.bindValue(":id", id);
    
    if (executeQuery(query)) {
        qDebug() << "User deleted successfully";
        return true;
    }
    error = m_lastError;
    return false;
}

QList<UserData> UserCrud::getAllUsers()
{
    QList<UserData> userList;
    QSqlQuery query("SELECT ID_USER, NOM, PRENOM, TEL, MAIL, MDP, SALAIRE, ROLE, ETAT FROM USERS");
    
    if (!query.exec()) {
        m_lastError = "Erreur lors de la récupération des utilisateurs";
        qDebug() << "Error retrieving users:" << query.lastError().text();
        return userList;
    }
    
    while (query.next()) {
        userList.append(readUserFromQuery(query));
    }
    
    qDebug() << "Retrieved" << userList.size() << "users";
    return userList;
}

QList<UserData> UserCrud::searchUsers(const QString &searchText)
{
    QList<UserData> userList;
    
    if (searchText.trimmed().isEmpty()) {
        return getAllUsers();
    }
    
    QSqlQuery query;
    query.prepare("SELECT ID_USER, NOM, PRENOM, TEL, MAIL, MDP, SALAIRE, ROLE, ETAT FROM USERS "
                  "WHERE LOWER(NOM) LIKE :search OR LOWER(PRENOM) LIKE :search "
                  "OR LOWER(TEL) LIKE :search OR LOWER(MAIL) LIKE :search");
    
    query.bindValue(":search", "%" + searchText.toLower() + "%");
    
    if (query.exec()) {
        while (query.next()) {
            userList.append(readUserFromQuery(query));
        }
    } else {
        m_lastError = "Erreur lors de la recherche";
        qDebug() << "Search error:" << query.lastError().text();
    }
    
    return userList;
}

UserData UserCrud::getUserById(int id)
{
    UserData user;
    
    if (id <= 0) {
        m_lastError = "ID utilisateur invalide";
        return user;
    }
    
    QSqlQuery query;
    query.prepare("SELECT ID_USER, NOM, PRENOM, TEL, MAIL, MDP, SALAIRE, ROLE, ETAT FROM USERS WHERE ID_USER=:id");
    query.bindValue(":id", id);
    
    if (query.exec() && query.next()) {
        user = readUserFromQuery(query);
    } else {
        m_lastError = "Utilisateur non trouvé";
        qDebug() << "Error getting user:" << query.lastError().text();
    }
    
    return user;
}
{
    QSqlQuery query;
    QStringList seqCandidates = {"USERS_SEQ", "ID_USER_SEQ", "SEQ_USERS", "USERS_ID_SEQ", "SEQ_USERS_ID"};

    // Try common sequence names
    for (const QString &seqName : seqCandidates) {
        QString sql = QString("SELECT %1.NEXTVAL FROM DUAL").arg(seqName);
        if (query.exec(sql) && query.next()) {
            return query.value(0).toInt();
        }
        // clear state for next attempt
        query.clear();
    }

    // No existing sequence found; try to create one starting after current max(ID_USER)
    QSqlQuery q2;
    if (!q2.exec("SELECT NVL(MAX(ID_USER),0)+1 FROM USERS")) {
        error = q2.lastError().text();
        m_lastError = error;
        return -1;
    }
    int startVal = 1;
    if (q2.next()) startVal = q2.value(0).toInt();

    QString createSql = QString("CREATE SEQUENCE USERS_SEQ START WITH %1 INCREMENT BY 1 NOCACHE NOCYCLE").arg(startVal);
    if (!q2.exec(createSql)) {
        error = q2.lastError().text();
        m_lastError = error;
        return -1;
    }

    QSqlQuery q3;
    if (!q3.exec("SELECT USERS_SEQ.NEXTVAL FROM DUAL") || !q3.next()) {
        error = q3.lastError().text();
        m_lastError = error;
        return -1;
    }

    return q3.value(0).toInt();
}

bool UserCrud::updateUser(const UserData &user, QString &error)
{
    if (user.id <= 0) {
        error = "ID utilisateur invalide";
        m_lastError = error;
        return false;
    }
    
    ValidationResult validation = validateUser(user);
    if (!validation.isValid) {
        error = validation.errorMessage;
        m_lastError = error;
        return false;
    }
    
    QSqlQuery query;
    query.prepare("UPDATE USERS SET NOM=:nom, PRENOM=:prenom, TEL=:tel, MAIL=:mail, "
                  "MDP=:mdp, SALAIRE=:salaire, ROLE=:role, ETAT=:etat WHERE ID_USER=:id");

    query.bindValue(":id", user.id);
    query.bindValue(":nom", user.nom.trimmed());
    query.bindValue(":prenom", user.prenom.trimmed());
    query.bindValue(":tel", user.tel.trimmed());
    query.bindValue(":mail", user.mail.trimmed());
    query.bindValue(":mdp", user.mdp);
    query.bindValue(":salaire", user.salaire.toDouble());
    query.bindValue(":role", user.role);
    query.bindValue(":etat", user.etat);
    
    if (executeQuery(query)) {
        qDebug() << "User updated successfully";
        return true;
    }
    error = m_lastError;
    return false;
}

bool UserCrud::deleteUser(int id, QString &error)
{
    if (id <= 0) {
        error = "ID utilisateur invalide";
        m_lastError = error;
        return false;
    }
    
    QSqlQuery query;
    query.prepare("DELETE FROM USERS WHERE ID_USER=:id");
    query.bindValue(":id", id);
    
    if (executeQuery(query)) {
        qDebug() << "User deleted successfully";
        return true;
    }
    error = m_lastError;
    return false;
}

QList<UserData> UserCrud::getAllUsers()
{
    QList<UserData> userList;
    QSqlQuery query("SELECT ID_USER, NOM, PRENOM, TEL, MAIL, MDP, SALAIRE, ROLE, ETAT FROM USERS");
    
    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error retrieving users:" << m_lastError;
        return userList;
    }
    
    while (query.next()) {
        UserData user;
        user.id = query.value(0).toInt();
        user.nom = query.value(1).toString();
        user.prenom = query.value(2).toString();
        user.tel = query.value(3).toString();
        user.mail = query.value(4).toString();
        user.mdp = query.value(5).toString();
        user.salaire = query.value(6).toString();
        user.role = query.value(7).toString();
        user.etat = query.value(8).toString();
        
        userList.append(user);
    }
    
    qDebug() << "Retrieved" << userList.size() << "users";
    return userList;
}

QList<UserData> UserCrud::searchUsers(const QString &searchText)
{
    QList<UserData> userList;
    
    if (searchText.trimmed().isEmpty()) {
        return getAllUsers();
    }
    
    QSqlQuery query;
    query.prepare("SELECT ID_USER, NOM, PRENOM, TEL, MAIL, MDP, SALAIRE, ROLE, ETAT FROM USERS "
                  "WHERE LOWER(NOM) LIKE :search OR LOWER(PRENOM) LIKE :search "
                  "OR LOWER(TEL) LIKE :search OR LOWER(MAIL) LIKE :search");
    
    QString searchPattern = "%" + searchText.toLower() + "%";
    query.bindValue(":search", searchPattern);
    
    if (query.exec()) {
        while (query.next()) {
            UserData user;
            user.id = query.value(0).toInt();
            user.nom = query.value(1).toString();
            user.prenom = query.value(2).toString();
            user.tel = query.value(3).toString();
            user.mail = query.value(4).toString();
            user.mdp = query.value(5).toString();
            user.salaire = query.value(6).toString();
            user.role = query.value(7).toString();
            user.etat = query.value(8).toString();
            
            userList.append(user);
        }
    } else {
        m_lastError = query.lastError().text();
        qDebug() << "Search query error:" << m_lastError;
    }
    
    return userList;
}

UserData UserCrud::getUserById(int id)
{
    UserData user;
    
    if (id <= 0) {
        m_lastError = "ID utilisateur invalide";
        return user;
    }
    
    QSqlQuery query;
    query.prepare("SELECT ID_USER, NOM, PRENOM, TEL, MAIL, MDP, SALAIRE, ROLE, ETAT FROM USERS WHERE ID_USER=:id");
    query.bindValue(":id", id);
    
    if (query.exec() && query.next()) {
        user.id = query.value(0).toInt();
        user.nom = query.value(1).toString();
        user.prenom = query.value(2).toString();
        user.tel = query.value(3).toString();
        user.mail = query.value(4).toString();
        user.mdp = query.value(5).toString();
        user.salaire = query.value(6).toString();
        user.role = query.value(7).toString();
        user.etat = query.value(8).toString();
    } else {
        m_lastError = "Utilisateur non trouvé ou erreur: " + query.lastError().text();
        qDebug() << m_lastError;
    }
    
    return user;
}
