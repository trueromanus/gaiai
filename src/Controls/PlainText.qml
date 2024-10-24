import QtQuick

Text {
    font.family: "Arial"

    property real fontSize: 12
    readonly property real textMultiplier: systemSettings.textMultiplier

    onFontSizeChanged: {
        font.pixelSize = fontSize * textMultiplier;
    }

    onTextMultiplierChanged: {
        font.pixelSize = fontSize * textMultiplier;
    }

}
