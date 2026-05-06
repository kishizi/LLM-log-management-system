#ifndef ITEMFORM_H
#define ITEMFORM_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class itemform;
}

class itemform : public QMainWindow
{
    Q_OBJECT

public:
    //explicit itemform(QWidget *parent = nullptr);


    //新测试，构造新加入一个item参数，方便对应操作
    explicit itemform(QListWidgetItem *item, QWidget *parent = nullptr);

    ~itemform();

    void setStaffInfo(QString name);

signals:
    void selected(const QVariant &name);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::itemform *ui;
    QListWidgetItem *m_item;
};

#endif // ITEMFORM_H
