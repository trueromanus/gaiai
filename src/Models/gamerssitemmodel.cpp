#include "gamerssitemmodel.h"

GameRssItemModel::GameRssItemModel(QObject *parent)
    : QObject{parent}
{}

void GameRssItemModel::setIcon(const QString &icon) noexcept
{
    if (m_icon == icon) return;

    m_icon = icon;
    emit iconChanged();
}

void GameRssItemModel::setHeader(const QString &header) noexcept
{
    if (m_header == header) return;

    m_header = header;
    emit headerChanged();
}

void GameRssItemModel::setContent(const QString &content) noexcept
{
    if (m_content == content) return;

    m_content = content;
    emit contentChanged();
}

void GameRssItemModel::setTopic(const QString &topic) noexcept
{
    if (m_topic == topic) return;

    m_topic = topic;
    emit topicChanged();
}

void GameRssItemModel::setDay(int day) noexcept
{
    if (m_day == day) return;

    m_day = day;
    emit dayChanged();
}
