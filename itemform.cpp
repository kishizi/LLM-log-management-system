#include "itemform.h"
#include "ui_itemform.h"

itemform::itemform(QListWidgetItem *item,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::itemform)
    , m_item(item)
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

void itemform::mousePressEvent(QMouseEvent *event)
{
    if (m_item && m_item->listWidget()) {
        m_item->listWidget()->setCurrentItem(m_item);
    }

    //qDebug()<<"click";
    //this->setStyleSheet("background-color: lightblue;");

    // 发射数据
    if (m_item) {
        emit selected(m_item->data(Qt::UserRole));
    }
    QWidget::mousePressEvent(event); // 可选
}
