/**
  Object created to display and change time zones.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"

Text {
    id: timeZoneText
    text: qsTr(utcTimeZones[index]);
    textFormat: Text.RichText
    font: Style.settingPageTitle
    color: Style.primary_light

    property int index: 0
    property var utcTimeZones: [
        "Eastern Daylight Time",
        "Eastern Standard Time",
        "Central Daylight Time",
        "Central Standard Time",
        "Mountain Daylight Time",
        "Mountain Standard Time",
        "Pacific Daylight Time",
        "Pacific Standard Time",
        "Alaska Daylight Time",
        "Alaska Standard Time",
        "Hawaii-Aleutian Daylight Time",
        "Hawaii-Aleutian Standard Time"
    ];

    property var daylightSavingStates: [1,0,1,0,1,0,1,0,1,0,1,0];

    function getAbbreviation(timeZone) {
        if (timeZone === utcTimeZones[0])
        {
            return "EDT"
        }
        else if (timeZone === utcTimeZones[1])
        {
            return "EST";
        }
        else if (timeZone === utcTimeZones[2])
        {
            return "CDT";
        }
        else if (timeZone === utcTimeZones[3])
        {
            return "CST";
        }
        else if (timeZone === utcTimeZones[4])
        {
            return "MDT";
        }
        else if (timeZone === utcTimeZones[5])
        {
            return "MST";
        }
        else if (timeZone === utcTimeZones[6])
        {
            return "PDT";
        }
        else if (timeZone === utcTimeZones[7])
        {
            return "PST";
        }
        else if (timeZone === utcTimeZones[8])
        {
            return "AKDT";
        }
        else if (timeZone === utcTimeZones[9])
        {
            return "AKST";
        }
        else if (timeZone === utcTimeZones[10])
        {
            return "HADT";
        }
        else if (timeZone === utcTimeZones[11])
        {
            return "HAST";
        }
    }

    function getDaylight()
    {
        return daylightSavingStates[index];
    }
}


