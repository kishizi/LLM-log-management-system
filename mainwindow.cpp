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

    //点击切换
    QAction *mapi = new QAction("mapi",this);
    ui->menubar->addAction(mapi);
    QAction *db = new QAction("db",this);
    ui->menubar->addAction(db);

    connect(ui->menu_api,&QMenu::aboutToShow,this,&MainWindow::handstackchange_api);
    connect(mapi,&QAction::triggered,this,&MainWindow::handstackchange_api);
    connect(db,&QAction::triggered,this,&MainWindow::handstackchange_db);

    //abouttoshow式切换
    //connect(ui->menu_db,&QMenu::aboutToShow,this,&MainWindow::handstackchange_db);
    //connect(oc,&ollamacilent::resultReady, this,&MainWindow::handleresult);





    //qDebug() << QSqlDatabase::drivers();
    //ollamacilent client;
    //oc->generate("鲁迅是谁");

    //this->setCentralWidget(new QStackedWidget);
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

void MainWindow::handstackchange_db()
{
    //qDebug()<<"cahnge_db";
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::handstackchange_api()
{
    //qDebug()<<"cahnge_api";
    ui->stackedWidget->setCurrentIndex(0);
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

