#ifndef GAMEBACKEND_H
#define GAMEBACKEND_H

#include <QObject>
#include <QVariantList>
#include <QtQml/qqmlregistration.h>

class GameBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList tasks READ tasks NOTIFY tasksChanged FINAL)
    QML_ELEMENT

private:
    QVariantList m_tasks { QVariantList() };

public:
    explicit GameBackend(QObject *parent = nullptr);

    QVariantList tasks() const noexcept { return m_tasks; }

signals:
    void tasksChanged();

};

#endif // GAMEBACKEND_H
