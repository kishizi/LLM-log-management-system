#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QtHttpServer/QHttpServer>
#include "ollamacilent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , oc(new ollamacilent)
    //, dbm(new DataBase)
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
    connect(this,&MainWindow::TbListBt_show_tables,ui->TbList,&DataBase::TbListBt_handle);
    connect(ui->TbList,&DataBase::showList,this,&MainWindow::showList);

    //abouttoshow式切换
    //connect(ui->menu_db,&QMenu::aboutToShow,this,&MainWindow::handstackchange_db);
    connect(oc,&ollamacilent::resultReady, this,&MainWindow::handleresult);





    //qDebug() << QSqlDatabase::drivers();
    //ollamacilent client;
    //oc->generate("鲁迅是谁");

    //this->setCentralWidget(new QStackedWidget);
}

MainWindow::~MainWindow()
{
    delete oc;
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

//声明itemform实例放入QListWidget
void MainWindow::showList(const QStringList &list)
{
    ui->listWidget->clear();
    int i = 0;

    for (const QString &name :list)  {
        itemform* staffItem = new itemform;
        staffItem->setStaffInfo(name);

        QListWidgetItem* item = new QListWidgetItem;

        //item->setSizeHint(QSize(150,50));
        item->setSizeHint(staffItem->size());
        item->setData(Qt::UserRole,i);
        //item->setSizeHint(staffItem->sizeHint());


        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,staffItem);

        //item没有信号，靠listwidget
        //connect(item,&QListWidgetItem::isSelected,)
        i++;
    }

}

//设置界面为大模型问答界面
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

//输出当前连接数据库的所有表，后续选择来确定模型绑定哪个表来操作
void MainWindow::on_TbListBt_clicked()
{
    emit TbListBt_show_tables();

}

