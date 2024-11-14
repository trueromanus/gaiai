import QtQuick
import QtQuick.Shapes

Shape {
    id: shape
    height: 1

    property alias dashColor: shapePath.strokeColor

    ShapePath {
        id: shapePath
        strokeStyle: ShapePath.DashLine
        dashPattern: [ 1, 2 ]
        startX: 0
        startY: 0
        PathLine {
            x: shape.width
            y: 0
        }
    }
}
