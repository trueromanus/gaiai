#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "translationsmodel.h"

TranslationsModel::TranslationsModel(QObject *parent)
    : QObject{parent}
{
    readTasksContents("en");
}

QString TranslationsModel::getTasksTranslation(const QString &key) noexcept
{
    if (!m_tasksContents.contains(key)) return "";

    return m_tasksContents.value(key);
}

void TranslationsModel::readTasksContents(const QString& language)
{
    QFile file(":/qt/qml/gaiai/TextContents/taskContents." + language + ".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto content = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(content);
    auto array = document.array();

    foreach (auto item, array) {
        auto object = item.toObject();
        auto id = object.value("id").toString();
        auto text = object.value("text").toString();

        if (m_tasksContents.contains(id)) {
            m_tasksContents[id] = text;
        } else {
            m_tasksContents.insert(id, text);
        }
    }
}
