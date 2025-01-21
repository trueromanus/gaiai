#ifndef GAMECITIZEN_H
#define GAMECITIZEN_H

#include <QObject>
#include "../gamebackend.h"

class GameCitizen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(bool isALive READ isALive NOTIFY isALiveChanged FINAL)
    Q_PROPERTY(bool isNotALive READ isNotALive NOTIFY isNotALiveChanged FINAL)
    Q_PROPERTY(bool isMad READ isMad NOTIFY isMadChanged FINAL)
    Q_PROPERTY(int stressLevel READ stressLevel WRITE setStressLevel NOTIFY stressLevelChanged FINAL)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged FINAL)
    Q_PROPERTY(QString originalLocation READ originalLocation WRITE setOriginalLocation NOTIFY originalLocationChanged FINAL)

private:
    QString m_title { "" };
    bool m_isALive { true };
    int m_stressLevel { 0 };
    QString m_location { "" };
    QString m_originalLocation { "" };
    QList<QString> m_relatedTrafficLights { QList<QString>() };

public:
    explicit GameCitizen(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    bool isALive() const noexcept { return m_isALive; }
    bool isNotALive() const noexcept { return !m_isALive; }
    bool isMad() const noexcept { return m_stressLevel >= 2; }

    int stressLevel() const noexcept { return m_stressLevel; }
    void setStressLevel(int stressLevel) noexcept;

    QString location() const { return m_location; }
    void setLocation(const QString& location) noexcept;

    QString originalLocation() const { return m_originalLocation; }
    void setOriginalLocation(const QString& originalLocation) noexcept;

    void handleTimer(int time, const GameBackend& backend);

    void addTrafficLights(const QList<QString>& trafficLights) noexcept;

signals:
    void titleChanged();
    void isALiveChanged();
    void isNotALiveChanged();
    void isMadChanged();
    void stressLevelChanged();
    void locationChanged();
    void originalLocationChanged();

};

#endif // GAMECITIZEN_H
