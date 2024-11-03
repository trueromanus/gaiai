#include "framepaginator.h"

FramePaginator::FramePaginator(QObject *parent)
    : QObject{parent}
{}

void FramePaginator::setStartPage(int startPage) noexcept
{
    if (m_startPage == startPage) return;

    m_startPage = startPage;
    emit startPageChanged();
}

void FramePaginator::setCurrentPage(int currentPage) noexcept
{
    if (m_currentPage == currentPage) return;

    m_currentPage = currentPage;
    emit currentPageChanged();
}

void FramePaginator::setCountPages(int countPages) noexcept
{
    if (m_countPages == countPages) return;

    m_countPages = countPages;
    emit countPagesChanged();
}

void FramePaginator::nextPage()
{
    if (m_currentPage >= m_countPages - 1) return;

    setCurrentPage(m_currentPage + 1);
    emit hasNextPageChanged();
    emit hasPreviousPageChanged();
}

void FramePaginator::previousPage()
{
    if (m_currentPage <= 0) return;

    setCurrentPage(m_currentPage - 1);
    emit hasNextPageChanged();
    emit hasPreviousPageChanged();
}
