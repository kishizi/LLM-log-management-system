#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include "ollamacilent.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //QCoreApplication a(argc, argv);

    MainWindow w;
    w.show();

    //命令行打印qt支持数据库驱动
    //qDebug()<<"Sql available drives::"<< QSqlDatabase::drivers();


    //ollamacilent client;
    //client.generate("ollama");


    // db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("log.db");

    // db.close();
    // db.removeDatabase("log.db");
    // if(!db.open())
    // {
    //     qDebug()<< "open error"<<db.lastError().text();
    //     return -1;
    // }

    return a.exec();

}
