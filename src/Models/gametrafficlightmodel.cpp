#include "gametrafficlightmodel.h"

GameTrafficLightModel::GameTrafficLightModel(QObject *parent)
    : QObject{parent}
{
    m_colors.append(m_redName);
    m_colors.append(m_greenName);
    m_colors.append(m_yellowName);
}

void GameTrafficLightModel::setText(const QString &text) noexcept
{
    if (m_text == text) return;

    m_text = text;
    emit textChanged();
}

void GameTrafficLightModel::simpleSetup(int red, int green, int yellow, bool correct)
{
    m_isCorrect = correct;
    m_correctRed = red;
    m_correctGreen = green;
    m_correctYellow = yellow;
    auto text = QString("red %1sec\ngreen %2sec\nyellow %3sec").arg(red).arg(green).arg(yellow);
    setText(text);
}

void GameTrafficLightModel::parseText()
{
    auto lines = m_text.split("\n");
    auto redCorrect = false;
    auto greenCorrect = false;
    auto yellowCorrect = false;
    foreach(auto line, lines) {
        auto lineContent = parseLine(line);
        auto type = std::get<0>(lineContent);
        if (type == -1) continue;

        auto seconds = std::get<1>(lineContent);

        switch (type) {
            case 0:
                redCorrect = seconds == m_correctRed;
                break;
            case 1:
                greenCorrect = seconds == m_correctGreen;
                break;
            case 2:
                yellowCorrect = seconds == m_correctYellow;
                break;
        }
    }

    m_isCorrect = redCorrect && greenCorrect && yellowCorrect;
    emit isCorrectChanged();
}

std::tuple<int, int> GameTrafficLightModel::parseLine(const QString &line)
{
    auto parts = line.trimmed().split(" ");
    if (parts.size() < 2) return std::make_tuple(-1, 0);

    auto first = parts.first();
    auto colorIndex = m_colors.indexOf(first);
    if (colorIndex == -1) return std::make_tuple(-1, 0);

    auto second = parts.value(1);
    auto seconds = second.trimmed().replace("sec", "").toInt();

    return std::make_tuple(colorIndex, seconds);
}
