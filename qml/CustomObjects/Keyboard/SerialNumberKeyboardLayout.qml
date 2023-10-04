import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../CustomObjects"
import "../../CustomObjects/Keyboard"
import "../../Styles"

Rectangle {
    id: root_window

    function createFirstRow(row)
    {
        var x_coordinate = root_window.x;
        var y_coordinate = root_window.y;
        var component = Qt.createComponent("SerialNumberKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            for (var i = 0; i < row.length; i++)
            {
                var sprite = component.createObject(
                            root_window,
                            {
                                x: x_coordinate,
                                y: y_coordinate,
                                keyValue: row[i],
                                keyId: 0
                            });
                x_coordinate = x_coordinate + 100
            }
        }
    }

    function createSecondRow(row)
    {
        var x_coordinate = root_window.x + 48
        var y_coordinate = root_window.y + 100
        var component = Qt.createComponent("SerialNumberKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            for (var i = 0; i < row.length; i++)
            {
                var sprite = component.createObject(
                            root_window,
                            {
                                x: x_coordinate,
                                y: y_coordinate,
                                keyValue: row[i],
                                keyId: 0
                            })
                x_coordinate = x_coordinate + 100
            }
        }
    }

    function createThirdRow(row)
    {
        var x_coordinate = root_window.x + 100
        var y_coordinate = root_window.y + 200
        var component = Qt.createComponent("SerialNumberKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            for (var i = 0; i < row.length; i++)
            {
                var sprite = component.createObject(
                            root_window,
                            {
                                x: x_coordinate,
                                y: y_coordinate,
                                keyValue: row[i],
                                keyId: 0
                            })
                x_coordinate = x_coordinate + 100
            }
        }
    }

    function createFourthRow(row)
    {
        var x_coordinate = root_window.x + 148
        var y_coordinate = root_window.y + 300
        var component = Qt.createComponent("SerialNumberKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            for (var i = 0; i < row.length; i++)
            {
                var sprite = component.createObject(
                            root_window,
                            {
                                x: x_coordinate,
                                y: y_coordinate,
                                keyValue: row[i],
                                keyId: 0
                            })
                x_coordinate = x_coordinate + 100
            }
        }
    }

    function createBackSpaceKey()
    {
        var x_coordinate = root_window.x + 948
        var y_coordinate = root_window.y + 300
        var component = Qt.createComponent("SerialNumberKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite = component.createObject(
                        root_window,
                        {
                            width: 128,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: "Delete",
                            keyId: 1
                        })
        }
    }

    function createEscapeKey(popupStack)
    {
        var x_coordinate = root_window.x + 1076
        var y_coordinate = root_window.y + 300
        var component = Qt.createComponent("SerialNumberKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite = component.createObject(
                        root_window,
                        {
                            width: 128,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: "Close",
                            keyId: 2
                        })
        }
    }
}
