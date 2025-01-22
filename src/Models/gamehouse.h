#ifndef GAMEHOUSE_H
#define GAMEHOUSE_H

#include <QObject>

class GameHouse : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString district READ district WRITE setDistrict NOTIFY districtChanged FINAL)
    Q_PROPERTY(QString shape READ shape WRITE setShape NOTIFY shapeChanged FINAL)

private:
    QString m_name { "" };
    QString m_district { "" };
    QString m_shape { "" };

public:
    GameHouse(QObject *parent = nullptr);

    QString name() const noexcept { return m_name; }
    void setName(const QString& name) noexcept;

    QString district() const noexcept { return m_district; }
    void setDistrict(const QString& district) noexcept;

    QString shape() const noexcept { return m_shape; }
    void setShape(const QString& shape) noexcept;

signals:
    void nameChanged();
    void districtChanged();
    void shapeChanged();

};

#endif // GAMEHOUSE_H
