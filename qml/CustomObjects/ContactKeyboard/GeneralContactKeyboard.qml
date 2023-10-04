import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../CustomObjects"
import "../../CustomObjects/ContactKeyboard"
import "../../Styles"

Rectangle
{
    id: root

    property int layoutState: 0
    property int allCapState: 0

    ContactKeyboardLayout
    {
        id: upperCase

        visible: layoutState === 0

        Component.onCompleted:
        {
            createFirstRow("QWERTYUIOP")
            createSecondRow("ASDFGHJKL")
            createThirdRow("ZXCVBNM")
            createSpaceBar()
            createBackSpaceKey()
            createShiftKey(1, "Shift")
            createSwitchKey(2,"123")
        }
    }

    ContactKeyboardLayout
    {
        id: lowerCase

        visible: layoutState === 1

        Component.onCompleted:
        {
            createFirstRow("qwertyuiop")
            createSecondRow("asdfghjkl")
            createThirdRow("zxcvbnm")
            createSpaceBar()
            createBackSpaceKey()
            createShiftKey(0, "shift")
            createSwitchKey(2,"123")
        }
    }

    ContactKeyboardLayout
    {
        id: numbersSymbols1

        visible: layoutState === 2

        Component.onCompleted: {
            createFirstRow("1234567890")
            createSecondRow("-/:;?&@")
            createThirdRow(".,!\'\"()")
            createSpaceBar()
            createBackSpaceKey()
            createShiftKey(3,"#+=")
            createSwitchKey(1,"abc")
        }
    }

    ContactKeyboardLayout
    {
        id: numbersSymbols2

        visible: layoutState === 3

        Component.onCompleted: {
            createFirstRow("[]{}#%^*+=")
            createSecondRow("$_\\|~<>`")
            createThirdRow(".,!\'\"()")
            createSpaceBar()
            createBackSpaceKey()
            createShiftKey(2,"123")
            createSwitchKey(1,"abc")
        }
    }
}
