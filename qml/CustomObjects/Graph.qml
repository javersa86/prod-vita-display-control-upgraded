import QtQuick 2.12
import QtCharts 2.3
import "../Styles"

Item {
    id: root
    function addData(index,pip,sp1){chart_view.addData(index, pip, sp1)}
    property int borderWidth
    property real sliding_bar_index: chart_view.lastX * (1/ xAxis.max) * width
    property int graph_state: 0
    property variant pip_window:[0,0,0,0]
    property int pip_window_index: 0
    property variant ymax
    property int sp1Setting;
    property int pipSetting;
    property int lineVisible

    Item {
        id: variables
        property var estimation // last filtered measurement
        property var q: 1 // measurement noise
        property var r: 1.1 //process noise
        property var cov
        property var stateVector: 1
        property var c: 1

    }
    function filter(z)
    {
        if (variables.estimation === undefined)
        {
            variables.estimation = (1/variables.c) * z
            variables.cov = (1/ variables.c) * variables.q * (1/variables.c)
        }
        else
        {
            const predX = predict()
            const predCov = uncertainty()

            const K = predCov * variables.c * (1 / (variables.c * predCov * variables.c + variables.q))
            variables.estimation = predX + K * (z - (variables.c * predX))
            variables.cov = predCov - (K * variables.c * predCov)
        }
        return variables.estimation
    }

    function predict()
    {
        return (variables.stateVector * variables.estimation)
    }

    function uncertainty()
    {
        return ((variables.stateVector * variables.cov) * variables.stateVector) + variables.r
    }

    function avg()
    {
        var pip_avg = 0;
        for (var m = 0; m < pip_window.length; m++)
        {
            pip_avg += pip_window[m];
        }
        pip_avg /= pip_window.length
        return pip_avg
    }

    onSp1SettingChanged:
    {
        sp1_setting.clear()
        sp1_setting.append(0,sp1Setting)
        sp1_setting.append(10000,sp1Setting)
    }

    onPipSettingChanged:
    {
        pip_setting.clear()
        pip_setting.append(0,pipSetting)
        pip_setting.append(10000,pipSetting)
    }

    ChartView {
        id: chart_view
        width: root.width
        height: root.height
        anchors.centerIn: parent
        backgroundColor: Style.transparent
        legend.visible: false
        legend.backgroundVisible: false
        property alias ymin: yAxis.min

        property int lastX: 0
        property int count:0
        margins { top: 0; bottom: 0; left: 0; right: 0 }
        plotArea: Qt.rect(0, 0, width, height)
        backgroundRoundness: 0
        antialiasing: true

        ValueAxis{
            id: xAxis
            min: 0
            max: 10000
            labelsVisible: false
            gridVisible:false
            lineVisible: false
        }
        ValueAxis{
            id: yAxis
            min: 0
            max: root.ymax
            labelsVisible: false
            gridVisible:false
            lineVisible:false
        }


        function addData(currX, pip, sp1){
            if(pip > root.ymax)
            {
                pip = root.ymax
            }

            if(sp1 > root.ymax)
            {
                sp1 = root.ymax
            }

            pip_window[pip_window_index] = pip;
            pip_window_index += 1;
            pip_window_index %= pip_window.length;


            filter(pip)
            pip_window[pip_window_index] = variables.estimation
            pip = avg()
            if (pip < 0) pip = 0
            if (sp1 < 0) sp1 = 0

            if(lastX > currX)
            {
                if(graph_state == 0)
                {
                    sp1_line2.removePoints(0,sp1_line2.count)
                    pip_line2.removePoints(0,pip_line2.count)
                    graph_state = 1;
                }

                else if (graph_state == 1)
                {
                    sp1_line1.removePoints(0,sp1_line1.count)
                    pip_line1.removePoints(0,pip_line1.count)
                    graph_state = 0;
                }
            }

            lastX = currX

            if(graph_state == 0)
            {
                //remove upcoming points
                while (sp1_line2.count > 0 && sp1_line2.at(0).x < currX)
                {
                    sp1_line2.remove(0);
                    pip_line2.remove(0);
                }
                //append new points
                sp1_line1.append(currX, sp1);
                pip_line1.append(currX, pip);
            }

            else
            {
                //remove upcoming points
                while (sp1_line1.count > 0 && sp1_line1.at(0).x < currX)
                {
                    sp1_line1.remove(0);
                    pip_line1.remove(0);
                }
                //append new points
                sp1_line2.append(currX, sp1);
                pip_line2.append(currX, pip);
            }


            count ++;
        }

        LineSeries{
            id: pip_line1
            axisX: xAxis
            axisY: yAxis
            color: Style.pip
            useOpenGL: true
            width: 3
        }
        LineSeries{
            id: sp1_line1
            axisX: xAxis
            axisY: yAxis
            color: Style.sp
            width: 3
            useOpenGL: true
            visible: root.lineVisible
        }
        LineSeries{
            id: pip_line2
            axisX: xAxis
            axisY: yAxis
            color: Style.pip
            useOpenGL: true
            width: 3
        }
        LineSeries{
            id: sp1_line2
            axisX: xAxis
            axisY: yAxis
            color: Style.sp
            width: 3
            useOpenGL: true
            visible: root.lineVisible
        }

        LineSeries
        {
            id: sp1_setting
            axisX:xAxis
            axisY:yAxis
            color:Style.sp
            width:3
            style: Qt.DashLine
            visible: root.lineVisible
        }

        LineSeries
        {
            id: pip_setting
            axisX:xAxis
            axisY:yAxis
            color:Style.pip
            width:3
            style: Qt.DashLine
        }
    }

    Rectangle {
        width: 12
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        color: Style.primary_dark
        x: root.sliding_bar_index - width / 2
    }

}
