#ifndef GAMETRAFFICLIGHTMODEL_H
#define GAMETRAFFICLIGHTMODEL_H

#include <QObject>

class GameTrafficLightModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)
    Q_PROPERTY(QString district READ district WRITE setDistrict NOTIFY districtChanged FINAL)
    Q_PROPERTY(bool isCorrect READ isCorrect NOTIFY isCorrectChanged FINAL)

private:
    const QString m_redName { "red" };
    const QString m_greenName { "green" };
    const QString m_yellowName { "yellow" };
    QStringList m_colors { QStringList() };
    QString m_text { "" };
    bool m_isCorrect { false };
    int m_correctRed { 0 };
    int m_correctGreen { 0 };
    int m_correctYellow { 0 };
    QString m_district { "" };

public:
    explicit GameTrafficLightModel(QObject *parent = nullptr);

    QString text() const noexcept { return m_text; }
    void setText(const QString& text) noexcept;

    QString district() const noexcept { return m_district; }
    void setDistrict(const QString& district) noexcept;

    bool isCorrect() const noexcept { return m_isCorrect; }

    void simpleSetup(int red, int green, int yellow, bool correct);

    void parseText();

private:
    std::tuple<int, int> parseLine(const QString& line);

signals:
    void textChanged();
    void isCorrectChanged();
    void districtChanged();

};

#endif // GAMETRAFFICLIGHTMODEL_H
