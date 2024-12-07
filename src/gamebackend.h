#ifndef GAMEBACKEND_H
#define GAMEBACKEND_H

#include <QObject>
#include <QVariantList>
#include <QtQml/qqmlregistration.h>
#include "Models/gametaskmodel.h"
#include "Models/gametrafficlightmodel.h"
#include "Models/gametasksectionmodel.h"
#include "PageModels/smarttrackerpage.h"
#include "PageModels/rssreaderpage.h"
#include "Models/translationsmodel.h"

class GameBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTaskSectionModel*> tasks READ tasks NOTIFY tasksChanged FINAL)
    Q_PROPERTY(int day READ day NOTIFY dayChanged FINAL)
    Q_PROPERTY(int time READ time NOTIFY timeChanged FINAL)
    Q_PROPERTY(SmartTrackerPage* smartTrackerPage READ smartTrackerPage NOTIFY smartTrackerPageChanged FINAL)
    Q_PROPERTY(RssReaderPage* rssReaderPage READ rssReaderPage NOTIFY rssReaderPageChanged FINAL)
    QML_ELEMENT

private:
    const QString m_onboardingTasks { "Onboarding" };
    const QString m_streetsTasks { "Streets" };
    const int m_firstDay { 1 };
    QList<GameTaskSectionModel*> m_tasksSections { QList<GameTaskSectionModel*>() };
    QMap<QString, GameTaskSectionModel*> m_tasksSectionMap { QMap<QString, GameTaskSectionModel*>() };
    QList<GameTaskModel*> m_allTasks { QList<GameTaskModel*>() };
    QList<GameTaskModel*> m_activeTasks { QList<GameTaskModel*>() };
    QMap<QString, GameTrafficLightModel*> m_trafficLights { QMap<QString, GameTrafficLightModel*>() };
    TranslationsModel* m_translationsModel { new TranslationsModel(this) };
    int m_day { 1 };
    int m_time { 0 };
    SmartTrackerPage* m_smartTrackerPage { new SmartTrackerPage(this) };
    RssReaderPage* m_rssReaderPage { new RssReaderPage(this) };

public:
    explicit GameBackend(QObject *parent = nullptr);

    QList<GameTaskSectionModel*> tasks() const noexcept { return m_tasksSections; }
    int day() const noexcept { return m_day; }
    int time() const noexcept { return m_time; }
    SmartTrackerPage* smartTrackerPage() const noexcept { return m_smartTrackerPage; }
    RssReaderPage* rssReaderPage() const noexcept { return m_rssReaderPage; }

    Q_INVOKABLE void moveToNextDay();
    Q_INVOKABLE void checkCompletedTasks();

private:
    void createDay1Tasks();
    void fillTasksForDay(int day);
    void createTrafficLights();

signals:
    void tasksChanged();
    void dayChanged();
    void timeChanged();
    void smartTrackerPageChanged();
    void rssReaderPageChanged();

};

#endif // GAMEBACKEND_H
