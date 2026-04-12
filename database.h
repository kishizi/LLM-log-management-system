#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableView>
#include <QSqlTableModel>

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

signals:
    void showList(const QStringList &list);


private slots:

    void on_find_clicked();

    void on_add_clicked();

public slots:
    void TbListBt_handle();

private:
    Ui::DataBase *ui;
    QSqlDatabase db;
    //QSqlTableModel *model = new QSqlTableModel(this,db);
    QSqlTableModel *model;

    //申明为成员变量会崩溃？？
    //QSqlQuery query;
};
#endif // DATABASE_H
