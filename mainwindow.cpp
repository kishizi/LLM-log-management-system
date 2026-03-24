#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QtHttpServer/QHttpServer>
#include "ollamacilent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , oc(new ollamacilent)
{
    ui->setupUi(this);

    connect(oc,&ollamacilent::resultReady, this,&MainWindow::handleresult);

    //qDebug() << QSqlDatabase::drivers();
    //ollamacilent client;
    //oc->generate("鲁迅是谁");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleresult(const QString &result)
{
    qDebug()<<"sucess/n";
    ui->Tx->setText(result);
}

void MainWindow::on_Tx_textChanged()
{

}

//文本发出确认按钮
void MainWindow::on_TxaB_clicked()
{
    QString txt = ui->Txa->toPlainText();
    oc->generate(txt);
    ui->Txa->setText("");
}

