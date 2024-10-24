#ifndef INGAMESTARTMENU_H
#define INGAMESTARTMENU_H

#include <QObject>
#include <QQuickItem>

class InGameStartMenu : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariantList menu READ menu NOTIFY menuChanged FINAL)
    QML_ELEMENT
private:
    QVariantList m_menu { QVariantList() };

public:
    InGameStartMenu();

    QVariantList menu() const { return m_menu; }

signals:
    void menuChanged();

};

#endif // INGAMESTARTMENU_H
