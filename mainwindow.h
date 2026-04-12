#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "ollamacilent.h"
#include <QStackedWidget>
#include "itemform.h"

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

public slots:
    void showList(const QStringList &list);

signals:
    void TbListBt_show_tables();

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
