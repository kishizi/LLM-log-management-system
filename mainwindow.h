#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ollamacilent.h"
#include <QStackedWidget>

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

private slots:
    void on_Tx_textChanged();

    void on_TxaB_clicked();

private:
    Ui::MainWindow *ui;
    ollamacilent *oc;
};
#endif // MAINWINDOW_H
