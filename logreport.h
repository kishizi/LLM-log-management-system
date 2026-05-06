#ifndef LOGREPORT_H
#define LOGREPORT_H

#include <QWidget>

namespace Ui {
class LogReport;
}

class LogReport : public QWidget
{
    Q_OBJECT

public:
    explicit LogReport(QWidget *parent = nullptr);
    ~LogReport();

public: signals:
    void exportModelToCsv(const QString &name);


public slots:
   void fd_bt_set_enabled(const QString &name);

private slots:
    void on_export_button_clicked();



private:
    Ui::LogReport *ui;
    QString _tbname;
};

#endif // LOGREPORT_H
