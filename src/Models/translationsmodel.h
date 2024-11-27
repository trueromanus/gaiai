#ifndef TRANSLATIONSMODEL_H
#define TRANSLATIONSMODEL_H

#include <QObject>
#include <QMap>

class TranslationsModel : public QObject
{
    Q_OBJECT
private:
    QMap<QString, QString> m_tasksContents { QMap<QString, QString>() };
    QMap<QString, QString> m_emailContents { QMap<QString, QString>() };

public:
    explicit TranslationsModel(QObject *parent = nullptr);

    QString getTasksTranslation(const QString& key) noexcept;

private:
    void readTasksContents(const QString& language);

signals:
};

#endif // TRANSLATIONSMODEL_H
