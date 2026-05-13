#include "database.h"
#include "ui_database.h"
#include "ui_mainwindow.h"
#include <QSqlIndex>

DataBase::DataBase(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataBase)
    //, model(new QSqlTableModel(this,db))
{
    ui->setupUi(this);

    //快捷方式触发
    //refresh
    QShortcut *shortcut1 = new QShortcut(QKeySequence("space"), this);
    connect(shortcut1, &QShortcut::activated, ui->refresh, &QPushButton::click);
    //find
    QShortcut *shortcut2 = new QShortcut(QKeySequence("F"), this);
    connect(shortcut2, &QShortcut::activated, ui->find, &QPushButton::click);




    //初始创建表的语句
    //QSqlQuery query;
    //query.exec("CREATE TABLE IF NOT EXISTS person (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER)");


}

DataBase::~DataBase()
{
    model->clear();
    delete model;
    delete ui;

    db.close();

    db = QSqlDatabase();   // 赋值为无效数据库对象

    QSqlDatabase::removeDatabase("main_conn");


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
    // 删除当前选中行
    int curRow = ui->tableView->currentIndex().row();
    model->removeRow(curRow);
    model->submitAll(); // 若策略为 OnManualSubmit 则需调用
}

void DataBase::model_operate_db()
{

}

void DataBase::model_analyse_db()
{

}
//导出数据库文件
void DataBase::exportModelToCsv(const QString &name)
{
    qDebug()<<"导出数据库csv文件";


    QString filePath = QFileDialog::getSaveFileName(this, "导出 CSV", "", "CSV 文件 (*.csv)");
    if (filePath.isEmpty()) return;
    if (!filePath.endsWith(".csv", Qt::CaseInsensitive))
        filePath += ".csv";

    //QFuture<void> future = QtConcurrent::run(startExport,filePath);


    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this, [this, watcher]() {
        QMessageBox::information(this, "导出", "文件写入完成！");
        watcher->deleteLater();
    });


    QFuture<void> future = QtConcurrent::run(&DataBase::startExport, this, filePath, name, m_type,m_database);


    watcher->setFuture(future);
}



//线程不处理gui操作，线程中仅处理写入数据
void DataBase::startExport(const QString &filePath,const QString &tbname,const QString &type,const QString &databasename)
{
    //tbname为传入的选中表列参数
    qDebug()<<"startExport:"<<"线程进入成功";

    //设置新的数据库连接
    //to do.....
    //QSqlDatabase Ex_db = QSqlDatabase::addDatabase("QSQLITE","export_conn");
    qDebug()<<"打印数据库名和连接类型："<<databasename<<type;

    QSqlDatabase Ex_db = QSqlDatabase::addDatabase(type,"export_conn");
    if(type == "QSQLITE")
    {

        Ex_db.setDatabaseName(databasename);
    }
    if(type == "QMYSQL")
    {
        Ex_db.setHostName(m_hostname);
        Ex_db.setPort(m_port.toInt());
        Ex_db.setDatabaseName(databasename);
        Ex_db.setUserName(m_username);
        Ex_db.setPassword(m_password);

    }

    if(!Ex_db.open())
    {
        qDebug() << "导出线程数据库打开失败";
        qDebug()<< "open error"<<db.lastError().text();
        QSqlDatabase::removeDatabase("export_conn");  // 退出前清理

        return;
    }

    //保证退出时删除连接
    auto cleanup = [&]() {
        Ex_db.close();
        QSqlDatabase::removeDatabase("export_conn");
    };

    //QSqlTableModel *Ex_model = new QSqlTableModel(nullptr,Ex_db);
    std::unique_ptr<QSqlTableModel> Ex_model(new QSqlTableModel(nullptr, Ex_db));
    Ex_model->setTable(tbname);

    Ex_model->select();
    while (Ex_model->canFetchMore()) {
        Ex_model->fetchMore();
    }

    QFile file(filePath);
    qDebug()<<filePath;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 打开失败处理……
        qDebug()<<"文件创建失败";
        return;
    }

    QTextStream out(&file);

    //out.setCodec("UTF-8"); // 设置编码

    qDebug()<<"startExport:"<<tbname<<"QTextStream out 设置成功";
    // 写入表头
    QStringList headers;
    for (int col = 0; col < Ex_model->columnCount(); ++col) {
        headers << Ex_model->headerData(col, Qt::Horizontal).toString();
    }
    out << headers.join(",") << "\n";

    // 一次性遍历所有行
    for (int row = 0; row < Ex_model->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < Ex_model->columnCount(); ++col) {
            QString cell = Ex_model->data(Ex_model->index(row, col)).toString();
            // 简单处理 CSV 里的特殊字符
            cell.replace("\"", "\"\"");
            if (cell.contains(",") || cell.contains("\"") || cell.contains("\n"))
                cell = "\"" + cell + "\"";
            rowData << cell;
        }
        out << rowData.join(",") << "\n";
    }


    file.close();  // 收尾

    Ex_model.reset();
}

void DataBase::warnning(const QString &text)
{
    //失败后弹出失败信息对话框
    WarningDialog *dlg = new WarningDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
    dlg->setWindowTitle("提示");
    dlg->settext(text);
    dlg->exec();
}

void DataBase::loaddata()
{
    const int rows = 200;//一批次固定200行
    const int cols = model->columnCount();

    for (int col = 0; col < cols; ++col) {
        m_dataheader << model->headerData(col, Qt::Horizontal).toString();
    }


    // 工作线程中
    /*QStringList batchList;
    for (const auto& row : batchRows) {
        batchList << formatLog(row); // 格式化为 "[时间] [级别] 消息"
    }
    QString prompt = batchList.join("\n"); // 拼接成一个多行字符串

    // 然后调用发送函数
    sendToOllama(prompt);*/

}



void DataBase::on_find_clicked()
{

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



//往最下方加一行数据
void DataBase::on_add_clicked()
{
    int row = model->rowCount();  // 末尾插入
    model->insertRow(row);

    model->submitAll();

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

//激活find按钮
void DataBase::set_find_ennable(const QString &name)
{
    model->setTable(name);
    ui->find->setEnabled(true);

    //选择好表名后，数据导出页面按钮激活，传递表名参数
    emit logreport_fd_bt_enabled(name);
}

void DataBase::sqlite_connect(const QString &type,const QString &databasename)
{
    //sqlite数据库连接
     db = QSqlDatabase::addDatabase(type,"main_conn");
     db.setDatabaseName(databasename);

     if(!db.open())
     {
         qDebug()<< "open error"<<db.lastError().text();

         //失败后弹出失败信息对话框
         warnning(db.lastError().text());

     }
     else
     {

         //如果成功，传递信号给window切换页面
         //to do....
         m_type = "QSQLITE";
         m_database = databasename;
         emit db_open_success();
     }

      //设置ui显示type类型
     ui->label_type->setText(m_type);

    model = new QSqlTableModel(this,db);

}

void DataBase::mysql_connect(const QString &type,const QString &hostname,const QString &port,
                             const QString &databasename,const QString &username,const QString &password)
{

    qDebug()<<type<<hostname<<port.toInt()<<databasename<<username<<password;




    //mysql数据库连接
    db = QSqlDatabase::addDatabase(type,"main_conn");
    db.setHostName(hostname);
    db.setPort(port.toInt());
    db.setDatabaseName(databasename);
    db.setUserName(username);
    db.setPassword(password);


    if(!db.open())
    {
        qDebug()<< "open error"<<db.lastError().text();

        //失败后弹出失败信息对话框
         warnning(db.lastError().text());
    }
    else
    {
        //如果成功，传递信号给window切换页面
        //to do....
         //设置database全局变量
        m_type = "QMYSQL";
        m_database = databasename;
        m_hostname = hostname;
        m_port = port;
        m_username = username;
        m_password = password;
        emit db_open_success();

    }

    //设置ui显示type类型
     ui->label_type->setText(m_type);


    model = new QSqlTableModel(this,db);
}


void DataBase::on_remove_clicked()
{
    // 删除当前选中行
    int curRow = ui->tableView->currentIndex().row();
    model->removeRow(curRow);
    model->submitAll(); // 若策略为 OnManualSubmit 则需调用

}


void DataBase::on_refresh_clicked()
{
    model->submitAll();
    model->select();

    ui->tableView->show();

}

