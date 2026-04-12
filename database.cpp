#include "database.h"
#include "ui_database.h"
#include <QSqlIndex>

DataBase::DataBase(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataBase)
    //, model(new QSqlTableModel(this,db))
{
    ui->setupUi(this);


    //db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/test.db");
     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("log.db");

     //初始创建表的语句
     //QSqlQuery query;
     //query.exec("CREATE TABLE IF NOT EXISTS person (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER)");


    if(!db.open())
    {
        qDebug()<< "open error"<<db.lastError().text();

    }

    model = new QSqlTableModel(this,db);
    model->setTable("person");


}

DataBase::~DataBase()
{
    db.close();
    db.removeDatabase("log.db");

    delete ui;
    //db.close();
}

//tableview显示方法，qt封装
void DataBase::find()
{

}

void DataBase::add()
{



}

void DataBase::delete_db()
{

}

void DataBase::model_operate_db()
{

}

void DataBase::model_analyse_db()
{

}

void DataBase::on_find_clicked()
{
    //QSqlQuery query;
    //query.exec("CREATE TABLE IF NOT EXISTS person (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER)");


    //QSqlTableModel *model = new QSqlTableModel(this,db);
    //model->setTable("person");       // 添加表（设置表名）

    qDebug()<<"model: "<<model;

    //model->insertRowIntoTable(Q);

    model->setEditStrategy(QSqlTableModel::OnFieldChange); // 实时提交
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);  // 手动提交
    model->select();                 // 加载数据

    ui->tableView->setModel(model);

    //ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    ui->tableView->show();

    // 方法一：通过 insertRow() 插入空行，然后填充数据
    // int row = model->rowCount();  // 末尾插入
    // model->insertRow(row);
    // model->setData(model->index(row, 1), "张三");  // 假设第1列是name
    // model->setData(model->index(row, 2), 25);      // 第2列是age
    // model->submitAll();   // 提交到数据库

    // 方法二：使用 QSqlRecord 插入
    // QSqlRecord record = model->record();
    // record.setValue("name", "李四");
    // record.setValue("age", 30);
    // model->insertRecord(-1, record);   // -1 表示追加到末尾
    // model->submitAll();

}




void DataBase::on_add_clicked()
{
    //int row = model->rowCount();  // 末尾插入
    //model->insertRow(row);


}

void DataBase::TbListBt_handle()
{
    //qDebug()<<"TbList";
    //显示所有表，包括系统表和用户表
    QStringList tables = db.tables(QSql::AllTables);

    if(tables.isEmpty()) {
        qDebug()<<"当前数据库没有用户表";
    } else {
        qDebug() <<"找到以下表";
        for (const QString &table :tables)
            qDebug()<< table;
    }

    emit showList(tables);
}

