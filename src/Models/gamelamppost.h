#ifndef GAMELAMPPOST_H
#define GAMELAMPPOST_H

#include <QObject>

class GameLampPost : public QObject
{
    Q_OBJECT
public:
    explicit GameLampPost(QObject *parent = nullptr);

signals:
};

#endif // GAMELAMPPOST_H
