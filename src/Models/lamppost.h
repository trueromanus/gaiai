#ifndef LAMPPOST_H
#define LAMPPOST_H

#include <QObject>

class LampPost : public QObject
{
    Q_OBJECT
public:
    explicit LampPost(QObject *parent = nullptr);

signals:
};

#endif // LAMPPOST_H
