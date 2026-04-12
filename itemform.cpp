#include "itemform.h"
#include "ui_itemform.h"

itemform::itemform(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::itemform)
{
    ui->setupUi(this);
}

itemform::~itemform()
{
    delete ui;
}

void itemform::setStaffInfo(QString name)
{
    ui->name_label->setText(name);
}
