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
    ~itemform();

private:
    Ui::itemform *ui;
};

#endif // ITEMFORM_H
