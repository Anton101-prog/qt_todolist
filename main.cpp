#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "DataBase.h"
#include "ListModel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    MyDataBase database;
    database.connectDataBase();

    ListModel * model = new ListModel();

    engine.rootContext()->setContextProperty("myModel", model);
    engine.rootContext()->setContextProperty("database", &database);

    engine.load(QUrl(QString(QStringLiteral("qrc:/main.qml"))));


    return app.exec();
}
