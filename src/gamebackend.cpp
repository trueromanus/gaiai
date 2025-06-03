#include <QTimer>
#include <QCoreApplication>
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

    fillDay(1);
    QSet<QString> emptyTasks;
    m_rssReaderPage->fillForDay(m_firstDay, emptyTasks);
}

void GameBackend::moveToNextDay()
{
    if (m_day == 8) {
        //TODO: it is game end need to make resume of all game
        return;
    }

    fillDay(m_day + 1);

    emit dayChanged();
}

void GameBackend::moveToDay(int number)
{
    if (number > 8 || number < 1) return;

    fillDay(number);
}

void GameBackend::checkCompletedTasks()
{
    foreach (auto activeTask, m_activeTasks) {
        if (activeTask->completed()) continue;

        activeTask->checkCompleted();
    }
}

void GameBackend::fillDay(int day)
{
    m_day = day;
    fillTasksForDay(m_day);
    m_emailClientPage->fillForDay(m_day);
    QSet<QString> completedTasks;
    m_rssReaderPage->fillForDay(m_day, completedTasks);
}

void GameBackend::showFullScreen(const QString &screen)
{
    m_bigScreenType = screen;
    m_isBigScreenVisible = true;

    emit bigScreenTypeChanged();
    emit isBigScreenVisibleChanged();
}

void GameBackend::hideFullScreen()
{
    m_bigScreenType = "";
    m_isBigScreenVisible = false;

    emit bigScreenTypeChanged();
    emit isBigScreenVisibleChanged();
}

void GameBackend::turnoffGame()
{
    QTimer::singleShot(4000, this, &GameBackend::handleTurnOff);
}

bool GameBackend::locationIsFixed(const QString &location) const
{
    return true;
}

void GameBackend::createDay1Tasks()
{
    auto emailTutorial = new GameTaskModel(true, "Check you emails", m_onboardingTasks, m_firstDay,[]() { return true; }, this);
    emailTutorial->setDescription(m_translationsModel->getTasksTranslation("emailTutorial"));
    m_allTasks.append(emailTutorial);

    auto messagerTutorial = new GameTaskModel(true, "Reply in user groups", m_onboardingTasks, m_firstDay,[]() { return true; }, this);
    messagerTutorial->setDescription(m_translationsModel->getTasksTranslation("messagerTutorial"));
    m_allTasks.append(messagerTutorial);

    auto rssTutorial = new GameTaskModel(true, "Read news", m_onboardingTasks, m_firstDay,[]() { return true; }, this);
    rssTutorial->setDescription(m_translationsModel->getTasksTranslation("rssTutorial"));
    m_allTasks.append(rssTutorial);

    auto mapTutorial = new GameTaskModel(true, "Discover interactive map", m_onboardingTasks, m_firstDay,[]() { return true; }, this);
    mapTutorial->setDescription(m_translationsModel->getTasksTranslation("mapTutorial"));
    m_allTasks.append(mapTutorial);

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

void GameBackend::handleTurnOff()
{
    QCoreApplication::quit();
}
