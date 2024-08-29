#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantMap> // Include for QVariantMap
#include <QList>       // Include for QList
#define SUCCESS 1
#define FAIL 0
class DataManage : public QObject
{
    Q_OBJECT
public:
    static DataManage *getInstance();

    explicit DataManage(QObject *parent = nullptr);
    void init();

    QSqlDatabase getDatabase() const;
    void addSampleHouses();

    // Chat related methods
    bool addChatMessage(const QString &sender, const QString &receiver, const QString &message);
    QList<QVariantMap> getChatMessages(const QString &user1, const QString &user2);

private:
    static DataManage* g_dataManage;
    QSqlDatabase db;
public:
    void initDataBase();
    void initHouseDataBase();
    void initConfig();
    void initChatDataBase();  // New method for initializing chat database
    bool addRecordDB(QString username, QString password, QString resetcode, QString firstname, QString lastname, QString email, QString phonenumber);
    bool addHouseDB(QString address, int numBathrooms, int numBedrooms, int rentPerPerson, QString landlord); //Instead of landlord as a string, should have a landlord object?
signals:

};

#endif // DATAMANAGE_H
