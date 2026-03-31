//ollama客户端，大模型api接入
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
    //void generate(const QString &prompt, const QString &model = "llama2");
    void generate(const QString &prompt, const QString &model = "qwen3.5:2b");
    void onFinished();
    //QString result(){return result;}

signals:
    void resultReady(const QString &result);

private:
    QNetworkAccessManager* manager;
    QString result;

};

#endif // OLLAMACILENT_H
