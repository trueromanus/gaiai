#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ingamefullscreen.h"

InGameFullScreen::InGameFullScreen() {
    loadMessages("en");
}

void InGameFullScreen::loadMessages(const QString &language)
{
    QFile file(":/qt/qml/gaiai/TextContents/fullscreen." + language + ".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto content = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(content);
    auto root = document.object();

    m_turnOffMessage = root.value("turnoffMessage").toString();
    emit turnOffMessageChanged();

    m_loadingMessages.clear();
    auto loadingScreenMessages = root.value("loadingScreenMessages").toArray();
    foreach (auto screenMessage, loadingScreenMessages) {
        auto messageItem = screenMessage.toObject();

        auto model = new GameStartScreenModel(this);
        model->setDay(messageItem.value("day").toInt());
        model->setNameOS(messageItem.value("nameOS").toString());
        model->setNameOSExtra(messageItem.value("nameOSExtra").toString());
        model->setCompanyName(messageItem.value("companyName").toString());
        model->setSlogan(messageItem.value("slogan").toString());
        model->setBackground(messageItem.value("background").toString());

        m_loadingMessages.append(model);
    }
}
