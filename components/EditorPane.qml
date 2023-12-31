import QtQuick 2.15
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Window

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
            id: codeEditor
            text: if (isOutput) fileHandler.output; else fileHandler.script;
            anchors.margins: 12
            font.pointSize: 12
            font.family: "JetBrains Mono"
            color: theme.foreground
            selectionColor: theme.currentLine
            selectByMouse: !isOutput
            selectByKeyboard: !isOutput

            background: Rectangle {
                    color: "#00000000"
                }


            Component.onCompleted: {
                syntaxHandler.setDocument(codeEditor.textDocument, !isHighlightingEnabled);
                if (isOutput) {
                    cursorHandler.setOutput(codeEditor)
                } else {
                    cursorHandler.setInput(codeEditor)
                }
            }

            onFocusChanged: if (focus) {
                                border.color = theme.comment
                            } else {
                                border.color =  theme.background
                            }

            onTextChanged: {
                 if(!isOutput)
                    fileHandler.setScript(codeEditor.text)
            }

            Keys.onReleased: (event) =>  { if (isOutput) {
                                    fileHandler.inputChanged(event.text);
                                }}

            MouseArea {
                id:mouseArea
                anchors.fill: parent
                enabled: readOnlyMode
                onClicked: (mouse) => {
                               if (mouse.button !== Qt.LeftButton) return;
                               cursorHandler.position = codeEditor.positionAt(mouseX, mouseY)
                           }
            }
        }
    }
}
