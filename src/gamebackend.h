#ifndef GAMEBACKEND_H
#define GAMEBACKEND_H

#include <QObject>
#include <QVariantList>
#include <QtQml/qqmlregistration.h>
#include "Models/gametaskmodel.h"
#include "Models/gametrafficlightmodel.h"

class GameBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList tasks READ tasks NOTIFY tasksChanged FINAL)
    Q_PROPERTY(int day READ day NOTIFY dayChanged FINAL)
    Q_PROPERTY(int time READ time NOTIFY timeChanged FINAL)
    QML_ELEMENT

private:
    const QString m_onboardingTasks { "Onboarding" };
    QVariantList m_tasks { QVariantList() };
    QList<GameTaskModel*> m_allTasks { QList<GameTaskModel*>() };
    QList<GameTaskModel*> m_activeTasks { QList<GameTaskModel*>() };
    QMap<QString, GameTrafficLightModel*> m_trafficLights { QMap<QString, GameTrafficLightModel*>() };
    int m_day { 1 };
    int m_time { 0 };

public:
    explicit GameBackend(QObject *parent = nullptr);

    QVariantList tasks() const noexcept { return m_tasks; }
    int day() const noexcept { return m_day; }
    int time() const noexcept { return m_time; }

    Q_INVOKABLE void moveToNextDay();
    Q_INVOKABLE void checkCompletedTasks();

private:
    void createDay1Tasks();
    void createDay2Tasks();
    void createDay3Tasks();
    void createDay4Tasks();
    void createDay5Tasks();
    void createDay6Tasks();
    void createDay7Tasks();
    void createDay8Tasks();
    void fillTasksForDay(int day);
    void createTrafficLights();

signals:
    void tasksChanged();
    void dayChanged();
    void timeChanged();

};

#endif // GAMEBACKEND_H
