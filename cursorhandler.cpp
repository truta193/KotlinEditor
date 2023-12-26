#include "cursorhandler.h"
#include <QRegularExpression>
#include <QTimer>

CursorHandler::CursorHandler(QObject *parent)
    : QObject{parent}
{
    connect(this, &CursorHandler::positionChanged, this, &CursorHandler::onPositionChanged);
}

Q_INVOKABLE void CursorHandler::setInput(QQuickItem *inputPane)
{
    this->inputPane = inputPane;
}

Q_INVOKABLE void CursorHandler::setOutput(QQuickItem *outputPane)
{
    this->outputPane = outputPane;
}

bool CursorHandler::validClick()
{
    if (inputPane == nullptr || outputPane == nullptr)
        return false;

    QString text = outputPane->property("text").toString();
    QRegularExpression exp("([^:\\n]+):(\\d+):(\\d+)");
    QRegularExpressionMatchIterator matchIterator = exp.globalMatch(text);

    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();

        int descPositionStart = match.capturedStart(0);
        int descPositionEnd = descPositionStart + match.captured(0).length();

        if (m_position >= descPositionStart && m_position <= descPositionEnd)
            return true;
    }

    return false;
}

void CursorHandler::moveCursor()
{
    if (inputPane == nullptr || outputPane == nullptr)
        return;

    QString outputText = outputPane->property("text").toString();
    QString inputText = inputPane->property("text").toString();

    QRegularExpression exp("([^:\\n]+):(\\d+):(\\d+)");
    QRegularExpressionMatchIterator matchIterator = exp.globalMatch(outputText);

    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        int descPositionStart = match.capturedStart(0);
        int descPositionEnd = descPositionStart + match.captured(0).length();
        int lineNumber = match.captured(2).toInt();
        int columnNumber = match.captured(3).toInt();

        if (m_position < descPositionStart || m_position > descPositionEnd)
            continue;

        QStringList lines = inputText.split("\n");
        int currentLength = 0;

        for (int i = 1; i < lineNumber; i++) {
            currentLength += lines[i - 1].length();
        }

        int newPos = currentLength + columnNumber - 2 + lineNumber;

        QMetaObject::invokeMethod(inputPane, "forceActiveFocus");

        inputPane->setProperty("activeFocus", true);
        QTimer::singleShot(0,
                           [this, newPos]() { inputPane->setProperty("cursorPosition", newPos); });

        break;
    }
}

int CursorHandler::getPosition()
{
    return m_position;
}

void CursorHandler::setPosition(int pos)
{
    if (pos != m_position) {
        m_position = pos;
        emit positionChanged();
    }
}

void CursorHandler::onPositionChanged()
{
    if (validClick())
        moveCursor();
}
