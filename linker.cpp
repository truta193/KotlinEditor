#include "linker.h"
#include "theme.h"

Linker::Linker(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    Theme theme;
    HighlightingRule rule;

    locationDescription.setForeground(theme.cyan());
    rule.pattern = QRegularExpression("([^:\\n]+:\\d+:\\d+)");
    rule.format = locationDescription;
    highlightingRules.append(rule);
}

void Linker::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : highlightingRules)
    {
        QRegularExpression expression(rule.pattern);
        auto matches = expression.globalMatch(text);
        while (matches.hasNext())
        {
            auto match = matches.next();
            int index = match.capturedStart();
            int length = match.capturedLength();
            setFormat(index, length, rule.format);
        }
    }

    setCurrentBlockState(0);
}
