#include "gamebackend.h"

GameBackend::GameBackend(QObject *parent)
    : QObject{parent}
{
    auto onboardingSection = new GameTaskSectionModel(this);
    onboardingSection->setTitle("Onboarding");
    m_tasksSections.append(onboardingSection);

    auto streetsSection = new GameTaskSectionModel(this);
    streetsSection->setTitle("Streets");
    m_tasksSections.append(streetsSection);

    m_tasksSectionMap.insert(m_onboardingTasks, onboardingSection);
    m_tasksSectionMap.insert(m_streetsTasks, streetsSection);

    createTrafficLights();

    createDay1Tasks();

    fillTasksForDay(m_firstDay);
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
    auto emailTutorial = new GameTaskModel(true, "Check you emails", m_onboardingTasks, m_firstDay,[]() { return true; }, this);
    emailTutorial->setDescription("First youn need open email client<br>");
    m_allTasks.append(emailTutorial);

    auto messagerTutorial = new GameTaskModel(true, "Reply in user groups", m_onboardingTasks, m_firstDay,[]() { return true; }, this);
    m_allTasks.append(messagerTutorial);

    auto rssTutorial = new GameTaskModel(true, "Read news", m_onboardingTasks, m_firstDay,[]() { return true; }, this);
    m_allTasks.append(rssTutorial);

    auto trafficLightTask = m_trafficLights.value("ElmStreetHighway");
    auto fixTrafficLightTutorial = new GameTaskModel(true, "Fix traffic light", m_onboardingTasks, m_firstDay, [trafficLightTask]() { return trafficLightTask->isCorrect(); }, this);
    m_allTasks.append(fixTrafficLightTutorial);
}

void GameBackend::fillTasksForDay(int day)
{
    m_activeTasks.clear();

    // clear inner tasks
    foreach (auto section, m_tasksSections) {
        section->clearInnerTasks();
    }

    // fill active tasks and section inner tasks
    foreach (auto task, m_allTasks) {
        if (task->day() != day) continue;

        m_activeTasks.append(task);
        auto parentId = task->parentId();
        if (!m_tasksSectionMap.contains(parentId)) continue;

        auto section = m_tasksSectionMap.value(parentId);
        section->addInnerTask(task);
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
