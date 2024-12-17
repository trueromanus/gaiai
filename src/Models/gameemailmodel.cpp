#include "gameemailmodel.h"

GameEmailModel::GameEmailModel(QObject *parent)
    : QObject{parent}
{}

void GameEmailModel::setHasAttachments(bool hasAttachments) noexcept
{
    if (m_hasAttachments == hasAttachments) return;

    m_hasAttachments = hasAttachments;
    emit hasAttachmentsChanged();
}

void GameEmailModel::setIsReaded(bool isReaded) noexcept
{
    if (m_isReaded == isReaded) return;

    m_isReaded = isReaded;
    emit isReadedChanged();
}

void GameEmailModel::setFrom(const QString &from) noexcept
{
    if (m_from == from) return;

    m_from = from;
    emit fromChanged();
}

void GameEmailModel::setTo(const QString &to) noexcept
{
    if (m_to == to) return;

    m_to = to;
    emit toChanged();
}

void GameEmailModel::setSubject(const QString &subject) noexcept
{
    if (m_subject == subject) return;

    m_subject = subject;
    emit subjectChanged();
}

void GameEmailModel::setGroup(const QString &group) noexcept
{
    if (m_group == group) return;

    m_group = group;
    emit groupChanged();
}
