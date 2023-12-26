#include "include/highlighter.h"
#include "include/theme.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    Theme theme;
    HighlightingRule rule;


    keywordFormat.setForeground(theme.pink());
    QStringList keywordPatterns;
    keywordPatterns <<
        "\\bas\\b" <<
        "\\bas?\\b" <<
        "\\bbreak\\b" <<
        "\\bclass\\b" <<
        "\\bcontinue\\b" <<
        "\\bdo\\b" <<
        "\\belse\\b" <<
        "\\bfalse\\b" <<
        "\\bfor\\b" <<
        "\\bfun\\b" <<
        "\\bif\\b" <<
        "\\bin\\b" <<
        "\\binterface\\b" <<
        "\\bis\\b" <<
        "\\bnull\\b" <<
        "\\bobject\\b" <<
        "\\bpackage\\b" <<
        "\\breturn\\b" <<
        "\\bsuper\\b" <<
        "\\bthis\\b" <<
        "\\bthrow\\b" <<
        "\\btrue\\b" <<
        "\\btry\\b" <<
        "\\btypealias\\b" <<
        "\\bval\\b" <<
        "\\bvar\\b" <<
        "\\bwhen\\b" <<
        "\\bwhile\\b";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }


    functionFormat.setForeground(theme.green());
    rule.pattern = QRegularExpression("\\b[a-z][A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);


    classFormat.setForeground(theme.cyan());
    rule.pattern = QRegularExpression("\\b[A-Z][a-zA-Z]*\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);


    numberFormat.setForeground(theme.purple());
    rule.pattern = QRegularExpression("\\b\\d+(\\.\\d+)?\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    methodFormat.setForeground(theme.purple());
    rule.pattern = QRegularExpression("\\b\\w+\\(.*?\\)\\b");
    rule.format = methodFormat;
    highlightingRules.append(rule);

    parenthesisFormat.setForeground(theme.purple());
    rule.pattern = QRegularExpression("[()\\[\\]{}]");
    rule.format = parenthesisFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(theme.yellow());
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(theme.comment());
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(theme.comment());

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
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

    int startIndex = 0;
    if (previousBlockState() != 1)
    {
        auto match = commentStartExpression.match(text);
        startIndex = match.hasMatch() ? match.capturedStart() : -1;
    }

    while (startIndex >= 0)
    {
        auto match = commentEndExpression.match(text, startIndex);
        int endIndex = match.hasMatch() ? match.capturedEnd() : -1;

        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex;
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);

        startIndex = commentStartExpression.match(text, startIndex + commentLength).capturedStart();
    }
}
