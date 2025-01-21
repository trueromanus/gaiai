#ifndef INGAMECITYOBJECTS_H
#define INGAMECITYOBJECTS_H

#include <QQuickItem>
#include "Models/gamecitizen.h"
#include "gamebackend.h"

class InGameCityObjects : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(GameBackend* gameBackend READ gameBackend WRITE setGameBackend NOTIFY gameBackendChanged FINAL)
    QML_ELEMENT

private:
    QList<GameCitizen*> m_gameCitizens { QList<GameCitizen*>() };
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
