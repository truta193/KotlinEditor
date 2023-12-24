#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class Linker : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit Linker(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);
    void mousePressEvent(QTextDocument *document,
                         const QTextCursor &cursor,
                         const QTextBlock &block,
                         const QPoint &pos);

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat locationDescription;
};
