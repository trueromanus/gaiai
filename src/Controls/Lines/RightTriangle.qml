import QtQuick
import QtQuick.Shapes

Shape {
    id: root
    width: 10
    height: 20

    property color shapeColor: "black"

    ShapePath {
        strokeWidth: 0
        strokeColor: root.shapeColor
        fillGradient: LinearGradient {
            x1: 0
            y1: 0
            x2: 0
            y2: 20
            GradientStop { position: 0; color: root.shapeColor }
            GradientStop { position: 1; color: root.shapeColor }
        }
        startX: 0
        startY: 0
        PathLine { x: 10; y: 10 }
        PathLine { x: 0; y: 20 }
    }
}
