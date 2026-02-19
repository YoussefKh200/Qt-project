#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("USERS_DB");//inserer le nom de la source de données
db.setUserName("USER2");//inserer nom de l'utilisateur
db.setPassword("pqsszord123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
