#ifndef INGAMEFULLSCREEN_H
#define INGAMEFULLSCREEN_H

#include <QQuickItem>
#include "Models/gamestartscreenmodel.h"

class InGameFullScreen : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString turnOffMessage READ turnOffMessage NOTIFY turnOffMessageChanged FINAL)
    QML_ELEMENT

private:
    QString m_turnOffMessage { "" };
    QList<GameStartScreenModel*> m_loadingMessages { QList<GameStartScreenModel*>() };

public:
    InGameFullScreen();

    QString turnOffMessage() const noexcept { return m_turnOffMessage; }

private:
    void loadMessages(const QString& language);

signals:
    void turnOffMessageChanged();

};

#endif // INGAMEFULLSCREEN_H
