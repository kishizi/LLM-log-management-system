#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include "ollamacilent.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    QCoreApplication a(argc, argv);
    ollamacilent client;
    client.generate("ollama");
    return a.exec();

}
