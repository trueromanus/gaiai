#ifndef GAMETABLECOLUMN_H
#define GAMETABLECOLUMN_H

#include <QObject>

class GameTableColumn : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString field READ field WRITE setField NOTIFY fieldChanged FINAL)
    Q_PROPERTY(int columnWidth READ columnWidth WRITE setColumnWidth NOTIFY columnWidthChanged FINAL)

private:
    QString m_title { "" };
    QString m_field { "" };
    int m_columnWidth { 0 };

public:
    explicit GameTableColumn(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    QString field() const noexcept { return m_field; }
    void setField(const QString& field) noexcept;

    int columnWidth() const noexcept { return m_columnWidth; }
    void setColumnWidth(int columnWidth) noexcept;

signals:
    void titleChanged();
    void fieldChanged();
    void columnWidthChanged();

};

#endif // GAMETABLECOLUMN_H
