#ifndef QTODO_SERIALIZABLE_HPP
#define QTODO_SERIALIZABLE_HPP

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

/// Serializable struct for interactions with json
struct Serializable
{
    [[ nodiscard ]] virtual QString serialize() const = 0;
};

#endif //QTODO_SERIALIZABLE_HPP