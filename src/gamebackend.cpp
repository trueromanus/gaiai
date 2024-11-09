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

void GameBackend::createDay1Tasks()
{
    auto emailTutorial = new GameTaskModel(true, "Check email from government", m_onboardingTasks, 1, this);
    auto messagerTutorial = new GameTaskModel(true, "Reply in user groups", m_onboardingTasks, 1, this);
    auto rssTutorial = new GameTaskModel(true, "Read news", m_onboardingTasks, 1, this);
    auto fixTrafficLightTutorial = new GameTaskModel(true, "Fix traffic light", m_onboardingTasks, 1, this);

    m_allTasks.append(emailTutorial);
    m_allTasks.append(messagerTutorial);
    m_allTasks.append(rssTutorial);
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
