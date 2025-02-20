#ifndef GAMEHOUSE_H
#define GAMEHOUSE_H

#include <QObject>

class GameHouse : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString district READ district WRITE setDistrict NOTIFY districtChanged FINAL)
    Q_PROPERTY(QString shape READ shape WRITE setShape NOTIFY shapeChanged FINAL)
    Q_PROPERTY(int xvalue READ xvalue WRITE setXvalue NOTIFY xvalueChanged FINAL)
    Q_PROPERTY(int yvalue READ yvalue WRITE setYvalue NOTIFY yvalueChanged FINAL)
    Q_PROPERTY(int rotation READ rotation WRITE setRotation NOTIFY rotationChanged FINAL)

private:
    QString m_name { "" };
    QString m_district { "" };
    QString m_shape { "" };
    int m_xvalue { 0 };
    int m_yvalue { 0 };
    int m_rotation { 0 };

public:
    GameHouse(QObject *parent = nullptr);

    QString name() const noexcept { return m_name; }
    void setName(const QString& name) noexcept;

    QString district() const noexcept { return m_district; }
    void setDistrict(const QString& district) noexcept;

    QString shape() const noexcept { return m_shape; }
    void setShape(const QString& shape) noexcept;

    int xvalue() const noexcept { return m_xvalue; }
    void setXvalue(int xvalue) noexcept;

    int yvalue() const noexcept { return m_yvalue; }
    void setYvalue(int yvalue) noexcept;

    int rotation() const noexcept { return m_rotation; }
    void setRotation(int rotation) noexcept;

signals:
    void nameChanged();
    void districtChanged();
    void shapeChanged();
    void xvalueChanged();
    void yvalueChanged();
    void rotationChanged();

};

#endif // GAMEHOUSE_H
