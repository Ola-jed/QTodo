#ifndef QTODO_STEP_HPP
#define QTODO_STEP_HPP

#include "serializable.hpp"

struct Step: Serializable
{
    int id;
    QString title;
    int priority;

    Step(int id, const QString &title,int priority)
        :id(id),title(title),priority(priority)
    {}

    /// Build a step from a serialized one
    /// \param serializedStep
    /// \return Step
    static Step deserialize(const QString &serializedStep)
    {
        auto const jsonDocument = QJsonDocument::fromJson(serializedStep.toUtf8());
        auto const object = jsonDocument.object();
        return Step{
            object["id"].toInt(),
            object["title"].toString(),
            object["priority"].toInt()
        };
    }

    /// Serialize the current step
    /// \return QString
    [[nodiscard]] QString serialize() const override
    {
        QJsonObject obj{};
        obj["id"] = id;
        obj["title"] = title;
        obj["priority"] = priority;
        return QJsonDocument{obj}.toJson();
    }
};

#endif //QTODO_STEP_HPP
