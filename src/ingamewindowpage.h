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

};

#endif // INGAMEWINDOWPAGE_H
