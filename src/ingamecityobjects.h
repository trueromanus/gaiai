#ifndef INGAMECITYOBJECTS_H
#define INGAMECITYOBJECTS_H

#include <QQuickItem>
#include "Models/gamecitizen.h"
#include "Models/gamehouse.h"
#include "Models/gametrafficlightmodel.h"
#include "Models/gamelamppost.h"
#include "gamebackend.h"

class InGameCityObjects : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(GameBackend* gameBackend READ gameBackend WRITE setGameBackend NOTIFY gameBackendChanged FINAL)
    QML_ELEMENT

private:
    QList<GameCitizen*> m_activeCitizens { QList<GameCitizen*>() };
    QMap<QString, GameCitizen*> m_citizens { QMap<QString, GameCitizen*>() };
    QMap<QString, GameHouse*> m_houses { QMap<QString, GameHouse*>() };
    QMap<QString, GameTrafficLightModel*> m_trafficLights { QMap<QString, GameTrafficLightModel*>() };
    QMap<QString, GameLampPost*> m_lampPosts { QMap<QString, GameLampPost*>() };
    GameBackend* m_gameBackend { nullptr };

public:
    explicit InGameCityObjects(QObject *parent = nullptr);

    GameBackend* gameBackend() const noexcept { return m_gameBackend; }
    void setGameBackend(const GameBackend* backend) noexcept;

    Q_INVOKABLE void handleTimerForObjects(int time) noexcept;

private:
    void loadCitizens(const QString& language);
    void loadHouses(const QString& language);
    void fillActiveCitizens() noexcept;
    bool citizenInTargetDestination(const QString& location);
    bool ligthTrafficIsFixed(const QString& location);
    bool lumpPostIsFixed(const QString& location);

signals:
    void gameBackendChanged();

};

#endif // INGAMECITYOBJECTS_H
