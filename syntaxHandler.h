#pragma once

#include <QObject>
#include <QQuickTextDocument>

class SyntaxHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)

private:
    QString m_text;

public:
    explicit SyntaxHandler(QObject *parent = nullptr);

    ~SyntaxHandler() {}

    Q_INVOKABLE void openFile(const QString& path);
    Q_INVOKABLE void setDocument(QQuickTextDocument* document);


public slots:
    QString getText();
    void setText(QString text);

signals:
    void textChanged(QString text);

};

