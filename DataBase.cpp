#include "DataBase.h"
#include <QFile>
#include <QCoreApplication>
MyDataBase::MyDataBase(QObject * parent) : QObject(parent) {
}

MyDataBase::~MyDataBase() {

}

void MyDataBase::connectDataBase(){
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    dbPath.append(DATABASE_NAME);
    // dbPath.append(DATABASE_NAME);
    if (!QFile(dbPath).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool MyDataBase::restoreDataBase(){
    if (this->openDataBase()){
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool MyDataBase::openDataBase(){
    const QString DRIVER("QSQLITE");
    db = db.addDatabase(DRIVER);
    db.setHostName(DATABASE_HOSTNAME);

    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    db.setDatabaseName(dbPath + DATABASE_NAME);




    if (db.open()){
        return true;
    } else {
        return false;
    }

}

void MyDataBase::closeDataBase(){
    db.close();
}

bool MyDataBase::createTable() {
    QSqlQuery query;

    if (!query.exec("CREATE TABLE " TABLE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_INFO " TEXT "
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


bool MyDataBase::insertIntoTable(const QVariantList& data) {
    QSqlQuery query;

    query.prepare("INSERT INTO " TABLE " ( " TABLE_INFO " )"
                  "VALUES (:info)");
    query.bindValue(":info", data[0].toString());

    if (!query.exec()){
        qDebug() << "error insert ino " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool MyDataBase::insertIntoTable(const QString & text) {
    QVariantList data;
    data.append(text);

    if (insertIntoTable(data)){
        return true;
    } else {
        return false;
    }
}

bool MyDataBase::removeRecord(const int id){
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE " WHERE id= :ID ;");
    query.bindValue(":ID", id);

    if (!query.exec()){
        qDebug() << "error delete row " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

// bool MyDataBase::insertItemDataBase(QString myText)
// {
//     QSqlQuery query;

//     if(!query.exec("INSERT INTO mytable(info) VALUES('" + myText + "')")) {
//         qWarning() << "InsertItemDataBase error: " << query.lastError().text();
//         return false;

//     } else {
//         return true;
//     }
// }

// QString MyDataBase::getItemDataBase(int id_item)
// {
//     // в дальшейшем вместо Qstring нужно будет использовать QVariantMap
//     QSqlQuery query;

//     query.prepare("SELECT info FROM mytable WHERE id = :id");
//     query.bindValue(":id", id_item+1); // в SQL индексация начинается
//     // с 1, поэтому добавляем 1

//     if (query.exec() && query.first()){
//         QString info = query.value("info").toString();

//         return info;
//     } else {
//         qWarning() << "getItemDataBase error: " << query.lastError().text();
//         return QString();
//     }
// }

// bool MyDataBase::deleteItemDataBase(int index_item)
// {
//     ; // реализовать позже
//     return 0;
// }

// void MyDataBase::clearDataBase()
// {
//     QSqlQuery query("DELETE FROM mytable");

//     if(!query.isActive())
//         qWarning() << "clearDataBase error: " << query.lastError().text();

// }

// int MyDataBase::countRowDataBase() {
//     QSqlQuery query;
//     query.prepare("SELECT COUNT(*) FROM mytable");
//     if(!query.exec())
//         return -1; // в случае ошибки выполнения запроса

//     if(query.next()){
//         return query.value(0).toInt(); // получаем значение количества строк
//     }

//     return 0; // в случае неудачного запроса
// }

// void MyDataBase::connectDataBase() {
//     const QString DRIVER("QSQLITE");
//     // if(QSqlDatabase::isDriverAvailable(DRIVER))
//     // {
//     //     QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

//     //     db.setDatabaseName(":memory:"); // поменять не на оперативную память

//     //     if(!db.open())
//     //         qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
//     // }
//     if(QSqlDatabase::isDriverAvailable(DRIVER))
//     {
//         QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

//         QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

//         dbPath.append("/mydatabase.db");

//         db.setDatabaseName(dbPath);

//         if(!db.open())
//             qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
//     }
//     else
//         qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";

// }

// void MyDataBase::initDataBase(){
//     QSqlQuery query("CREATE TABLE mytable (id INTEGER PRIMARY KEY, info TEXT)");
//     if (!query.isActive()){
//         qWarning() << "initDataBase error: " << query.lastError().text();
//     }
// }
