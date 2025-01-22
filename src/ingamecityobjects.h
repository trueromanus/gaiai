#ifndef INGAMECITYOBJECTS_H
#define INGAMECITYOBJECTS_H

#include <QQuickItem>
#include "Models/gamecitizen.h"
#include "Models/gamehouse.h"
#include "Models/gametrafficlightmodel.h"
#include "gamebackend.h"

class InGameCityObjects : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(GameBackend* gameBackend READ gameBackend WRITE setGameBackend NOTIFY gameBackendChanged FINAL)
    QML_ELEMENT

private:
    QList<QString> m_activeCitizens { QList<QString>() };
    QMap<QString, GameCitizen*> m_citizens { QMap<QString, GameCitizen*>() };
    QMap<QString, GameHouse*> m_houses { QMap<QString, GameHouse*>() };
    QMap<QString, GameTrafficLightModel*> m_trafficLights { QMap<QString, GameTrafficLightModel*>() };
    GameBackend* m_gameBackend { nullptr };

public:
    explicit InGameCityObjects(QObject *parent = nullptr);

    GameBackend* gameBackend() const noexcept { return m_gameBackend; }
    void setGameBackend(const GameBackend* backend) noexcept;

    Q_INVOKABLE void handleTimerForCitizens(int time) noexcept;

signals:
    void gameBackendChanged();

};

#endif // INGAMECITYOBJECTS_H
