#include "shhandler.h"
#include "highlighter.h"
#include<QFile>

SHHandler::SHHandler(QObject *parent)
    : QObject{parent}
{}

void SHHandler::openFile(const QString& path)
{
    QUrl url(path);
    QFile file(url.toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream stream(&file);
    auto text = stream.readAll();
    setText(text);
    file.close();
}

void SHHandler::setDocument(QQuickTextDocument* document)
{
    auto highlighter = new Highlighter(document->textDocument());
    Q_UNUSED(highlighter)
}

QString SHHandler::text() const
{
    return m_text;
}

void SHHandler::setText(QString text)
{
    if (m_text != text) {
        m_text = text;
        emit textChanged(text);
    }
}
