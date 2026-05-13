#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "ollamacilent.h"
#include <QStackedWidget>
#include "itemform.h"
#include "logdataprocessing.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void handleresult(const QString &result);
    void handstackchange_api();
    void handstackchange_db();
    void handstackchange_log();

    void startNewLogDataProcessing();//创建一个新线程开始数据处理，同时日志到发送ollama
public slots:
    void showList(const QStringList &list);
    //列表选择后触发
    void selected_handle(const QVariant &name);

    void login_in();

signals:
    void TbListBt_show_tables();

    void set_find_enabled(const QString &name);

private slots:
    void on_Tx_textChanged();

    void on_TxaB_clicked();

    void on_TbListBt_clicked();



private:
    Ui::MainWindow *ui;
    ollamacilent *oc;
    //DataBase *dbm;
};
#endif // MAINWINDOW_H
