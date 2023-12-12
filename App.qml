import QtQuick
import "components"
Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Kotlin Editor")
    flags: Qt.FramelessWindowHint| Qt.WindowMinimizeButtonHint | Qt.Window | Qt.WindowSystemMenuHint
    color: "#00000000"

    property int bw: 5

    function toggleMaximized() {
            if (window.visibility === Window.Maximized) {
                window.showNormal();
            } else {
                window.showMaximized();
            }
        }

    MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: {
                const p = Qt.point(mouseX, mouseY);
                const b = bw;
                if (p.x < b && p.y < b) return Qt.SizeFDiagCursor;
                if (p.x >= width - b && p.y >= height - b) return Qt.SizeFDiagCursor;
                if (p.x >= width - b && p.y < b) return Qt.SizeBDiagCursor;
                if (p.x < b && p.y >= height - b) return Qt.SizeBDiagCursor;
                if (p.x < b || p.x >= width - b) return Qt.SizeHorCursor;
                if (p.y < b || p.y >= height - b) return Qt.SizeVerCursor;
            }
            acceptedButtons: Qt.NoButton
        }

        DragHandler {
            id: resizeHandler
            grabPermissions: TapHandler.TakeOverForbidden
            target: null
            onActiveChanged: if (active) {
                const p = resizeHandler.centroid.position;
                const b = bw + 10;
                let e = 0;
                if (p.x < b) { e |= Qt.LeftEdge }
                if (p.x >= width - b) { e |= Qt.RightEdge }
                if (p.y < b) { e |= Qt.TopEdge }
                if (p.y >= height - b) { e |= Qt.BottomEdge }
                window.startSystemResize(e);
            }
        }

    Main {
        anchors.fill: parent
        anchors.margins: window.visibility === Window.Windowed ? bw : 0
    }
}
