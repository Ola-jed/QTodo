#ifndef QTODO_HTTPREQUESTHANDLER_HPP
#define QTODO_HTTPREQUESTHANDLER_HPP

#include "user.hpp"
#include "task.hpp"
#include <QList>
#include <QSysInfo>
#include <QJsonArray>
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
    void tryTaskCreation(const Task &taskToCreate);
    void tryTasksRetrieving();

signals:
    void signupSucceeded(const QString &result);
    void signinSucceeded(const QString &result);
    void logoutSucceeded();
    void authFailed(const QString &result);
    void taskCreationSucceeded();
    void tasksRetrievingSucceeded(const QList<Task> &tasks);
    void dataCreationFailed();
    void dataRetrievingFailed();
};

#endif //QTODO_HTTPREQUESTHANDLER_HPP