import QtQuick 2.15
import QtQuick.Controls.Basic
import QtQuick.Layouts
Rectangle {
    property alias readOnlyMode: codeEditor.readOnly
    property alias text: codeEditor.text
    property bool isHighlightingEnabled: true
    property bool isOutput: false

    width: parent.width
    height: parent.height
    anchors.margins: 12
    border.width: 3
    border.color: theme.background
    radius: 12
    color: theme.background

    ScrollView {
        id: scrollView
        anchors.fill: parent

        TextArea {
            text: if (isOutput) fileHandler.output; else fileHandler.script;
            id: codeEditor
            anchors.margins: 12
            font.pointSize: 12
            font.family: "JetBrains Mono"
            color: theme.foreground
            selectionColor: theme.currentLine
            Component.onCompleted: {
                if (isHighlightingEnabled)
                    syntaxHandler.setDocument(codeEditor.textDocument)
            }
            background: Rectangle {
                    color: "#00000000"
                }

            selectByMouse: true
            selectByKeyboard: true
            onFocusChanged: if (focus) {
                                border.color = theme.comment
                            } else {
                                border.color =  theme.background
                            }

            onTextChanged: {
                if(!isOutput)
                    fileHandler.setScript(codeEditor.text)
            }

        }
    }
}
