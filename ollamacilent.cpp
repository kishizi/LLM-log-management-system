#include "ollamacilent.h"
#include "QNetworkAccessManager"

ollamacilent::ollamacilent(QObject *parent)
    : QObject{parent}
    , manager{new QNetworkAccessManager}
{


}

void ollamacilent::generate(const QString &prompt, const QString &model)
{
    // 构建请求URL（默认Ollama地址）
    QUrl url("http://localhost:11434/api/generate");
    //QUrl url("http://localhost:11434/api/chat");
    //QUrl url("https://ollama.com/api");
    //QUrl url("http://localhost:11434/api");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 构建JSON请求体
    QJsonObject json;
    json["model"] = model;
    json["prompt"] = prompt;
    json["stream"] = false;  // 关闭流式输出，一次性获取完整响应
    //json["stream"] = true;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    //qDebug()<<data;

    // 发送POST请求
    QNetworkReply *reply = manager->post(request, data);
    connect(reply, &QNetworkReply::finished, this, &ollamacilent::onFinished);
}

void ollamacilent::onFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();


        // 提取响应文本（Ollama的响应字段为"response"）


        QString result = jsonObject["response"].toString();
        //QString response = jsonObject["response"].toString();   // 取最终回答
        QString thinking = jsonObject["thinking"].toString();   // 可选，显示思考过程

        qDebug() << "Ollama Response:" << result;
        //qDebug() << "Ollama Response:" <<thinking<<result<<"\n";


        emit resultReady(result);

    } else {

        qDebug() << "Error:" << reply->errorString();
    }

    reply->deleteLater();
}

