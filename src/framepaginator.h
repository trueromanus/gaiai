#ifndef FRAMEPAGINATOR_H
#define FRAMEPAGINATOR_H

#include <QObject>
#include <QQmlEngine>

class FramePaginator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int startPage READ startPage WRITE setStartPage NOTIFY startPageChanged FINAL)
    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged FINAL)
    Q_PROPERTY(int countPages READ countPages WRITE setCountPages NOTIFY countPagesChanged FINAL)
    Q_PROPERTY(bool hasNextPage READ hasNextPage NOTIFY hasNextPageChanged FINAL)
    Q_PROPERTY(bool hasPreviousPage READ hasPreviousPage NOTIFY hasPreviousPageChanged FINAL)
    QML_ELEMENT

private:
    int m_startPage { 0 };
    int m_currentPage { 0 };
    int m_countPages { 0 };

public:
    explicit FramePaginator(QObject *parent = nullptr);

    int startPage() const noexcept { return m_startPage; }
    void setStartPage(int startPage) noexcept;

    int currentPage() const noexcept { return m_currentPage; }
    void setCurrentPage(int currentPage) noexcept;

    int countPages() const noexcept { return m_countPages; }
    void setCountPages(int countPages) noexcept;

    bool hasNextPage() const noexcept { return m_currentPage < m_countPages - 1; }

    bool hasPreviousPage() const noexcept { return m_currentPage > 0; }

    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void previousPage();

signals:
    void startPageChanged();
    void currentPageChanged();
    void countPagesChanged();
    void hasNextPageChanged();
    void hasPreviousPageChanged();

};

#endif // FRAMEPAGINATOR_H
