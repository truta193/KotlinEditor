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

    QRegularExpression exp("([^:\\n]+):(\\d+):(\\d+)");
    QRegularExpressionMatch match = exp.match(outputPane->property("text").toString());
    if (!match.hasMatch()) {
        return false;
    }

    int descPositionStart = outputPane->property("text").toString().indexOf(match.captured(1));
    int descPositionEnd = descPositionStart + match.captured(1).length();
    qInfo() << m_position << descPositionStart << descPositionEnd;
    if (m_position < descPositionStart || m_position > descPositionEnd) return false;

    return true;
}

void CursorHandler::moveCursor() {
    if (inputPane == nullptr || outputPane == nullptr) return;
    QRegularExpression exp("([^:\\n]+):(\\d+):(\\d+)");
    QRegularExpressionMatch match = exp.match(outputPane->property("text").toString());
    if (!match.hasMatch()) {
        return;
    }

    int lineNumber = match.captured(2).toInt();
    int columnNumber = match.captured(3).toInt();

    QStringList lines = inputPane->property("text").toString().split("\n");
    int currentLength = 0;

    for (int i = 1; i < lineNumber; i++) {
        currentLength += lines[i-1].length();
    }

    int newPos = currentLength + columnNumber - 1;

    QMetaObject::invokeMethod(inputPane, "forceActiveFocus");

    inputPane->setProperty("activeFocus", true);
    QTimer::singleShot(50, [this, newPos]() {
        inputPane->setProperty("cursorPosition", newPos);
    });
    //inputPane->setProperty("cursorPosition", currentLength + columnNumber);
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
