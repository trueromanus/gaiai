#ifndef RUNPAGE_H
#define RUNPAGE_H

#include <QObject>

class RunPage : public QObject
{
    Q_OBJECT

private:
    QList<QString> m_usedCommands { QList<QString>() };

public:
    explicit RunPage(QObject *parent = nullptr);

    Q_INVOKABLE void runCommand(const QString& command);

signals:
    void commandRunned(const QString& command);

};

#endif // RUNPAGE_H
