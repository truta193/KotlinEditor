#ifndef SHHANDLER_H
#define SHHANDLER_H

#include <QObject>
#include <QQuickTextDocument>

class SHHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit SHHandler(QObject *parent = nullptr);

    ~SHHandler() {}

    Q_INVOKABLE void openFile(const QString& path);
    Q_INVOKABLE void setDocument(QQuickTextDocument* document);
    QString text() const;

public slots:
    void setText(QString text);

signals:
    void textChanged(QString text);

private:
    QString m_text;
};

#endif // SHHANDLER_H
