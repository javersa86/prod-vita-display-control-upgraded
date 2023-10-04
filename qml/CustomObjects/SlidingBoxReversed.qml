import QtQuick 2.12
import "../Styles"

Rectangle
{
    id: box
    color: Style.primary_dark
    width: 1280; height: 500
    border.color: Style.primary_light
    border.width: 4
    property int startX: 0
    property int startY: 800
    property int desiredX: 0
    property int desiredY: 300
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
