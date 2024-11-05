import QtQuick
import QtQuick.Shapes

Shape {
    id: root
    width: 1

    property alias dashColor: shapePath.strokeColor

    ShapePath {
        id: shapePath
        strokeStyle: ShapePath.DashLine
        dashPattern: [ 1, 2 ]
        startX: 0
        startY: 0
        PathLine {
            x: 0
            y: root.height
        }
    }
}
