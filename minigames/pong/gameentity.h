#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <QQuickItem>

class GameEntity : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged FINAL)
    QML_ELEMENT

private:
    QString m_identifier { "" };

public:
    GameEntity();

    QString identifier() const noexcept { return m_identifier; }
    void setIdentifier(const QString& identifier) noexcept;

signals:
    void identifierChanged();

};

#endif // GAMEENTITY_H
