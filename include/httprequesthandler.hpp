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
    void tryTaskCreation(const QMap<QString,QVariant> &taskToCreateAsMap);
    void tryTaskUpdate(const QString &slug,const Task &newValue);
    void tryTaskMarkingAsFinished(const QString &slug, bool status);
    void tryTaskDeletion(const Task &taskToDelete);
    void tryTaskSearching(const QString &title);
    void tryTasksRetrieving();
    void tryAccountInformationRetrieving();
    void tryAccountUpdate(const QMap<QString,QVariant> &newAccountData);
    void tryAccountDeletion(const QString &password);

signals:
    void signupSucceeded(const QString &result);
    void signinSucceeded(const QString &result);
    void logoutSucceeded();
    void authFailed(const QString &result);
    void taskCreationSucceeded();
    void taskDeletionSucceeded();
    void tasksRetrievingSucceeded(const QList<Task> &tasks);
    void taskUpdateSucceeded(const Task &task);
    void accountDataRetrievingSucceeded(const QMap<QString,QVariant> &accountData);
    void accountUpdateSuceeded();
    void accountDeleteSuceeded();
    void dataCreationFailed();
    void dataRetrievingFailed();
    void dataUpdateFailed();
    void dataDeletionFailed();
};

#endif //QTODO_HTTPREQUESTHANDLER_HPP