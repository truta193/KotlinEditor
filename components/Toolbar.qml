import QtQuick 2.15
import QtQuick.Controls.Basic

Rectangle {
    id: toolbar
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    height: 40
    color: theme.background

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
        onReleased: {
            fileHandler.saveFile()
        }

        Connections {
            target: fileHandler

            function onIsBusyChanged() {
                if (fileHandler.isBusy === true)
                    runButton.enabled = false
                else
                    runButton.enabled = true
            }
        }
    }

    ActionButton {
        id: terminateButton
        iconPath: "qrc:/icons/assets/ic_stop.svg"
        anchors.top: parent.top
        anchors.right: runButton.left
        visible: false

        Connections {
            target: fileHandler

            function onIsBusyChanged() {
                if (fileHandler.isBusy === true)
                    terminateButton.visible = true
                else
                    terminateButton.visible = false
            }
        }

        onClicked: {
            fileHandler.terminate()
        }
    }

    Label {
        id: appLabel
        anchors.top: parent.top
        anchors.left: parent.left
        leftPadding: 12
        text: "Kotlin Script Editor"
        antialiasing: true
        verticalAlignment: TextInput.AlignVCenter
        height: toolbar.height
        color: theme.foreground
        font.pointSize: 14
        font.family: "JetBrains Mono"
    }

    ActionButton {
        id: minimizeButton
        iconPath: "qrc:/icons/assets/ic_minimize.svg"
        onClicked: {window.showMinimized()}
        anchors.top: parent.top
        anchors.right: maximizeButton.left
    }

    ActionButton {
        id: maximizeButton
        iconPath: window.visibility === Window.Maximized ? "qrc:/icons/assets/ic_maximize_back.svg" : "qrc:/icons/assets/ic_maximize.svg"
        onClicked: {window.toggleMaximized()}
        anchors.top: parent.top
        anchors.right: exitButton.left
    }

    ActionButton {
        id: exitButton
        iconPath: "qrc:/icons/assets/ic_close.svg"
        onClicked: {Qt.callLater(Qt.quit)}
        anchors.top: parent.top
        anchors.right: parent.right
    }
}
