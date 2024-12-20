#ifndef GAMEEMAILMODEL_H
#define GAMEEMAILMODEL_H

#include <QObject>

class GameEmailModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasAttachments READ hasAttachments WRITE setHasAttachments NOTIFY hasAttachmentsChanged FINAL)
    Q_PROPERTY(bool isReaded READ isReaded WRITE setIsReaded NOTIFY isReadedChanged FINAL)
    Q_PROPERTY(QString hasAttachmentImage READ hasAttachmentImage NOTIFY hasAttachmentImageChanged FINAL)
    Q_PROPERTY(QString isReadedImage READ isReadedImage NOTIFY isReadedImageChanged FINAL)
    Q_PROPERTY(QString from READ from WRITE setFrom NOTIFY fromChanged FINAL)
    Q_PROPERTY(QString to READ to WRITE setTo NOTIFY toChanged FINAL)
    Q_PROPERTY(QString subject READ subject WRITE setSubject NOTIFY subjectChanged FINAL)
    Q_PROPERTY(QString group READ group WRITE setGroup NOTIFY groupChanged FINAL)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged FINAL)

private:
    bool m_hasAttachments { false };
    bool m_isReaded { false };
    QString m_from { "" };
    QString m_to { "" };
    QString m_subject { "" };
    QString m_group { "" };
    QString m_content { "" };

public:
    explicit GameEmailModel(QObject *parent = nullptr);

    bool hasAttachments() const noexcept { return m_hasAttachments; }
    void setHasAttachments(bool hasAttachments) noexcept;

    bool isReaded() const noexcept { return m_isReaded; }
    void setIsReaded(bool isReaded) noexcept;

    QString from() const noexcept { return m_from; }
    void setFrom(const QString& from) noexcept;

    QString to() const noexcept { return m_to; }
    void setTo(const QString& to) noexcept;

    QString subject() const noexcept { return m_subject; }
    void setSubject(const QString& subject) noexcept;

    QString group() const noexcept { return m_group; }
    void setGroup(const QString& group) noexcept;

    QString content() const noexcept { return m_content; }
    void setContent(const QString& content) noexcept;

    QString isReadedImage() const noexcept { return m_isReaded ? "columnreadedemail" : ""; }
    QString hasAttachmentImage() const noexcept { return m_hasAttachments ? "columnattachmentmail" : ""; }

signals:
    void hasAttachmentsChanged();
    void isReadedChanged();
    void fromChanged();
    void toChanged();
    void subjectChanged();
    void groupChanged();
    void hasAttachmentImageChanged();
    void isReadedImageChanged();
    void contentChanged();

};

#endif // GAMEEMAILMODEL_H
