import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import NotificationIndex 1.0
import IDs 1.0

Rectangle{
    id: root
    color: Style.transparent

    width: 1079
    height: 800

    property var warnings
    property ListModel model: ListModel{}
    property StackView popupStack
    property int topWarning: 0

    Timer
    {
        id: warningTimer
        interval: 30
        onTriggered:
        {
            warningListView.setColors()
        }
    }

    function populateWarnings()
    {
        model.clear()
        var numWarnings = warnings.length

        for(var i = 0; i < numWarnings; i++)
        {
            model.append({warningClassVal: warning_manager.getWarningClass(warnings[i]),
                         warningBehaviorVal: warning_manager.getWarningBehavior(warnings[i]),
                         warningActiveVal: warning_manager.getWarningActive(warnings[i]),
                         warningColorVal: warning_manager.getWarningColor(warnings[i]),
                         titleVal: warning_manager.getWarningTitle(warnings[i]),
                         descriptionVal: warning_manager.getWarningDesc(warnings[i]),
                         clearTextVal: warning_manager.getWarningClearText(warnings[i]),
                         warningIDVal: warnings[i],
                         warningIndexVal: i})
        }
    }

    onWarningsChanged:
    {
        if (warnings.length <=1)
        {
            warningListView.expanded = false
        }

        populateWarnings()
        if(warnings.length)
        {
            topWarning = warnings[0]
        }


        warningTimer.start()
    }

    Rectangle
    {
        id: roundedBottom
        width: warningListView.expanded && warnings.length > 3 ? parent.width + 40 : parent.width
        height: 20
        radius: 10
        color: warningListView.expanded ? warningListView.bottomColor : warning_manager.getWarningColor(topWarning)
    }

    ListView
    {
        id: warningListView
        width: expanded && warnings.length > 3 ? parent.width + 40 : parent.width
        height: expanded ? warnings.length > 3 ? 3 * 65 : warnings.length * 65 : 65
        interactive: expanded
        boundsBehavior: Flickable.StopAtBounds
        model: root.model
        visible: warnings.length !== 0
        property bool expanded
        snapMode: ListView.SnapOneItem
        property color bottomColor
        property color topColor
        delegate: WarningBannerModel {
            warningClass: warningClassVal;
            warningBehavior: warningBehaviorVal;
            warningActive: warningActiveVal;
            warningColor: warningColorVal;
            title: titleVal;
            description: descriptionVal;
            warningID: warningIDVal;
            height: 65; width: warningListView.width;
            clearText: clearTextVal;
            warningIndex: warningIndexVal;
            popupStack: root.popupStack;
            warningExpanded: warningListView.expanded && warnings.length > 3
        }
        clip: true

        ScrollBar.vertical: ScrollBar {
            id: vbar
            active: warningListView.expanded
            policy: warningListView.expanded && warnings.length > 3 ? ScrollBar.AlwaysOn :ScrollBar.AlwaysOff
            hoverEnabled: true

            contentItem: Rectangle {
                implicitWidth: 40
                radius: width / 4
                color: vbar.pressed ? Style.numeric_ui_unit : Style.primary_light
            }
        }

        onHeightChanged:
        {
            roundedBottom.y = height - roundedBottom.height / 2
        }

        onContentYChanged:
        {
            setColors()
        }

        onExpandedChanged:
        {
            setColors()
        }

        onAddChanged:
        {
            setColors()
        }

        onRemoveChanged:
        {
            setColors()
        }


        function setColors()
        {

            var bottomY = contentY + 64 + 65 * 2
            while(! itemAt(contentX,bottomY) && bottomY > 0)
            {
                bottomY -= 65;
            }
            if( itemAt(contentX, bottomY) )
            {
                bottomColor = itemAt(contentX, bottomY).warningColor
            }
            if( itemAt(contentX, contentY) )
            {
                topColor = itemAt(contentX, contentY).warningColor
            }
        }
    }
    Rectangle
    {
        id: numActiveWarningsFlag
        width: 75
        height: 65
        radius: 5
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 5
        color: Style.transparent

        WarningBannerAlarmIcon
        {
            id: numActiveRoot
            anchors.top: parent.top
            anchors.left: parent.left
            visible: warnings.length === 1

            onClicked:
            {
                warningListView.expanded = !warningListView.expanded
            }
        }
        WarningBannerAlarmIcons
        {
            id: numActiveRoot1
            anchors.top: parent.top
            anchors.left: parent.left
            visible: warnings.length > 1 && warnings.length !== 1

            numWarnings: warnings.length

            onClicked:
            {
                warningListView.expanded = !warningListView.expanded
            }
        }
    }


}
