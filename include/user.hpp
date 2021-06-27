#ifndef QTODO_USER_HPP
#define QTODO_USER_HPP

#include "serializable.hpp"

struct User: Serializable
{
    QString name;
    QString email;

    /// Constructor
    /// \param name
    /// \param email
    User(const QString& name, const QString& email)
        : name(name),email(email)
    {}

    /// Create a new user from a json serialized one
    /// \param QString serializedUser
    /// \return User
    static User deserialize(const QString &serializedUser)
    {
        auto const jsonDoc = QJsonDocument::fromJson(serializedUser.toUtf8());
        auto const object = jsonDoc.object();
        return User{
            object["name"].toString(),
            object["email"].toString()
        };
    }

    /// Serialize a user to a json format
    /// \return QString
    [[nodiscard]] QString serialize() const override
    {
        QJsonObject obj{};
        obj["name"] = name;
        obj["email"] = email;
        return QJsonDocument{obj}.toJson();
    }
};
#endif //QTODO_USER_HPP
