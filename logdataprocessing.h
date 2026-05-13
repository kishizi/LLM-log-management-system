#ifndef LOGDATAPROCESSING_H
#define LOGDATAPROCESSING_H

#include <QObject>

class LogdataProcessing : public QObject
{
    Q_OBJECT
public:
    explicit LogdataProcessing(QObject *parent = nullptr);

public slots:
    void dowork();

signals:
    void progressUpdated(int percent);  // 把进度发给主线程
    void workFinished();

signals:
};

#endif // LOGDATAPROCESSING_H
