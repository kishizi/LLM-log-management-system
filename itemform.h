#ifndef ITEMFORM_H
#define ITEMFORM_H

#include <QMainWindow>

namespace Ui {
class itemform;
}

class itemform : public QMainWindow
{
    Q_OBJECT

public:
    explicit itemform(QWidget *parent = nullptr);


    //新测试，构造新加入一个item参数，方便对应操作
    //explicit MyWidget(QListWidgetItem *item, QWidget *parent = nullptr);

    ~itemform();

    void setStaffInfo(QString name);

signals:
    void selected(QVariant string);


private:
    Ui::itemform *ui;
};

#endif // ITEMFORM_H
