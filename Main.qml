import QtQuick
import "components"
import QtQuick.Controls.Basic
import QtQuick.Layouts

Rectangle {
    id: centralWidget
    width: parent.width
    height: parent.height
    anchors.fill: parent
    color: theme.currentLine

    Toolbar {
        id: toolBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }

    Rectangle {
        id: mainWidget
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom

        color: "#00000000"

        EditorPane {
            id: inputPane
            width: centralWidget.width / 2 - 6
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            isOutput: false
            isHighlightingEnabled: true
        }

        EditorPane {
            id: outputPane
            anchors.left: inputPane.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            isOutput: true
            isHighlightingEnabled: false
        }
    }
}
