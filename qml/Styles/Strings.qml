pragma Singleton
import QtQuick 2.12

QtObject {
    //names of settings
    property string pip_title: 'Peak Insp. Pressure'
    property string sp_title: 'Stacking Pressure'
    property string aux_title: 'Auxiliary'
    property string hum_title: 'Humidity'
    property string dp_title: 'Driving Pressure'
    property string rate_title: 'Rate'
    property string iTime_title: 'Inspiratory Time'
    property string o2_title: 'Oxygen'

    //units
    property string cmh2o: 'cmH<sub>2</sub>O'
    property string lpm: 'lpm'
    property string percent: '%'
    property string psi: "PSI"
    property string bpm: 'BPM'
    property string ml: 'ml'

    property string map: 'MAP'
    property string tv: 'TV'
    property string mv: 'MV'

}
