#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ingamecityobjects.h"

InGameCityObjects::InGameCityObjects(QObject *parent) {
    loadCitizens("en");
    loadHouses("en");
}

void InGameCityObjects::setGameBackend(const GameBackend* backend) noexcept
{
    m_gameBackend = const_cast<GameBackend *>(backend);
}

void InGameCityObjects::handleTimerForCitizens(int time) const noexcept
{
    foreach (auto citizenKey, m_activeCitizens) {
        auto citizen = m_citizens.value(citizenKey);
        citizen->handleTimer(time, *m_gameBackend);
    }
}

void InGameCityObjects::loadCitizens(const QString& language)
{
    QFile file(":/qt/qml/gaiai/TextContents/citizens." + language + ".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto content = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(content);
    auto array = document.array();

    foreach (auto item, array) {
        auto object = item.toObject();
        auto title = object.value("title").toString("");
        auto originalLocation = object.value("originalLocation").toString("");
        auto location = object.value("location").toString("");
        auto schedule = object.value("schedule").toArray();

        auto citizen = new GameCitizen(this);
        citizen->setTitle(title);
        citizen->setOriginalLocation(originalLocation);
        citizen->setLocation(location);
        foreach (auto scheduleItem, schedule) {
            auto scheduleObject = scheduleItem.toObject();
            auto time = scheduleObject.value("time").toInt();
            //TODO: added extra parameter `randomTime` for randomize time in schedule
            auto scheduleLocation = scheduleObject.value("location").toString();
            citizen->addSchedule(time, scheduleLocation);
        }

        m_citizens.insert(title, citizen);
    }
}

void InGameCityObjects::loadHouses(const QString& language)
{
    QFile file(":/qt/qml/gaiai/TextContents/houses." + language + ".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto content = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(content);
    auto array = document.array();

    foreach (auto districtItem, array) {
        auto districtObject = districtItem.toObject();
        auto district = districtObject.value("district").toString();
        auto houses = districtObject.value("houses").toArray();
        foreach (auto house, houses) {
            auto houseObject = house.toObject();
            auto name = houseObject.value("name").toString();
            auto shape = houseObject.value("shape").toString();
            auto x = houseObject.value("x").toInt();
            auto y = houseObject.value("y").toInt();
            auto rotation = houseObject.value("rotation").toInt();
            auto gameHouse = new GameHouse(this);
            gameHouse->setDistrict(district);
            gameHouse->setName(name);
            gameHouse->setShape(shape);
            gameHouse->setXvalue(x);
            gameHouse->setYvalue(y);
            gameHouse->setRotation(rotation);

            m_houses.insert(name, gameHouse);
        }
    }
}
