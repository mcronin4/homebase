#include "datamanage.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QApplication>
#include <QDebug>
#define SQLITE
DataManage *DataManage::g_dataManage = new DataManage();
DataManage * DataManage::getInstance()
{
    // get instance
    return g_dataManage;
}
DataManage::DataManage(QObject *parent)
    : QObject{parent}
{
}

void DataManage::init()
{
    initConfig();
    initDataBase();
    initHouseDataBase();
    initChatDataBase(); // Initialize the chat database

}

void DataManage::initConfig()
{

}


void DataManage::initDataBase()
{
#ifdef SQLITE
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.setHostName("localhost");
    db.setPort(3306);
#endif
    if(!db.open())
    {
        qDebug() << "connect db fail; " <<  db.lastError();
        return;
    }
    QStringList dbtables = db.tables();
    QSqlQuery sqlQuery(db);
    if (!dbtables.contains("AccountInfo")) {
        QString alarm = "CREATE TABLE AccountInfo ('id'INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "'username' TEXT,"
                        "'password' TEXT, "
                        "'resetcode' TEXT,"
                        "'firstname' TEXT,"
                        "'lastname' TEXT,"
                        "'email' TEXT,"
                        "'phonenumber' TEXT);";
        if (!sqlQuery.exec(alarm)) {
            qWarning() << sqlQuery.lastError();
        }
    }
}

void DataManage::initHouseDataBase() {
#ifdef SQLITE
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.setHostName("localhost");
    db.setPort(3306);
#endif
    if(!db.open())
    {
        qDebug() << "connect db fail; " <<  db.lastError();
        return;
    }
    QStringList dbtables = db.tables();
    QSqlQuery sqlQuery(db);

    if (!dbtables.contains("HousesInfo")) {
        QString alarm = "CREATE TABLE HousesInfo ('id'INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                        "'address' TEXT,"
                        "'numBathrooms' INT, "
                        "'numBedrooms' INT,"
                        "'rentPerPerson' INT"
                        "'landlord' TEXT,"
                        "'photo' LONGBLOB,";
        if (!sqlQuery.exec(alarm)) {
            qWarning() << sqlQuery.lastError();
        }
    }
}

void DataManage::initChatDataBase() {
#ifdef SQLITE
    if (!db.isOpen()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("data.db");
        db.setHostName("localhost");
        db.setPort(3306);
        if (!db.open()) {
            qDebug() << "connect db fail; " << db.lastError();
            return;
        }
    }
#endif

    QStringList dbtables = db.tables();
    QSqlQuery sqlQuery(db);

    if (!dbtables.contains("ChatMessages")) {
        QString createChatTable = "CREATE TABLE ChatMessages ("
                                  "'id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                                  "'sender' TEXT, "
                                  "'receiver' TEXT, "
                                  "'message' TEXT, "
                                  "'timestamp' DATETIME DEFAULT CURRENT_TIMESTAMP);";
        if (!sqlQuery.exec(createChatTable)) {
            qWarning() << sqlQuery.lastError();
        }
    }
}

bool DataManage::addChatMessage(const QString &sender, const QString &receiver, const QString &message) {
    QSqlQuery sqlQuery;
    if (db.isOpen()) {
        bool res = sqlQuery.exec(QString("INSERT INTO ChatMessages (sender, receiver, message) "
                                         "VALUES ('%1', '%2', '%3')")
                                     .arg(sender, receiver, message));
        if (!res) {
            qWarning() << "Insert chat message:" << sqlQuery.lastError();
            return false;
        }
        return true;
    }
    return false;
}

QList<QVariantMap> DataManage::getChatMessages(const QString &user1, const QString &user2) {
    QList<QVariantMap> messages;
    QSqlQuery sqlQuery;
    if (db.isOpen()) {
        bool res = sqlQuery.exec(QString("SELECT * FROM ChatMessages WHERE "
                                         "(sender = '%1' AND receiver = '%2') OR "
                                         "(sender = '%2' AND receiver = '%1') "
                                         "ORDER BY timestamp")
                                     .arg(user1, user2));
        if (!res) {
            qWarning() << "Retrieve chat messages:" << sqlQuery.lastError();
        } else {
            while (sqlQuery.next()) {
                QVariantMap message;
                message["id"] = sqlQuery.value("id");
                message["sender"] = sqlQuery.value("sender");
                message["receiver"] = sqlQuery.value("receiver");
                message["message"] = sqlQuery.value("message");
                message["timestamp"] = sqlQuery.value("timestamp");
                messages.append(message);
            }
        }
    }
    return messages;
}

bool DataManage::addHouseDB(QString address, int numBathrooms, int numBedrooms, int rentPerPerson, QString landlord) {
    QSqlQuery sqlQuery;
    if(db.isOpen())
    {
        bool res = sqlQuery.exec(QString("INSERT INTO 'HousesInfo'"
                                         "('address', 'numBathrooms','numBedrooms','rentPerPerson','landlord') "
                                         " VALUES ('%1', '%2','%3','%4','%5');")
                                     .arg(address,QString::number(numBathrooms),QString::number(numBedrooms),QString::number(rentPerPerson),landlord));
        if(!res)
            qWarning() <<"insert record:" << sqlQuery.lastError();
        else
        {
            return true;
        }
    }
    return false;
}

bool DataManage::addRecordDB(QString username,QString password, QString resetcode ,QString firstname,QString lastname,QString email,QString phonenumber)
{
    QSqlQuery sqlQuery;
    if(db.isOpen())
    {
        bool res = sqlQuery.exec(QString("INSERT INTO 'AccountInfo'"
                                         "('username', 'password','resetcode','firstname','lastname','email','phonenumber') "
                                         " VALUES ('%1', '%2','%3','%4','%5','%6','%7');")
                                     .arg(username,password,resetcode,firstname,lastname,email,phonenumber));
        if(!res)
            qWarning() <<"insert record:" << sqlQuery.lastError();
        else
        {
            return true;
        }
    }
    return false;
}

QSqlDatabase DataManage::getDatabase() const {
    return db;
}

void DataManage::addSampleHouses() {
    addHouseDB("123 Main St", 1, 2, 500, "John Doe");
    addHouseDB("456 Elm St", 2, 3, 750, "Jane Smith");
}
