#ifndef GAMETRAFFICLIGHTMODEL_H
#define GAMETRAFFICLIGHTMODEL_H

#include <QObject>

class GameTrafficLightModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)
    Q_PROPERTY(bool isCorrect READ isCorrect NOTIFY isCorrectChanged FINAL)

private:
    const QString m_redName { "red" };
    const QString m_greenName { "green" };
    const QString m_yellowName { "yellow" };
    QStringList m_colors { QStringList() };
    QString m_text { "" };
    bool m_isCorrect { false };
    bool m_correctRed { 0 };
    bool m_correctGreen { 0 };
    bool m_correctYellow { 0 };

public:
    explicit GameTrafficLightModel(QObject *parent = nullptr);

    QString text() const noexcept { return m_text; }
    void setText(const QString& text) noexcept;

    bool isCorrect() const noexcept { return m_isCorrect; }

    void simpleSetup(int red, int green, int yellow, bool correct);

    void parseText();

private:
    std::tuple<int, int> parseLine(const QString& line);

signals:
    void textChanged();
    void isCorrectChanged();

};

#endif // GAMETRAFFICLIGHTMODEL_H
