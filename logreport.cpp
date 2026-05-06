#include "logreport.h"
#include "ui_logreport.h"

LogReport::LogReport(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogReport)
{
    ui->setupUi(this);
}

LogReport::~LogReport()
{
    delete ui;
}

void LogReport::on_export_button_clicked()
{
    //logreport_fd_bt_enabled(const QString &name)

    emit exportModelToCsv(_tbname);
}

void LogReport::fd_bt_set_enabled(const QString &name)
{
    ui->tb_label->setText("当前选择项："+name);
    _tbname = name;
    ui->export_button->setEnabled(true);

    //_tbname = name;
}

