import QtQuick 2.12
import "../Styles"

Rectangle
{
    id: box
    height: 320
    width: 640
    property int startX: width / 2
    property int startY: - height
    property int desiredX: width / 2
    property int desiredY: 100
    x: startX
    y: startY



    states: [
            State {
                name: "moveOut"; when: box.moveOut
                PropertyChanges { target: box; y: startY; x: startX}
            },
            State {
                name: "moveIn"; when: box.moveIn
                PropertyChanges { target: box; x: desiredX; y: desiredY }
            }
        ]

    transitions: [
        Transition {
            to: "moveOut"
            NumberAnimation { properties: "x,y"; easing.type: Easing.InOutQuad; duration: 400; loops: 1 }
        },
        Transition {
            to: "moveIn"
            NumberAnimation { properties: "x,y"; easing.type: Easing.InOutQuad; duration: 400; loops: 1 }
        }
    ]
}
