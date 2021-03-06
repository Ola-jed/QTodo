#include "httprequesthandler.hpp"

// REMOTE API LINK : https://todolist-rest-api.herokuapp.com/api/
// LOCAL API LINK : http://localhost:8000/api/

const QString HttpRequestHandler::API_URL = "https://todolist-rest-api.herokuapp.com/api/";

/// Make the signin
/// \param data
void HttpRequestHandler::trySignin(const QMap<QString, QVariant> &data)
{
    QNetworkRequest rq{QUrl(API_URL + "signin")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject     obj{};
    const auto      keys              = data.keys();
    for (auto const &aKey : keys)
    {
        obj[aKey] = data[aKey].toString();
    }
    obj["device_name"]                = QSysInfo::machineHostName();
    const QJsonDocument doc{obj};
    auto const          qNetworkReply = manager.post(rq, doc.toJson());
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit signinSucceeded(qNetworkReply->readAll());
        }
        else
        {
            emit authFailed(qNetworkReply->errorString());
        }
    });
}

/// Make the signin
/// \param data
void HttpRequestHandler::trySignup(const QMap<QString, QVariant> &data)
{
    QNetworkRequest rq{QUrl(API_URL + "signup")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject     obj{};
    const auto      keys              = data.keys();
    for (auto const &aKey : keys)
    {
        obj[aKey] = data[aKey].toString();
    }
    obj["device_name"]                = QSysInfo::machineHostName();
    const QJsonDocument doc{obj};
    auto const          qNetworkReply = manager.post(rq, doc.toJson());
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit signupSucceeded(qNetworkReply->readAll());
        }
        else
        {
            emit authFailed(qNetworkReply->errorString());
        }
    });
}

/// Logout the connected user
/// Clear the token and close t)he connection
void HttpRequestHandler::tryLogout()
{
    if (token.isEmpty())
    {
        emit dataRetrievingFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "logout")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.post(rq, "");
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            token.clear();
            emit logoutSucceeded();
        }
        else
        {
            emit authFailed(qNetworkReply->errorString());
        }
    });
}

/// Creates a new task
/// \param taskToCreate
void HttpRequestHandler::tryTaskCreation(const QMap<QString, QVariant> &taskToCreateAsMap)
{
    if (token.isEmpty())
    {
        emit dataCreationFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "tasks")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject obj{};
    obj["title"]               = taskToCreateAsMap["title"].toString();
    obj["description"]         = taskToCreateAsMap["description"].toString();
    obj["date_limit"]          = taskToCreateAsMap["date_limit"].toString();
    obj["has_steps"]           = taskToCreateAsMap["has_steps"].toInt();
    obj["priority"]            = taskToCreateAsMap["priority"].toInt();
    const QJsonDocument doc{obj};
    auto const          header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.post(rq, doc.toJson());
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit taskCreationSucceeded();
        }
        else
        {
            qDebug() << "Error : " << qNetworkReply->readAll();
            emit dataCreationFailed();
        }
    });
}

/// Get all tasks created by the current user
/// And deserialize them to load all in a list of tasks
void HttpRequestHandler::tryTasksRetrieving()
{
    if (token.isEmpty())
    {
        emit dataRetrievingFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "tasks")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.get(rq);
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            auto const      jsonResponse = QJsonDocument::fromJson(qNetworkReply->readAll());
            auto const      tasksList    = jsonResponse.object()["data"].toArray().toVariantList();
            QList<Task>     tasks{};
            for (const auto &tempTaskSerialized : tasksList)
            {
                tasks.push_back(Task::deserialize(QJsonDocument{tempTaskSerialized.toJsonObject()}.toJson()));
            }
            emit tasksRetrievingSucceeded(tasks);
        }
        else
        {
            emit dataRetrievingFailed();
        }
    });
}

/// Delete a task
/// \param taskToDelete
void HttpRequestHandler::tryTaskDeletion(const Task &taskToDelete)
{
    if (token.isEmpty())
    {
        emit dataDeletionFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "tasks/" + taskToDelete.slug)};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.deleteResource(rq);
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit taskDeletionSucceeded();
        }
        else
        {
            emit dataDeletionFailed();
        }
    });
}

/// Update the task that corresponds to the given slug
/// \param slug
/// \param newValue
void HttpRequestHandler::tryTaskUpdate(const QString &slug, const Task &newValue)
{
    if (token.isEmpty())
    {
        emit dataUpdateFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "tasks/" + slug)};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    QJsonObject obj{};
    obj["title"]                      = newValue.title;
    obj["description"]                = newValue.description;
    obj["date_limit"]                 = newValue.date_limit;
    obj["has_steps"]                  = newValue.has_steps;
    obj["priority"]                   = newValue.priority;
    const QJsonDocument doc{obj};
    auto const          qNetworkReply = manager.put(rq, doc.toJson());
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            auto const jsonResponse   = QJsonDocument::fromJson(qNetworkReply->readAll());
            auto const taskSerialized = jsonResponse.object()["data"].toString();
            emit taskUpdateSucceeded(Task::deserialize(taskSerialized));
        }
        else
        {
            emit dataUpdateFailed();
        }
    });
}

/// Searching a task
/// \param title
void HttpRequestHandler::tryTaskSearching(const QString &title)
{
    if (token.isEmpty())
    {
        emit dataRetrievingFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "tasks/search/" + title)};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.get(rq);
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            auto const      jsonResponse = QJsonDocument::fromJson(qNetworkReply->readAll());
            auto const      tasksList    = jsonResponse.object()["data"].toArray().toVariantList();
            QList<Task>     tasks{};
            for (const auto &tempTaskSerialized : tasksList)
            {
                tasks.push_back(Task::deserialize(QJsonDocument{tempTaskSerialized.toJsonObject()}.toJson()));
            }
            emit tasksRetrievingSucceeded(tasks);
        }
        else
        {
            emit dataRetrievingFailed();
        }
    });
}

/// Set the finished status for a task
/// \param slug
/// \param status
void HttpRequestHandler::tryTaskMarkingAsFinished(const QString &slug, bool status)
{
    if (token.isEmpty())
    {
        emit dataUpdateFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "tasks/" + slug + "/finish")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    QJsonObject obj{};
    obj["status"]                     = status;
    const QJsonDocument doc{obj};
    auto const          qNetworkReply = manager.put(rq, doc.toJson());
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            auto const jsonResponse   = QJsonDocument::fromJson(qNetworkReply->readAll());
            auto const taskSerialized = jsonResponse.object()["data"].toString();
            emit taskUpdateSucceeded(Task::deserialize(taskSerialized));
        }
        else
        {
            emit dataUpdateFailed();
        }
    });
}

/// Get information about the account of the connected user
void HttpRequestHandler::tryAccountInformationRetrieving()
{
    if (token.isEmpty())
    {
        emit dataRetrievingFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "account")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.get(rq);
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit accountDataRetrievingSucceeded(
                    QJsonDocument::fromJson(qNetworkReply->readAll()).object().toVariantMap());
        }
        else
        {
            emit dataRetrievingFailed();
        }
    });
}

/// Try to update the user account
/// \param newAccountData
void HttpRequestHandler::tryAccountUpdate(const QMap<QString,QVariant> &newAccountData)
{
    if (token.isEmpty())
    {
        emit dataUpdateFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "account")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    QJsonObject obj{QJsonObject::fromVariantMap(newAccountData)};
    const QJsonDocument doc{obj};
    auto const          qNetworkReply = manager.put(rq, doc.toJson());
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            auto const jsonResponse = QJsonDocument::fromJson(qNetworkReply->readAll());
            if(jsonResponse.object()["message"] == "Account updated")
            {
                emit accountUpdateSuceeded();
                return;
            }
        }
        emit dataUpdateFailed();
    });
}

/// Delete the user account
/// TODO : fix this
void HttpRequestHandler::tryAccountDeletion(const QString &password)
{
    if (token.isEmpty())
    {
        emit dataDeletionFailed();
        return;
    }
    QNetworkRequest rq{QUrl(API_URL + "account")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto const header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    auto const qNetworkReply = manager.deleteResource(rq);
    connect(qNetworkReply, &QNetworkReply::finished, this, [=, this] {
        if (qNetworkReply->error() == QNetworkReply::NoError)
        {
            emit taskDeletionSucceeded();
        }
        else
        {
            emit dataDeletionFailed();
        }
    });
}