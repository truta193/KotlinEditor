#ifndef SYNTAXHANDLER_H
#define SYNTAXHANDLER_H

#include <QObject>
#include <QQuickTextDocument>

class SyntaxHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit SyntaxHandler(QObject *parent = nullptr);

    ~SyntaxHandler() {}

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

#endif // SYNTAXHANDLER_H
