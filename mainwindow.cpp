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
    QAction *mapi = new QAction("大模型问答界面",this);
    ui->menubar->addAction(mapi);
    QAction *db = new QAction("数据库手动操作界面",this);
    ui->menubar->addAction(db);
    QAction *log = new QAction("日志生成界面",this);
    ui->menubar->addAction(log);



    //connect(ui->menu_api,&QMenu::aboutToShow,this,&MainWindow::handstackchange_api);
    connect(mapi,&QAction::triggered,this,&MainWindow::handstackchange_api);
    connect(db,&QAction::triggered,this,&MainWindow::handstackchange_db);
    connect(log,&QAction::triggered,this,&MainWindow::handstackchange_log);
    connect(this,&MainWindow::TbListBt_show_tables,ui->TbList,&DataBase::TbListBt_handle);
    connect(ui->TbList,&DataBase::showList,this,&MainWindow::showList);
    connect(this,&MainWindow::set_find_enabled,ui->TbList,&DataBase::set_find_ennable);
    //abouttoshow式切换
    //connect(ui->menu_db,&QMenu::aboutToShow,this,&MainWindow::handstackchange_db);
    connect(oc,&ollamacilent::resultReady, this,&MainWindow::handleresult);

    connect(ui->logreport_widget,&LogReport::exportModelToCsv,ui->TbList,&DataBase::exportModelToCsv);//导出数据库csv文件

    connect(ui->TbList,&DataBase::logreport_fd_bt_enabled,ui->logreport_widget,&LogReport::fd_bt_set_enabled);

    connect(ui->login_widget,&Login::mysql_connect,ui->TbList,&DataBase::mysql_connect);
    connect(ui->login_widget,&Login::sqlite_connect,ui->TbList,&DataBase::sqlite_connect);

    connect(ui->TbList,&DataBase::db_open_success,this,&MainWindow::login_in);
    //connect()





    qDebug() << QSqlDatabase::drivers();
    //ollamacilent client;
    //oc->generate("鲁迅是谁");

    //this->setCentralWidget(new QStackedWidget);
    ui->stackedWidget->setCurrentIndex(3);//默认设置登陆界面
    ui->statusbar->hide();
    ui->menubar->hide();
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

void MainWindow::handstackchange_log()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//日志处理发送线程
void MainWindow::startNewLogDataProcessing()
{
    QThread *thread = new QThread(this);
    LogdataProcessing *worker = new LogdataProcessing();
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &LogdataProcessing::dowork);
    connect(worker, &LogdataProcessing::progressUpdated, this, [this](int v) { });
    connect(worker, &LogdataProcessing::workFinished, thread, &QThread::quit);
    connect(worker, &LogdataProcessing::workFinished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}


//声明itemform实例放入QListWidget
void MainWindow::showList(const QStringList &list)
{
    ui->listWidget->clear();
    //int i = 0;

    for (const QString &name :list)  {
        //itemform* staffItem = new itemform;
        //staffItem->setStaffInfo(name);

        QListWidgetItem* item = new QListWidgetItem;


        item->setData(Qt::UserRole,name);


        itemform* staffItem = new itemform(item);
        connect(staffItem,&itemform::selected,this,&MainWindow::selected_handle);

        staffItem->setStaffInfo(name);

        item->setSizeHint(staffItem->size());

        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,staffItem);

        //connect(staffItem,&itemform::selected,this,&MainWindow::selected_handle);

        //item没有信号，靠listwidget
        //connect(item,&QListWidgetItem::isSelected,)
    }

}

//表列项被选择中触发
void MainWindow::selected_handle(const QVariant& name)
{
    //qDebug()<<name;

    if (!name.isValid()) {
        qDebug() << "无效的 QVariant";
        return;
    }

    // 检查能否转为 QString
    QString str;
    if (name.canConvert<QString>()) {
        str = name.value<QString>();
        //qDebug() << "成功提取字符串:" << str;
    } else {
        qDebug() << "无法转换为 QString，当前类型为:" << name.metaType().name();
    }

    qDebug()<<str;

    //传给

    //传给database,传递选择名字，激活按钮
    emit set_find_enabled(str);
}

void MainWindow::login_in()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->statusbar->show();
    ui->menubar->show();
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

