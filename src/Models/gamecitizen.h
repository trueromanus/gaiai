#ifndef GAMECITIZEN_H
#define GAMECITIZEN_H

#include <QObject>
#include "../gamebackend.h"

class GameCitizen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(bool isAlive READ isAlive NOTIFY isAliveChanged FINAL)
    Q_PROPERTY(bool isNotAlive READ isNotAlive NOTIFY isNotAliveChanged FINAL)
    Q_PROPERTY(bool isMad READ isMad NOTIFY isMadChanged FINAL)
    Q_PROPERTY(int stressLevel READ stressLevel WRITE setStressLevel NOTIFY stressLevelChanged FINAL)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged FINAL)
    Q_PROPERTY(QString originalLocation READ originalLocation WRITE setOriginalLocation NOTIFY originalLocationChanged FINAL)

private:
    QString m_title { "" };
    bool m_isAlive { true };
    int m_stressLevel { 0 };
    QString m_location { "" };
    QString m_originalLocation { "" };
    QMap<int, QString> m_schedule { QMap<int, QString>() };

public:
    explicit GameCitizen(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    bool isAlive() const noexcept { return m_isAlive; }
    bool isNotAlive() const noexcept { return !m_isAlive; }
    bool isMad() const noexcept { return m_stressLevel >= 2; }

    int stressLevel() const noexcept { return m_stressLevel; }
    void setStressLevel(int stressLevel) noexcept;

    QString location() const { return m_location; }
    void setLocation(const QString& location) noexcept;

    QString originalLocation() const { return m_originalLocation; }
    void setOriginalLocation(const QString& originalLocation) noexcept;

    void handleTimer(int time, const GameBackend& backend);

    void addSchedule(int time, const QString& location) noexcept;

signals:
    void titleChanged();
    void isAliveChanged();
    void isNotAliveChanged();
    void isMadChanged();
    void stressLevelChanged();
    void locationChanged();
    void originalLocationChanged();

};

#endif // GAMECITIZEN_H
