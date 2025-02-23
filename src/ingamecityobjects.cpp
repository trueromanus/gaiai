#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ingamecityobjects.h"

InGameCityObjects::InGameCityObjects(QObject *parent) {
    loadCitizens("en");
    loadHouses("en");

    fillActiveCitizens();
}

void InGameCityObjects::setGameBackend(const GameBackend* backend) noexcept
{
    m_gameBackend = const_cast<GameBackend *>(backend);
}

void InGameCityObjects::handleTimerForObjects(int time) noexcept
{
    bool isNeedRefreshActiveCitizens = false;

    foreach (auto citizen, m_activeCitizens) {
        citizen->handleTimer(time); // move citizen between locations by his schedule

        //if citizen at home and lump post not fixed it will be increase stress level on each timer tick
        if ((citizen->isInHomeLocation() || !citizen->enableSchedule()) && !lumpPostIsFixed(citizen->location())) {
            citizen->setStressLevel();
        }

        //if citizen in road and in location where not fixed light traffic his drive is ended
        if (!citizen->isInHomeLocation() && !ligthTrafficIsFixed(citizen->location())) {
            citizen->setIsNotAlive();
        }

        //if after handle timer if citizen is not alive need to filter active citizens on last step
        if (citizen->isNotAlive()) isNeedRefreshActiveCitizens = true;
    }

    if (isNeedRefreshActiveCitizens) fillActiveCitizens();
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

void InGameCityObjects::fillActiveCitizens() noexcept
{
    m_activeCitizens.clear();

    auto list = m_citizens.values();
    std::copy_if(
        list.begin(),
        list.end(),
        std::back_inserter(m_activeCitizens),
        [&](GameCitizen* citizen){
            return citizen->isAlive();
        }
    );
}

bool InGameCityObjects::citizenInTargetDestination(const QString &location)
{
    if (location == "Hospital") return true;
    if (location == "Template House") return true;

    return false;
}

bool InGameCityObjects::ligthTrafficIsFixed(const QString &location)
{
    return std::none_of(
        m_trafficLights.cbegin(),
        m_trafficLights.cend(),
        [location](GameTrafficLightModel* item) {
            return !item->isCorrect() && item->isInAffectedLocations(location);
        }
    );
}

bool InGameCityObjects::lumpPostIsFixed(const QString &location)
{
    return std::none_of(
        m_lampPosts.cbegin(),
        m_lampPosts.cend(),
        [location](GameLampPost* item) {
            return !item->isCorrect() && item->isInAffectedLocations(location);
        }
    );
}
