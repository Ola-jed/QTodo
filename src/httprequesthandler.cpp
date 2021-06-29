#include "httprequesthandler.hpp"

const QString HttpRequestHandler::API_URL = "http://localhost:8000/api/";

/// Make the signin
/// \param data
void HttpRequestHandler::trySignin(const QMap<QString, QVariant> &data)
{
    QNetworkRequest rq{QUrl(API_URL +  "signin")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QJsonObject obj{};
    const auto keys = data.keys();
    for(auto const &aKey : keys)
    {
        obj[aKey] = data[aKey].toString();
    }
    obj["device_name"] = QSysInfo::machineHostName();
    const QJsonDocument doc{obj};
    auto const qNetworkReply = manager.post(rq,doc.toJson());
    connect(qNetworkReply,&QNetworkReply::finished,this,[=]{
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit signinSucceeded(qNetworkReply->readAll());
        }
        else
        {
            emit authFailed(qNetworkReply->errorString());
        }
        manager.clearConnectionCache();
    });
}

/// Make the signin
/// \param data
void HttpRequestHandler::trySignup(const QMap<QString, QVariant> &data)
{
    QNetworkRequest rq{QUrl(API_URL + "signup")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QJsonObject obj{};
    const auto keys = data.keys();
    for(auto const &aKey : keys)
    {
        obj[aKey] = data[aKey].toString();
    }
    obj["device_name"] = QSysInfo::machineHostName();
    const QJsonDocument doc{obj};
    auto const qNetworkReply = manager.post(rq,doc.toJson());
    connect(qNetworkReply,&QNetworkReply::finished,this,[=,this]{
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit signupSucceeded(qNetworkReply->readAll());
        }
        else
        {
            emit authFailed(qNetworkReply->errorString());
        }
        manager.clearConnectionCache();
    });
}

/// Logout the connected user
/// Clear the token and close t)he connection
void HttpRequestHandler::tryLogout()
{
    QNetworkRequest rq{QUrl(API_URL + "logout")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.post(rq,"");
    connect(qNetworkReply,&QNetworkReply::finished,this,[=,this]{
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            token.clear();
            emit logoutSucceeded();
        }
        else
        {
            emit authFailed(qNetworkReply->errorString());
        }
        manager.clearConnectionCache();
    });
}