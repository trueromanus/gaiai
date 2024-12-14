#ifndef GAMEEMAILMODEL_H
#define GAMEEMAILMODEL_H

#include <QObject>

class GameEmailModel : public QObject
{
    Q_OBJECT
public:
    explicit GameEmailModel(QObject *parent = nullptr);

signals:
};

#endif // GAMEEMAILMODEL_H
