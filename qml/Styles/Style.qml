pragma Singleton
import QtQuick 2.12

QtObject {

    property FontLoader roboto_black: FontLoader {source: "../fonts/Roboto-Black.ttf"}
    property FontLoader roboto_bold: FontLoader {source: "../fonts/Roboto-Bold.ttf"}
    property FontLoader roboto_medium: FontLoader {source: "../fonts/Roboto-Medium.ttf"}

    property color primary: "#3D96A8"
    property color secondary: "#6FCC68"
    property color tertiary: "#FAE061"
    property color pip: "#C12E30"
    property color sp: "#0E6CBF"
    property color primary_dark: "#202531"
    property color primary_light: "#E3ECFB"
    property color primary_dark_transluscent: "#8C202531"
    property color general_measured_value: "#E6E3ECFB"
    property color general_set_display: "#4A90E2"
    property color scale_rectangle_border: "#66F2F2F2"
    property color unit: "#99E3ECFB"
    property color minMax: "#BFE3ECFB"
    property color transparent: "#00000000"
    property color unclickable_border: "#313C51"
    property color statistic_value: "#E6E3ECFB"
    property color mode_active: "#1F2A34"
    property color mode_inactive: "#506385"
    property color mode_label:"#3D96A8"
    property color primary_light_selected: "#1AE3ECFB"
    property color numeric_ui_unit: "#A1A7B2"
    property color affirmative: "#4AE287"
    property color affirmative_transluscent: "#804AE287"
    property color dissident: "#FF223D"
    property color cancel: "#E24A5F"
    property color primary_light_disabled: "#8CE3ECFB"
    property color patient_warning: "#F24C26"
    property color system_warning: "#4A5AE4"
    property color notice: "#E2C044" //"#FBA455"
    property color warning_decription: "#8CE3ECFB"
    property color menu_color: "#313C51"
    property color mode_active_warning: "#FBA455"
    property color o2_color: "#6FCC68" //"#309c30"

    property color help_icon_selected: "#804A90E2"
    property color mode_active_warning_selected: "#8CFBA455"
    property color general_set_display_selected: "#8C4A90E2"

    property font measuredFont: Qt.font({
        family: roboto_black.name,
        styleName: "Black",
        pixelSize: 96,
        weight: 900
    })

    property font setFont: Qt.font({
        family: roboto_bold.name,
        styleName: "Bold",
        pixelSize: 32
    })

    property font titleFont: Qt.font({
        family: roboto_bold.name,
        styleName: "Bold",
        pixelSize: 18
    })

    property font unitFont: Qt.font({
        family: roboto_bold.name,
        styleName:"Bold",
        pixelSize: 18
    })

    property font minMaxFont: Qt.font({
        family: roboto_bold.name,
        styleName: "Bold",
        pixelSize: 18
    })

    property font statisticFont: Qt.font({
        family: roboto_black.name,
        styleName:"Black",
        pixelSize: 34
    })

    property font statisticFontSmaller: Qt.font({
        family: roboto_black.name,
        styleName:"Black",
        pixelSize: 30
    })

    property font numberButtonFont: Qt.font({
        family: roboto_medium.name,
        styleName:"Medium",
        pixelSize: 24
    })

    property font numericUiDisplayFont: Qt.font({
        family: roboto_medium.name,
        styleName:"Medium",
        pixelSize: 32
    })

    property font buttonFont: Qt.font({
        family: roboto_medium.name,
        styleName:"Medium",
        pixelSize: 17
    })

    property font buttonFontUnderlined: Qt.font({
        family: roboto_medium.name,
        styleName:"Medium",
        pixelSize: 17,
        underline: true
    })

    property font cancel_font: Qt.font({
        family: roboto_medium.name,
        styleName:"Medium",
        pixelSize: 18,
        underline: true
    })

    property font warningFlag: Qt.font({
        family: roboto_black.name,
        styleName:"Black",
        pixelSize: 24
    })

    property font warningFlagMini: Qt.font({
        family: roboto_black.name,
        styleName:"Black",
        pixelSize: 18
    })

    property font warningTitle: Qt.font({
        family: roboto_medium.name,
        styleName:"Medium",
        pixelSize: 24
    })

    property font warningDescFont: Qt.font({
        family: roboto_bold.name,
        styleName:"Bold",
        pixelSize: 18
    })

    property font pageTitle: Qt.font({
        family: roboto_bold.name,
        styleName:"Bold",
        pixelSize: 36
    })

    property font settingPageTitle: Qt.font({
        family: roboto_bold.name,
        styleName:"Bold",
        pixelSize: 24
    })

    property font loadingText: Qt.font({
        family: roboto_black.name,
        styleName: "Black",
        pixelSize: 72,
        weight: 900
    })

    property font smallButtonFont: Qt.font({
        family: roboto_medium.name,
        styleName: "Medium",
        pixelSize: 12
    })

}
