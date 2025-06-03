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
#include "PageModels/emailclientpage.h"
#include "PageModels/runpage.h"
#include "Models/translationsmodel.h"

class GameBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTaskSectionModel*> tasks READ tasks NOTIFY tasksChanged FINAL)
    Q_PROPERTY(int day READ day NOTIFY dayChanged FINAL)
    Q_PROPERTY(SmartTrackerPage* smartTrackerPage READ smartTrackerPage NOTIFY smartTrackerPageChanged FINAL)
    Q_PROPERTY(RssReaderPage* rssReaderPage READ rssReaderPage NOTIFY rssReaderPageChanged FINAL)
    Q_PROPERTY(EmailClientPage* emailClientPage READ emailClientPage NOTIFY emailClientPageChanged FINAL)
    Q_PROPERTY(RunPage* runPage READ runPage NOTIFY runPageChanged FINAL)
    Q_PROPERTY(bool isBigScreenVisible READ isBigScreenVisible NOTIFY isBigScreenVisibleChanged FINAL)
    Q_PROPERTY(QString bigScreenType READ bigScreenType NOTIFY bigScreenTypeChanged FINAL)
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
    QSet<QString> m_activatedTriggers { QSet<QString>() };
    TranslationsModel* m_translationsModel { new TranslationsModel(this) };
    int m_day { 1 };
    SmartTrackerPage* m_smartTrackerPage { new SmartTrackerPage(this) };
    RssReaderPage* m_rssReaderPage { new RssReaderPage(this) };
    EmailClientPage* m_emailClientPage { new EmailClientPage(this) };
    RunPage* m_runPage { new RunPage(this) };
    bool m_isBigScreenVisible { false };
    QString m_bigScreenType { "" };

public:
    explicit GameBackend(QObject *parent = nullptr);

    QList<GameTaskSectionModel*> tasks() const noexcept { return m_tasksSections; }
    int day() const noexcept { return m_day; }
    SmartTrackerPage* smartTrackerPage() const noexcept { return m_smartTrackerPage; }
    RssReaderPage* rssReaderPage() const noexcept { return m_rssReaderPage; }
    EmailClientPage* emailClientPage() const noexcept { return m_emailClientPage; }
    RunPage* runPage() const noexcept { return m_runPage; }

    bool isBigScreenVisible() const noexcept { return m_isBigScreenVisible; }
    QString bigScreenType() const noexcept { return m_bigScreenType; }

    Q_INVOKABLE void moveToNextDay();
    Q_INVOKABLE void moveToDay(int number);
    Q_INVOKABLE void checkCompletedTasks();
    Q_INVOKABLE void fillDay(int day);
    Q_INVOKABLE void showFullScreen(const QString& screen);
    Q_INVOKABLE void hideFullScreen();
    Q_INVOKABLE void turnoffGame();
    Q_INVOKABLE void activateTrigger(const QString& name);

    bool locationIsFixed(const QString& location) const;

private:
    void createDay1Tasks();
    void fillTasksForDay(int day);
    void createTrafficLights();

private slots:
    void handleTurnOff();

signals:
    void tasksChanged();
    void dayChanged();
    void timeChanged();
    void smartTrackerPageChanged();
    void rssReaderPageChanged();
    void emailClientPageChanged();
    void isBigScreenVisibleChanged();
    void bigScreenTypeChanged();
    void runPageChanged();

};

#endif // GAMEBACKEND_H
