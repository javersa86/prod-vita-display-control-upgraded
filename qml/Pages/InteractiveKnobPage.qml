import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: root

    Component.onCompleted:
    {
        backend.setMode(ID.LISTENING_KNOB,1)
    }

    Component.onDestruction:
    {
        backend.setMode(ID.LISTENING_KNOB,0)
    }

    Connections
    {
        target: root.popupStack
        onDepthChanged:
        {
            if(popupStack.depth == 1)
            {
                backend.setMode(ID.LISTENING_KNOB,0)
            }
            else if(popupStack.depth == 0)
            {
                backend.setMode(ID.LISTENING_KNOB,1)
            }
        }
    }
}
