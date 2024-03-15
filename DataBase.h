#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

#include <QObject>
#include <QDebug>

class MyDataBase : public QObject {
    Q_OBJECT

public:
    explicit MyDataBase(QObject * parent = 0);
    Q_INVOKABLE bool insertItemDataBase(QString mytext);
    Q_INVOKABLE QString getItemDataBase(int id_item);
    Q_INVOKABLE bool deleteItemDataBase(int index_item);
    static void clearDataBase();
    Q_INVOKABLE int countRowDataBase();

    static void connectDataBase();
    static void initDataBase();

};

#endif // DATABASE_H
