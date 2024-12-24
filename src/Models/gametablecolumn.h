#ifndef GAMETABLECOLUMN_H
#define GAMETABLECOLUMN_H

#include <QObject>

class GameTableColumn : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString field READ field WRITE setField NOTIFY fieldChanged FINAL)
    Q_PROPERTY(int columnWidth READ columnWidth WRITE setColumnWidth NOTIFY columnWidthChanged FINAL)
    Q_PROPERTY(QString formatter READ formatter WRITE setFormatter NOTIFY formatterChanged FINAL)
    Q_PROPERTY(bool selectable READ selectable WRITE setSelectable NOTIFY selectableChanged FINAL)
    Q_PROPERTY(int columnHeaderAlign READ columnHeaderAlign WRITE setColumnHeaderAlign NOTIFY columnHeaderAlignChanged FINAL)
    Q_PROPERTY(QString columnHeaderFormatter READ columnHeaderFormatter WRITE setColumnHeaderFormatter NOTIFY columnHeaderFormatterChanged FINAL)
    Q_PROPERTY(int columnHeaderWidth READ columnHeaderWidth WRITE setColumnHeaderWidth NOTIFY columnHeaderWidthChanged FINAL)
    Q_PROPERTY(int columnHeaderHeight READ columnHeaderHeight WRITE setColumnHeaderHeight NOTIFY columnHeaderHeightChanged FINAL)

private:
    QString m_title { "" };
    QString m_field { "" };
    int m_columnWidth { 0 };
    QString m_formatter { "" };
    bool m_selectable { false };
    int m_columnHeaderAlign { 0 };
    QString m_columnHeaderFormatter { "" };
    int m_columnHeaderWidth { 0 };
    int m_columnHeaderHeight { 0 };

public:
    explicit GameTableColumn(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    QString field() const noexcept { return m_field; }
    void setField(const QString& field) noexcept;

    int columnWidth() const noexcept { return m_columnWidth; }
    void setColumnWidth(int columnWidth) noexcept;

    QString formatter() const noexcept { return m_formatter; }
    void setFormatter(const QString& formatter) noexcept;

    bool selectable() const noexcept { return m_selectable; }
    void setSelectable(bool selectable) noexcept;

    int columnHeaderAlign() const noexcept { return m_columnHeaderAlign; }
    void setColumnHeaderAlign(int columnHeaderAlign) noexcept;

    QString columnHeaderFormatter() const noexcept { return m_columnHeaderFormatter; }
    void setColumnHeaderFormatter(const QString& columnHeaderFormatter) noexcept;

    int columnHeaderWidth() const noexcept { return m_columnHeaderWidth; }
    void setColumnHeaderWidth(int columnHeaderWidth) noexcept;

    int columnHeaderHeight() const noexcept { return m_columnHeaderHeight; }
    void setColumnHeaderHeight(int columnHeaderHeight) noexcept;


signals:
    void titleChanged();
    void fieldChanged();
    void columnWidthChanged();
    void formatterChanged();
    void selectableChanged();
    void columnHeaderAlignChanged();
    void columnHeaderFormatterChanged();
    void columnHeaderWidthChanged();
    void columnHeaderHeightChanged();

};

#endif // GAMETABLECOLUMN_H
