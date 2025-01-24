#include "gamelamppost.h"

GameLampPost::GameLampPost(QObject *parent)
    : QObject{parent}
{}

void GameLampPost::setIsWorks(bool isWorks) noexcept
{
    if (m_isWorks == isWorks) return;

    m_isWorks = isWorks;
    emit isWorksChanged();
}

void GameLampPost::setText(const QString &text) noexcept
{
    if (m_text == text) return;

    m_text = text;
    emit textChanged();
}

void GameLampPost::simpleSetup(QList<std::tuple<bool, int>> times, bool correct)
{
    m_correctTimes.clear();
    m_correctTimes.append(times);
    m_isCorrect = correct;

    emit isCorrectChanged();
}

void GameLampPost::parseText()
{
    m_parsedTimes.clear();

    auto lines = m_text.split("\n");
    foreach (auto item, lines) {
        auto parsedLine = parseLine(item);

        auto isCorrectLine = std::get<0>(parsedLine);
        if (!isCorrectLine) continue;

        bool isOn = std::get<1>(parsedLine);
        int hours = std::get<2>(parsedLine);

        m_parsedTimes.append(std::make_tuple(isOn, hours));
    }
}

std::tuple<bool, bool, int> GameLampPost::parseLine(const QString &line)
{
    auto parts = line.trimmed().split(" ");
    if (parts.size() < 2) return std::make_tuple(false, false, 0);

    auto first = parts.first();
    if (first == m_lightOn || first == m_lightOff) {
        bool* ok;
        auto second = parts.value(1).trimmed().toInt(ok);
        if (*ok) return std::make_tuple(true, first == m_lightOn, second);
    }

    return std::make_tuple(false, false, 0);
}
