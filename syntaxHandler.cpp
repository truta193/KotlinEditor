#include "syntaxHandler.h"
#include "highlighter.h"
#include "linker.h"
#include<QFile>

SyntaxHandler::SyntaxHandler(QObject *parent)
    : QObject{parent}
{
}

void SyntaxHandler::openFile(const QString& path)
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

void SyntaxHandler::setDocument(QQuickTextDocument* document, bool isOutput)
{
    if (!isOutput)
    {
        auto highlighter = new Highlighter(document->textDocument());
        Q_UNUSED(highlighter)
    } else {
        auto highlighter = new Linker(document->textDocument());
        Q_UNUSED(highlighter)
    }

}

QString SyntaxHandler::getText()
{
    return m_text;
}

void SyntaxHandler::setText(QString text)
{
    if (m_text != text)
    {
        m_text = text;
        emit textChanged(text);
    }
}
