#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableView>
#include <QSqlTableModel>
#include <QFile>
#include <QDialog>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrentRun>
#include <QtConcurrent/QtConcurrent>
#include <QTextStream>
#include <QtConcurrent>
#include <QMessageBox>
#include <QShortcut>

namespace Ui {
class DataBase;
}

class DataBase : public QWidget
{
    Q_OBJECT

public:
    explicit DataBase(QWidget *parent = nullptr);
    ~DataBase();
    void find();//查询查看数据库
    void add();//添加一条数据
    void delete_db();//删除一条数据

    void model_operate_db();//大模型使用sql语句对数据库进行操作
    void model_analyse_db();//大模型分析报告
    void exportModelToCsv(const QString &name);//导出当前数据库文件
    void startExport(const QString &filePath, const QString &tbname, const QString &type, const QString &databasename);//放在exportModelToCsv()里

    void warnning(const QString &text);

    void loaddata();//读取数据


signals:
    void showList(const QStringList &list);

    void logreport_fd_bt_enabled(const QString &name);

    //void db_open_failed();//数据库打开失败
    void db_open_success();//数据库打开成功


private slots:

    void on_find_clicked();

    void on_add_clicked();

    void on_remove_clicked();

    void on_refresh_clicked();

public slots:
    void TbListBt_handle();

    void set_find_ennable(const QString &name);

    void sqlite_connect(const QString &type,const QString &databasename);


    void mysql_connect(const QString &type,const QString &hostname,const QString &port,
                       const QString &databasename,const QString &username,const QString &password);

private:

    //QString data;//存储
    QStringList m_datalist;//单批处理数据
    QStringList m_dataheader;

    QString m_type;//连接类型
    QString m_database;//数据库名
    QString m_hostname;//ip地址
    QString m_port;//端口号
    QString m_username;//用户名
    QString m_password;//密码

    QSqlDatabase db;


    Ui::DataBase *ui;
    QSqlTableModel *model;



    //QSqlTableModel *model = new QSqlTableModel(this,db);


    //申明为成员变量会崩溃？？
    //QSqlQuery query;
};
#endif // DATABASE_H
