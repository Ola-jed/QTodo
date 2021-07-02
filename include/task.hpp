#ifndef QTODO_TASK_HPP
#define QTODO_TASK_HPP

#include "slugify.hpp"
#include "serializable.hpp"

struct Task: Serializable
{
    QString title = "";
    QString slug = "";
    QString description = "";
    bool has_steps = false;
    int priority = 1;
    QString date_limit = "";

    Task() = default;

    Task(const QString &title,const QString &slug,const QString &description,bool has_steps,int priority,const QString &date_limit)
        :title(title),slug(slug),description(description),has_steps(has_steps),priority(priority),date_limit(date_limit)
    {}

    /// Build a task from a serialized json
    /// \param serializedTask
    /// \return Task
    static Task deserialize(const QString &serializedTask)
    {
        auto const jsonDocument = QJsonDocument::fromJson(serializedTask.toUtf8());
        auto const object = jsonDocument.object();
        return Task{
            object["title"].toString(),
            object["slug"].toString(),
            object["description"].toString(),
            object["has_steps"].toBool(),
            object["priority"].toInt(),
            object["date_limit"].toString()
        };
    }

    /// Build a task from a map
    /// \param map
    /// \return
    static Task fromMap(const QMap<QString,QVariant> &map)
    {
        return Task{
            map["title"].toString(),
            QString::fromStdString(slugify(map["title"].toString().toStdString())),
            map["description"].toString(),
            map["has_steps"].toBool(),
            map["priority"].toInt(),
            map["date_limit"].toString()
        };
    }

    /// Serialize a task into json
    /// \return QString
    [[nodiscard]] QString serialize() const override
    {
        QJsonObject obj{};
        obj["title"] = title;
        obj["slug"] = slug;
        obj["description"] = description;
        obj["has_steps"] = has_steps;
        obj["priority"] = priority;
        obj["date_limit"] = date_limit;
        return QJsonDocument{obj}.toJson();
    }
};

#endif //QTODO_TASK_HPP
