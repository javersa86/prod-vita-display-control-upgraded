import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../CustomObjects"
import "../../CustomObjects/ContactKeyboard"
import "../../Styles"

Rectangle {
    id: root_window

    function createFirstRow(row)
    {
        var x_coordinate = root_window.x;
        var y_coordinate = root_window.y;
        var component = Qt.createComponent("ContactKeyboardButton.qml");
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
        var y_coordinate = root_window.y + 100//96
        var component = Qt.createComponent("ContactKeyboardButton.qml");
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
        var x_coordinate = root_window.x + 148
        var y_coordinate = root_window.y + 200
        var component = Qt.createComponent("ContactKeyboardButton.qml");
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

    function createSpaceBar()
    {
        var x_coordinate = root_window.x + 248
        var y_coordinate = root_window.y + 300
        var component = Qt.createComponent("ContactKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite = component.createObject(
                        root_window,
                        {
                            width: 496,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: " ",
                            keyId: 0
                        })
        }
    }

    function createBackSpaceKey()
    {
        var x_coordinate = root_window.x + 148 + 700; // + 16;
        var y_coordinate = root_window.y + 200;
        var component = Qt.createComponent("ContactKeyboardButton.qml");
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

    function createReturnKey()
    {
        var x_coordinate = root_window.x + 248 + 500
        var y_coordinate = root_window.y + 300
        var component = Qt.createComponent("ContactKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite = component.createObject(
                        root_window,
                        {
                            width: 112,
                            backgroundColor: Style.affirmative,
                            outlineColor: Style.unclickable_border,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: "Next",
                            keyId: 2
                        })
        }
    }

    function createShiftKey(keyboardState,tmp)
    {
        var x_coordinate = root_window.x + 16;
        var y_coordinate = root_window.y + 200;
        var component = Qt.createComponent("ContactKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite = component.createObject(
                        root_window,
                        {
                            width: 128,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: tmp,
                            keyId: 3,
                            keyboardState: keyboardState
                        })
        }
    }

    function createSwitchKey(keyboardState,tmp)
    {
        var x_coordinate = root_window.x + 132;
        var y_coordinate = root_window.y + 300;
        var component = Qt.createComponent("ContactKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite = component.createObject(
                        root_window,
                        {
                            width: 112,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: tmp,
                            keyId: 4,
                            keyboardState: keyboardState
                        })
        }
    }

    function createCancelKey()
    {
        var x_coordinate = root_window.x;
        var y_coordinate = root_window.y + 300;
        var component = Qt.createComponent("ContactKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite = component.createObject(
                        root_window,
                        {
                            width: 128,
                            backgroundColor: Style.cancel,
                            outlineColor: Style.unclickable_border,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: "Cancel",
                            keyId: 5
                        })
        }
    }

    function createDoneKey()
    {
        var x_coordinate = root_window.x + 148 + 700 + 16;
        var y_coordinate = root_window.y + 300;
        var component = Qt.createComponent("ContactKeyboardButton.qml");
        if (component.status === Component.Ready)
        {
            var sprite =component.createObject(
                        root_window,
                        {
                            width: 128,
                            backgroundColor: Style.affirmative,
                            outlineColor: Style.unclickable_border,
                            x: x_coordinate,
                            y: y_coordinate,
                            keyValue: "Done",
                            keyId: 6
                        })
        }
    }
}
