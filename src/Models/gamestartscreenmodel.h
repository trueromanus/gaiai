#ifndef GAMESTARTSCREENMODEL_H
#define GAMESTARTSCREENMODEL_H

#include <QObject>

class GameStartScreenModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int day READ day WRITE setDay NOTIFY dayChanged FINAL)
    Q_PROPERTY(QString nameOS READ nameOS WRITE setNameOS NOTIFY nameOSChanged FINAL)
    Q_PROPERTY(QString nameOSExtra READ nameOSExtra WRITE setNameOSExtra NOTIFY nameOSExtraChanged FINAL)
    Q_PROPERTY(QString companyName READ companyName WRITE setCompanyName NOTIFY companyNameChanged FINAL)
    Q_PROPERTY(QString slogan READ slogan WRITE setSlogan NOTIFY sloganChanged FINAL)
    Q_PROPERTY(QString background READ background WRITE setBackground NOTIFY backgroundChanged FINAL)
private:
    int m_day { 0 };
    QString m_nameOS { "" };
    QString m_nameOSExtra { "" };
    QString m_companyName { "" };
    QString m_slogan { "" };
    QString m_background { "" };

public:
    explicit GameStartScreenModel(QObject *parent = nullptr);

    int day() const noexcept { return m_day; }
    void setDay(int day) noexcept;

    QString nameOS() const noexcept { return m_nameOS; }
    void setNameOS(const QString& nameOS) noexcept;

    QString nameOSExtra() const noexcept { return m_nameOSExtra; }
    void setNameOSExtra(const QString& nameOSExtra) noexcept;

    QString companyName() const noexcept { return m_companyName; }
    void setCompanyName(const QString& companyName) noexcept;

    QString slogan() const noexcept { return m_slogan; }
    void setSlogan(const QString& slogan) noexcept;

    QString background() const noexcept { return m_background; }
    void setBackground(const QString& background) noexcept;

signals:
    void dayChanged();
    void nameOSChanged();
    void nameOSExtraChanged();
    void companyNameChanged();
    void sloganChanged();
    void backgroundChanged();

};

#endif // GAMESTARTSCREENMODEL_H
