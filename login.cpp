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

//自己输入信息的方式打开mysql或是sqlite数据库
void Login::on_bt_ok_clicked()
{

    qDebug()<<"login当前index"<<ui->stackedWidget->currentIndex();

    //打开mysql数据库
    if(ui->stackedWidget->currentIndex() == 1)
    {
        QString hn = ui->lineEdit_hostname->text();
        QString port =ui->lineEdit_port->text();
        QString dbn =ui->lineEdit_DataBaseName->text();
        QString un =ui->lineEdit_username->text();
        QString pw =ui->lineEdit_password->text();
        emit mysql_connect("QMYSQL",hn,port,dbn,un,pw);

        //触发返回信息输入错误的对话框
        //mysql用


        /*connect(this->parent()->parent()->findChild<DataBase*>("TbList"), &DataBase::db_open_failed, this, [this]()
                {
                    WarningDialog *dlg = new WarningDialog(this);
                    dlg->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
                    dlg->setWindowTitle("提示");
                    dlg->exec();
                });*/

    }
    //打开sqlite数据库
    if(ui->stackedWidget->currentIndex() == 2)
    {
        QString dbn =ui->lineEdit_sqlite_databasename->text();
        emit sqlite_connect("QSQLITE",dbn);
    }
}

//文件夹选择方式打开本地sqlite数据库
void Login::on_getfilename_Button_clicked()
{
    QString dbFilePath = QFileDialog::getOpenFileName(
        this,                   // 父窗口指针
        "打开数据库文件",       // 对话框标题
        QString(),              // 初始打开的目录，为空则默认
        "SQLite 数据库文件 (*.db)" // 文件过滤器
        );

    // 如果用户取消了选择（路径为空），则直接返回
    if (dbFilePath.isEmpty()) {
        qDebug() << "用户取消了选择";
        return;
    }

    emit sqlite_connect("QSQLITE",dbFilePath);
}

