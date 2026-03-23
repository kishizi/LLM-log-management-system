#ifndef OLLAMACILENT_H
#define OLLAMACILENT_H

#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class ollamacilent : public QObject
{
    Q_OBJECT
public:
    explicit ollamacilent(QObject *parent = nullptr);
    void generate(const QString &prompt, const QString &model = "llama2");
    void onFinished();

signals:


private:
    QNetworkAccessManager* manager;

};

#endif // OLLAMACILENT_H
