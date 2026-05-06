#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
}

Login::~Login()
{
    delete ui;
}

void Login::on_connect_Sqllite_clicked()
{
    //sqlite数据库连接
    /*db = QSqlDatabase::addDatabase("QSQLITE","main_conn");
     db.setDatabaseName("log.db");*/
    //emit sqlite_connect();
    ui->stackedWidget->setCurrentIndex(2);
}


void Login::on_connect_mysql_clicked()
{
    //mysql数据库连接
    /*db = QSqlDatabase::addDatabase("QMYSQL","main_conn");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("log");
    db.setUserName("root");
    db.setPassword("wrq3108622478.");*/
    ui->stackedWidget->setCurrentIndex(1);
    //QString databasename = "log";
    //emit sqlite_connect("QSQLITE",databasename);
}


void Login::on_bt_clear_clicked()
{

}


void Login::on_bt_ok_clicked()
{
    if(ui->stackedWidget->currentIndex() == 1)
    {
        QString hn = ui->lineEdit_hostname->text();
        QString port =ui->lineEdit_port->text();
        QString dbn =ui->lineEdit_DataBaseName->text();
        QString un =ui->lineEdit_username->text();
        QString pw =ui->lineEdit_password->text();
        emit mysql_connect("QSMYSQL",hn,port,dbn,un,pw);

    }
    if(ui->stackedWidget->currentIndex() == 2)
    {
        QString dbn =ui->lineEdit_sqlite_databasename->text();
        emit sqlite_connect("QSQLITE",dbn);
    }
}

