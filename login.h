#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();


 signals:
    void mysql_connect(const QString &type,const QString &hostname,const QString &port,
                        const QString &databasename,const QString &username,const QString &password);
    void sqlite_connect(const QString &type,const QString &databasename);


private slots:
    void on_connect_Sqllite_clicked();

    void on_connect_mysql_clicked();

    void on_bt_clear_clicked();

    void on_bt_ok_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
