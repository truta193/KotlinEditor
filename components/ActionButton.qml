import QtQuick 2.15
import QtQuick.Controls.Basic
import "qrc:/theme/assets/Theme.js" as Colors

Button {
    id: actionButton
    width: 45
    height: 40
    property color defaultColor: "#00FFFFFF"
    property color hoverColor: "#44FFFFFF"
    property color clickColor: "#88FFFFFF"
    property color textColor: Colors.colors.foreground
    property string textText: ""

    contentItem: Text {
        id: buttonText
        color: textColor
        text: textText
        font.pointSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    QtObject {
        id: internal

        property var dynamicColor: if (actionButton.down) {
                                       actionButton.down ? actionButton.clickColor : actionButton.defaultColor
                                   } else {
                                       actionButton.hovered ? actionButton.hoverColor : actionButton.defaultColor
                                   }

    }

    background: Rectangle {
        id: buttonBackground
        color: internal.dynamicColor
    }
}
