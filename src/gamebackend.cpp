#include "gamebackend.h"

GameBackend::GameBackend(QObject *parent)
    : QObject{parent}
{
    QVariantMap onboarding;
    onboarding["title"] = "Onboarding";
    onboarding["hasChildrens"] = true;
    onboarding["isEndItem"] = false;
    m_tasks.append(onboarding);

    QVariantMap streets;
    streets["title"] = "Streets";
    streets["hasChildrens"] = false;
    streets["isEndItem"] = true;
    m_tasks.append(streets);

    createTrafficLights();

    createDay1Tasks();
    createDay2Tasks();
    createDay3Tasks();
    createDay4Tasks();
    createDay5Tasks();
    createDay6Tasks();
    createDay7Tasks();
    createDay8Tasks();
}

void GameBackend::moveToNextDay()
{
    if (m_day == 8) {
        //TODO: it is game end need to make resume of all game
        return;
    }

    m_day += 1;

    fillTasksForDay(m_day);

    emit dayChanged();
}

void GameBackend::checkCompletedTasks()
{
    foreach (auto activeTask, m_activeTasks) {
        if (activeTask->completed()) continue;

        activeTask->checkCompleted();
    }
}

void GameBackend::createDay1Tasks()
{
    auto emailTutorial = new GameTaskModel(true, "Check you emails", m_onboardingTasks, 1,[]() { return true; }, this);
    m_allTasks.append(emailTutorial);

    auto messagerTutorial = new GameTaskModel(true, "Reply in user groups", m_onboardingTasks, 1,[]() { return true; }, this);
    m_allTasks.append(messagerTutorial);

    auto rssTutorial = new GameTaskModel(true, "Read news", m_onboardingTasks, 1,[]() { return true; }, this);
    m_allTasks.append(rssTutorial);

    auto trafficLightTask = m_trafficLights.value("ElmStreetHighway");
    auto fixTrafficLightTutorial = new GameTaskModel(true, "Fix traffic light", m_onboardingTasks, 1, [trafficLightTask]() { return trafficLightTask->isCorrect(); }, this);
    m_allTasks.append(fixTrafficLightTutorial);
}

void GameBackend::createDay2Tasks()
{

}

void GameBackend::createDay3Tasks()
{

}

void GameBackend::createDay4Tasks()
{

}

void GameBackend::createDay5Tasks()
{

}

void GameBackend::createDay6Tasks()
{

}

void GameBackend::createDay7Tasks()
{

}

void GameBackend::createDay8Tasks()
{

}

void GameBackend::fillTasksForDay(int day)
{
    m_activeTasks.clear();

    foreach (auto task, m_allTasks) {
        if (task->day() == day) m_activeTasks.append(task);
    }
}

void GameBackend::createTrafficLights()
{
    // Elm street, left side

    auto elmStreetStartHighway = new GameTrafficLightModel(this);
    elmStreetStartHighway->simpleSetup(10, 5, 3, true);
    m_trafficLights.insert("ElmStreetHighway", elmStreetStartHighway);

    auto elmStreetHouse1526 = new GameTrafficLightModel(this);
    elmStreetHouse1526->simpleSetup(5, 4, 2, true);
    m_trafficLights.insert("ElmStreetHouse1526", elmStreetHouse1526);

    auto elmStreetHouse1680 = new GameTrafficLightModel(this);
    elmStreetHouse1680->simpleSetup(7, 5, 2, true);
    m_trafficLights.insert("ElmStreetHouse1680", elmStreetHouse1680);

    // Elm street, right side

    auto elmStreetHouse1427 = new GameTrafficLightModel(this);
    elmStreetHouse1427->simpleSetup(9, 8, 3, true);
    m_trafficLights.insert("ElmStreetHouse1427", elmStreetHouse1427);

    auto elmStreetHouse1529 = new GameTrafficLightModel(this);
    elmStreetHouse1529->simpleSetup(8, 8, 2, true);
    m_trafficLights.insert("ElmStreetHouse1529", elmStreetHouse1529);

}
