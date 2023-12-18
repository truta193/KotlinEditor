import QtQuick
import "components"

Rectangle {
    id: centralWidget
    width: parent.width
    height: parent.height
    anchors.fill: parent
    color: "#44475A"

    Rectangle {
        id: topBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 40
        color: "#282A36"

        TapHandler {
            onTapped: if (tapCount === 2) toggleMaximized()
            gesturePolicy: TapHandler.DragThreshold
        }
        DragHandler {
            grabPermissions: TapHandler.CanTakeOverFromAnything
            onActiveChanged: if (active) { window.startSystemMove(); }
        }

        ActionButton {
            id: runButton
            iconPath: "qrc:/icons/assets/ic_run.svg"
            anchors.top: parent.top
            anchors.right: minimizeButton.left
            anchors.rightMargin: 100
        }


        ActionButton {
            id: minimizeButton
            textText: "🗕"
            onClicked: {window.showMinimized()}
            anchors.top: parent.top
            anchors.right: maximizeButton.left
        }

        ActionButton {
            id: maximizeButton
            textText: window.visibility === Window.Maximized ? "🗗" : "🗖"
            onClicked: {window.toggleMaximized()}
            anchors.top: parent.top
            anchors.right: exitButton.left
        }
        ActionButton {
            id: exitButton
            textText: "🗙"
            onClicked: {Qt.callLater(Qt.quit)}
            anchors.top: parent.top
            anchors.right: parent.right
        }

    }

    Rectangle {
        id: mainWidget
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom

        color: "#00000000"

        EditorPane {
            id: inputPane
            width: centralWidget.width / 2 - 6
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        EditorPane {
            id: outputPane
            anchors.left: inputPane.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            readOnlyMode: true
        }

    }


}
