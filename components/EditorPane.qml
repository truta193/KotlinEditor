import QtQuick 2.15
import QtQuick.Controls.Basic
import QtQuick.Layouts
Rectangle {
    property alias readOnlyMode: codeEditor.readOnly

    width: parent.width
    height: parent.height
    anchors.margins: 12
    border.width: 3
    border.color: theme.background
    radius: 12
    color: theme.background

    ScrollView {
        id: sv
        anchors.fill: parent

        TextArea {
            id: codeEditor
            anchors.margins: 12
            font.pointSize: 12
            font.family: "JetBrains Mono"
            color: theme.foreground
            selectionColor: theme.currentLine
            Component.onCompleted: {
                shHandler.setDocument(codeEditor.textDocument)
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
            onTextChanged: { fHandler.setScript(codeEditor.text)}

        }
    }





}
