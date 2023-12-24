#include "cursorhandler.h"
#include <QRegularExpression>
#include <QTimer>

CursorHandler::CursorHandler(QObject *parent)
    : QObject{parent}
{
    connect(this, &CursorHandler::positionChanged, this, &CursorHandler::onPositionChanged);
}


// if (mouse.button !== Qt.LeftButton) return;
// var regex = /([^:\n]+):(\d+):(\d+)/;
// var match = regex.exec(text);
// if (match === null) return;
// //match[2] is x match[3] is y
// console.info(match)

//     var descPositionStart = codeEditor.text.indexOf(match[0])
//       var descPositionEnd = descPositionStart + match[0].length
//                           console.info(descPositionStart, descPositionEnd)

//                           var position = codeEditor.positionAt(mouseX, mouseY)
//       console.info(position)

//       if (position < descPositionStart || position > descPositionEnd) return;

// var lines = codeEditor.text.split("\n")
// var currentLength = 0
// var line = 0;
// for (let i = 0; i < lines.length; i++) {
//     currentLength += lines[i].length
//     if (position > currentLength) {
//         break;
//     }
//     line++;
// }

Q_INVOKABLE void CursorHandler::setInput(QQuickItem* inputPane)
{
    this->inputPane = inputPane;
}

Q_INVOKABLE void CursorHandler::setOutput(QQuickItem* outputPane)
{
    this->outputPane = outputPane;
}
// if (mouse.button !== Qt.LeftButton) return;
// var regex = /([^:\n]+):(\d+):(\d+)/;
// var match = regex.exec(text);
// if (match === null) return;
// //match[2] is x match[3] is y
// console.info(match)

//     var descPositionStart = codeEditor.text.indexOf(match[0])
//       var descPositionEnd = descPositionStart + match[0].length
//                           console.info(descPositionStart, descPositionEnd)

//                           var position = codeEditor.positionAt(mouseX, mouseY)
//       console.info(position)

//       if (position < descPositionStart || position > descPositionEnd) return;

// var lines = codeEditor.text.split("\n")
// var currentLength = 0
// var line = 0;
// for (let i = 0; i < lines.length; i++) {
//     currentLength += lines[i].length
//     if (position > currentLength) {
//         break;
//     }
//     line++;
// }
bool CursorHandler::validClick() {
    if (inputPane == nullptr || outputPane == nullptr) return false;

    QString text = outputPane->property("text").toString();
    QRegularExpression exp("([^:\\n]+):(\\d+):(\\d+)");
    QRegularExpressionMatchIterator matchIterator = exp.globalMatch(text);

    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();

        int descPositionStart = match.capturedStart(0);
        int descPositionEnd = descPositionStart + match.captured(0).length();

        // Assuming m_position is the cursor position you want to check
        if (m_position >= descPositionStart && m_position <= descPositionEnd) {
            qInfo() << "Match found at position" << m_position;
            return true;
        }
    }

    return false;
}

void CursorHandler::moveCursor() {
    if (inputPane == nullptr || outputPane == nullptr) return;
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

        if (m_position < descPositionStart || m_position > descPositionEnd) continue;

        QStringList lines = inputText.split("\n");
        int currentLength = 0;

        for (int i = 1; i < lineNumber; i++) {
            currentLength += lines[i-1].length();
        }

        int newPos = currentLength + columnNumber - 2 + lineNumber;

        QMetaObject::invokeMethod(inputPane, "forceActiveFocus");

        inputPane->setProperty("activeFocus", true);
        QTimer::singleShot(0, [this, newPos]() {
            inputPane->setProperty("cursorPosition", newPos);
        });

        break;
    }
}


int CursorHandler::getPosition()
{
    return m_position;
}

void CursorHandler::setPosition(int pos)
{
    if (pos != m_position)
    {
        m_position = pos;
        emit positionChanged();
    }
}

void CursorHandler::onPositionChanged() {
    if (validClick()) {
        qInfo() <<"valid click";
        moveCursor();
    }
}
