#ifndef QTODO_HTTPREQUESTHANDLER_HPP
#define QTODO_HTTPREQUESTHANDLER_HPP

#include "user.hpp"
#include <QSysInfo>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class HttpRequestHandler: public QObject
{
Q_OBJECT

public:
    HttpRequestHandler() = default;
    QString token = "";
    static const QString API_URL;

private:
    QNetworkAccessManager manager{};

public slots:
    void trySignup(const QMap<QString,QVariant> &data);
    void trySignin(const QMap<QString,QVariant> &data);
    void tryLogout();

signals:
    void signupSucceeded(const QString &result);
    void signinSucceeded(const QString &result);
    void logoutSucceeded();
    void authFailed(const QString &result);
};

#endif //QTODO_HTTPREQUESTHANDLER_HPP