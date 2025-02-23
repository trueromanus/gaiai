#ifndef GAMELAMPPOST_H
#define GAMELAMPPOST_H

#include <QObject>

class GameLampPost : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorks READ isWorks WRITE setIsWorks NOTIFY isWorksChanged FINAL)
    Q_PROPERTY(bool isCorrect READ isCorrect NOTIFY isCorrectChanged FINAL)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)

private:
    bool m_isWorks { false };
    bool m_isCorrect { false };
    QString m_text { "" };
    QList<std::tuple<bool, int>> m_correctTimes { QList<std::tuple<bool, int>>() };
    QList<std::tuple<bool, int>> m_parsedTimes { QList<std::tuple<bool, int>>() };
    const QString m_lightOn { "lighton" };
    const QString m_lightOff { "lightoff" };
    QList<QString> m_affectedLocations { QList<QString>() };

public:
    explicit GameLampPost(QObject *parent = nullptr);

    bool isWorks() const noexcept { return m_isWorks; }
    void setIsWorks(bool isWorks) noexcept;

    bool isCorrect() const noexcept { return m_isCorrect; }

    QString text() const noexcept { return m_text; }
    void setText(const QString& text) noexcept;

    void simpleSetup(QList<std::tuple<bool, int>> times, bool correct);

    void parseText();

    void addAffectedLocation(const QString& location);
    bool isInAffectedLocations(const QString& location);

private:
    std::tuple<bool, bool, int> parseLine(const QString& line);

signals:
    void isWorksChanged();
    void isCorrectChanged();
    void textChanged();

};

#endif // GAMELAMPPOST_H

/*
lighton 19h
lightoff 20h
lighton 21h
*/
