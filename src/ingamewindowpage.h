#ifndef INGAMEWINDOWPAGE_H
#define INGAMEWINDOWPAGE_H

#include <QQuickItem>

class InGameWindowPage : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    InGameWindowPage();

signals:
    void closeContainerWindow();
    void runCommand(const QString& command);

};

#endif // INGAMEWINDOWPAGE_H
