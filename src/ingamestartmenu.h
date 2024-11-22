#ifndef INGAMESTARTMENU_H
#define INGAMESTARTMENU_H

#include <QObject>
#include <QQuickItem>
#include "Models/gamemenumodel.h"

class InGameStartMenu : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariantList menu READ menu NOTIFY menuChanged FINAL)
    Q_PROPERTY(QList<GameMenuModel*> programs READ programs NOTIFY programsChanged FINAL)
    QML_ELEMENT
private:
    QVariantList m_menu { QVariantList() };
    QList<GameMenuModel*> m_programs { QList<GameMenuModel*>() };

public:
    InGameStartMenu();

    QVariantList menu() const { return m_menu; }
    QList<GameMenuModel*> programs() const { return m_programs; }

private:
    void fillProgramsMenu();

signals:
    void menuChanged();
    void commandRunned(const QString& command);
    void programsChanged();

};

#endif // INGAMESTARTMENU_H
