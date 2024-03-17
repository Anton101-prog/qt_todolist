#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

#include <QObject>
#include <QDebug>

#define DATABASE_HOSTNAME "NameDataBase"
#define DATABASE_NAME "mydatabase.db"


#define TABLE "NameTable"
#define TABLE_INFO "info"

class MyDataBase : public QObject {
    Q_OBJECT

private:
    QSqlDatabase db;

public:
    explicit MyDataBase(QObject * parent = 0);
    ~MyDataBase();

    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
    void connectDataBase();
    void initDataBase();


public slots:
    bool insertIntoTable (const QVariantList & data);
    bool insertIntoTable(const QString&text);
    bool removeRecord(const int id);

};

#endif // DATABASE_H
