 * Modules for all backend components.

/**
 * @ingroup backendModule
 * @defgroup backendController Backend Controller
 * @brief Documentation for backend of the Display Controller.
 * @details
 * @{
 *
 * \subsection backendController Backend Controller
 *
 * \subsubsection backendController_description Backend Description
 *
 * The backend controller is where all activity occurs from the user inputs on the Graphical User Interface and the updates from the system controller. Note that all activities interact with all the managers on the application; see State Manager, Warnings and \htmlonly Warning \endhtmlonly Manager, and Log Manager and other Managers for detail on how data and log entries are saved on the display.
 *
 * \subsubsection backendController_request_function Backend Request Function
 *
 * Requests functions construct Op Code Requests that are sent to the system controller through the \htmlonly API \endhtmlonly Thread. The process of sending messages to the \htmlonly API \endhtmlonly go as followed:
 * 1. Requests are contructed through different datetypes like unsigned characters, ints, and QVectors.
 * 2. The requests are sent to the \htmlonly API \endhtmlonly thread via emitted QObject signals.
 * 3. After the first signal is sent, the associated unsigned char variable called a flag will be set to true (raised).
 * 4. While a flag is raised, the associated signal will continue to be emitted with the contructed request.
 * 5. The flag will be set to false (lowered) when the \htmlonly API \endhtmlonly thread emits their response signal and trigger the \htmlonly Backend \endhtmlonly QObject response slot.
 *
 * \subsubsection backendController_startup_requests Startup Requests
 *
 * The first 5 requests are only sent on startup, which would then trigger the home page to be displayed. The responses to these requests will save the values received from the \htmlonly API \endhtmlonly to the <b>State Manager</b>.
 *
 * The <b>Get Settings Request</b> retrieves all pneumatic settings from the \htmlonly API \endhtmlonly on startup if \htmlonly Humidity \endhtmlonly levels do not equal each other, Separate Humidities Mode will be set. The \htmlonly Humidity \endhtmlonly Percentages will be converted to the following levels:
 * - 100% to level 4
 * - 70% to level 3
 * - 50% to level 2
 * - 30% to level 1
 * - 0% to level 0
 *
 * The <b>Enable Notifications Request</b> enables the constant retrieval of notifications from the system on startup. Notification updates will be sent to the state manager and the warning manager.
 *
 * The <b>Get Op Modes Request</b> retrieves the state of all op modes enabled or disabled on the system on startup.
 *
 * The <b>Get Subsystem State Request</b> retrieves the state of all subsystems on the system on startup.
 *
 * The <b>Get System Version Request</b> retrieves the most recent version number of the system controller on startup. Also saves the most recent version of the display controller.
 *
 * \subsubsection backendController_requests Backend Requests
 *
 * The <b>Set Settings Request</b> updates the values for pneumatic settings requests updates to the system controller. One pneumatic setting can be changed, such as updating the rate from 30 BPM to 90 BPM. But for implementing a <b>Preset</b>, all pneumatic settings can be changed. When <b>Limited O<sub>2</sub> Oxygen Concentration</b> is less than the current oxygen concentration, oxygen concentration is updated. <b>\htmlonly Humidity\endhtmlonly</b> on the jet line and the auxiliary line is updated at once. All setting updates are logged to the <b>Log Manager</b>. When updating <b>\htmlonly Humidity\endhtmlonly</b>, levels will be converted to the following percentages:
 * - level 4 to 100%
 * - level 3 to 70%
 * - level 2 to 50%
 * - level 1 to 30%
 * - level 0 to 0%
 *
 * The <b>Get Measured Request</b> retrieves measurements running on the system, such as for detecting water on the system, O<sub>2</sub> Calibration Voltages, or low and high O<sub>2</sub> Calibration values, and saves the measurements to the <b>State Manager</b>.
 *
 * The <b>Clear \htmlonly Warning \endhtmlonly Request</b> clears warnings running on the system by ID. If the warning ID is 59, the display will clear the Service Due warning in the warning manager. If \htmlonly <b>PIP Disconnection Monitoring</b> \endhtmlonly is active, the \htmlonly PIP \endhtmlonly Disconnection warning is triggered and ventilation stops. Clearing the warning will restart ventilation. If the warning ID is either 4, 5, 6, or 7, (the <b> No Water Detected </b> warnings), the warning will be cleared, but the device will also attempt to pump water into the system if a water tube is connected. The warning that is cleared is logged to the <b> Log Manager </b>.
 *
 * The <b>Enable Op Mode Request</b> enables or disables an Op Mode available in <b>Operation Modes</b> to the <b>State Manager</b> and the system. All Op Mode activities are logged to the <b>Log Manager</b>. Based on which Op Mode is enabled or disabled, different activities in the \htmlonly Backend \endhtmlonly occur:
 * <table>
 *    <tr>
 *        <th>Op Mode</th>
 *        <th>Enabled</th>
 *        <th>Disabled</th>
 *    </tr>
 *     <tr>
 *         <td>Manual Mode</td>
 *         <td>
 *         - The SP Line is hidden on the QML graph.
 *         </td>
 *         <td>
 *         - The SP Line returns to its original state.
 *         </td>
 *     </tr>
 *     <tr>
 *         <td>Listening \htmlonly Knob \endhtmlonly Op Mode</td>
 *         <td>
 *         - Emits signal to knob controller to be enabled.
 *         </td>
 *         <td>
 *         - Emits signal to knob controller to be disabled.
 *         </td>
 *     </tr>
 *     <tr>
 *         <td>Limited O<sub>2</sub> Mode</td>
 *         <td>
 *         - If the Oxygen Concentration is greater than Limited O<sub>2</sub> Oxygen Concentration, Oxygen Concentration is updated to match it.
 *         - The states for mode reset in the state manager.
 *         </td>
 *         <td>
 *         - Oxygen Concentration is set back to its original value.
 *         - The states for mode reset in the state manager.
 *         </td>
 *     </tr>
 *     <tr>
 *         <td>O<sub>2</sub> Calibration Mode</td>
 *         <td>
 *         - Logs most recent calibration data to Log Manager.
 *         </td>
 *         <td>
 *         - Logs most recent calibration data to Log Manager.
 *         </td>
 *     </tr>
 *     <tr>
 *         <td>Service Calibration Mode</td>
 *         <td>
 *         - The warning banner will not be displayed (even if warnings are running).
 *         - The current Driving Pressure Pneumatic Setting will be saved.
 *         - Signal is emitted for the \htmlonly API \endhtmlonly service variable.
 *         - The Set DPR Cal Val Request is sent at its default state.
 *         - Updates the warning manager to stop raising the No Communication warning.
 *         </td>
 *         <td>
 *         - The saved Driving Pressured Pneumatic Setting will be set again.
 *         - The warning banner will be displayed.
 *         - Signal is emitted for the \htmlonly API \endhtmlonly service variable.
 *         - Updates the warning manager to raise the No Communication warning again when there is no communication between system and display.
 *         </td>
 *     </tr>
 *     <tr>
 *         <td>\htmlonly Humidity \endhtmlonly Priming Reset Available Mode</td>
 *         <td></td>
 *         <td>
 *         - The \htmlonly Humidity \endhtmlonly on the Jet Line and the Auxiliary Line is set to 0.
 *         </td>
 *     </tr>
 *     <tr>
 *         <td>Dehumidification Mode</td>
 *         <td></td>
 *         <td>Dehumidification Timer will stop.</td>
 *     </tr>
 * </table>

 * The following Op Modes Requested will not proceed if different criterias are met:
 * - If ventilation is inactive or Manual Mode is enabled, enabling <b>ETCO<sub>2</sub> Mode</b> is prevented.
 * - If ETCO<sub>2</sub> Mode is enabled, enabling <b>Manual Mode</b> is prevented.

 * The only Op Modes that will be enabled or disbaled together at the same time are <b>Screen Lock Mode</b> and <b>Screen Lock Touched Mode</b>.

 * The <b>Shutdown Confirm Send Request</b> sends a request to the system to confirm that the device can shutdown completely, and can cancel the shutdown procedure. Flags for shutting are also saved to the State Manager. Also, the shutdown request is logged to the Log Manager.

 * The <b>Set DPR Cal Val Request</b> requests to update the state of calibration for pressure regulators. All state changes are logged to the Log Manager. Depending on which state is active, different activities in the \htmlonly Backend \endhtmlonly will occur:

 * <table>
 * <tr>
 *     <th>Pressure Regulator State</th>
 *     <th>Activities</th>
 * </tr>
 * <tr>
 *     <td>Low DPR</td>
 *     <td>Requests constant measurements for DPR, and sets Driving Pressure to 0. Saves DPR value from system to DPR Calibration Manager.</td>
 * </tr>
 * <tr>
 *     <td>High DPR</td>
 *     <td>Requests constant measurements for DPR, and sets Driving pressure to 45. Sets precise float values for Driving Pressure during calibration and saves DPR value from system to DPR Calibration Manager.</td>
 * </tr>
 * <tr>
 *     <td>Air Regulator</td>
 *     <td>Sets Driving Pressure to 48. State change confirmation is logged to the Log Manager.</td>
 * </tr>
 * <tr>
 *     <td>O<sub>2</sub> Regulator</td>
 *     <td>Sets Driving Pressure to 48. State change confirmation is logged to the Log Manager.</td>
 * </tr>
 * <tr>
 *     <td>Default</td>
 *     <td></td>
 * </tr>
 * </table>
 *
 * The <b>Enable Pressure Sensor Zero Request</b> sends calibration verification for the following sensors: Inlet Air, Inlet O<sub>2</sub>, \htmlonly PIP\endhtmlonly, and SP. Saves value to Zero Calibration Manager for Sensor values. States of calibrations are logged to the Log Manager.
 *
 * \subsubsection backendController_functions Other Backend Functions
 *
 * The backend will continuously receive data from the system. Most importantly, the backend receives <b>Notifications</b> and <b>Service Notifications</b> from the \htmlonly API. \endhtmlonly
 *
 * The following are data is received from the Notifications and Service Notifications:
 * - The measurements for Stacking Pressure, Oxygen, Peak Inspiratory Pressure, Auxiliary Flow, TV, and MAP that are saved to the State Manager.
 * - The states for all 72 warnings are saved to the \htmlonly Warning \endhtmlonly Banner.
 * - The silence timer countdown time to the State Manager.
 * - The measurements for the average Stacking Pressure data, the instantaneous Stacking Pressure data, the average Peak Inspiratory Pressure data, the instantaneous Peak Inspiratory Pressure data, and the real-time O<sub>2</sub> Calibration voltage to the State Manager.
 *
 * The backend will also receive ventilation status updates, which will be utilized for the state manager, the End-Tidal Button, and the part manager; and ids for which the HMI button is pushed, and is especially useful for screen lock mode. Both inputs are saved to the State Manager and will be logged to the Log Manager.
 *
 * For Modes requested from the system, the states of the Modes will be logged to the Log Manager, and the following will occur:
 * - When the system enables or disables the O<sub>2</sub> Calibration Op Mode successfully, the measurement for the lowest and highest Calibration values and voltages are requested to the system, then saved to the State Manager and O<sub>2</sub> Calibration Manager. Calibration failures with no new measurements will be logged to the Log Manager.
 * - When the system enables dehumidification, the \htmlonly Humidity \endhtmlonly on the Jet Line and the Auxiliary Line is set to 0.
 *
 * For exporting service logs and other files to the USB, the backend detects the dev port for a USB drive, and finds and creates the directories to send files. Once finished, the backend will eject the dev port for the USB drive.
 *
 * For <b>Service Menu</b> service logs, the backend updates the log manager for when the service menu is opened, see Log Manager.
 *
 * For <b>Dehumidification</b>, the backend runs a 2 minute countdown timer for when the dehumidification progress page is up.
 *
 * For when the system begins the <b>Shutdown Procedure</b>, the backend requests measurements for Water Sensors to determine if water is detected on Jet and Auxiliary Lines. All values are saved to the State Manager.
 *
 * Lastly, the backend sends service calibration data as a QVector back to the system via signal to \htmlonly API \endhtmlonly.
 * @}
 */

/**
 * @ingroup backendModule
 * @defgroup stateManager State Manager
 * @brief Documentation for managing the states of settings, modes, and other parts of the NVENT-VITA.
 * @{
 * @details
 *
 * \subsection stateManager State Manager
 *
 * The State Manager stores and controls the following from the backend controller and the Graphical User Interface. States are stored in different data types, and are either constantly updating, or remain static.
 *
 * <table>
 *     <tr>
 *         <th>States</th>
 *         <th>Description</th>
 *     </tr>
 *     <tr>
 *         <td>Shutdown Flag</td>
 *         <td>State for when the shutdown procedure is active or inactive.</td>
 *     </tr>
 *     <tr>
 *         <td>Startup Flags</td>
 *         <td>State for when the startup procedure is still active or complete.</td>
 *     </tr>
 *     <tr>
 *         <td>Display Version</td>
 *         <td>Text representation for the most recent Display Version Number.</td>
 *     </tr>
 *     <tr>
 *         <td>System Version</td>
 *         <td>Text representation for the most recent System Version Number.</td>
 *     </tr>
 *     <tr>
 *         <td>Ventilating</td>
 *         <td>State for when system ventilation is active or inactive.</td>
 *     </tr>
 * <tr>
 * <td>
 * Op Modes
 * </td>
 * <td>
 * States stored that represent when mode is enabled or disabled. Op Modes include the following:
 * - Limited O<sub>2</sub> Mode
 * - Manual Mode
 * - \htmlonly PIP \endhtmlonly Monitoring Mode
 * - Demo Mode
 * - Screen Lock Mode
 * - Double Jets Mode
 * - End-Tidal Procedure
 * - Dehumidification Procedure
 * - O<sub>2</sub> Calibration Procedure
 * - Alarm Sounding Mode
 * - \htmlonly Humidity \endhtmlonly Priming Reset Available
 * - Listening to \htmlonly Knob \endhtmlonly Mode
 * - Sound Icon Mode (obsolete)
 * - Service Calibration Mode
 * </td>
 * </tr>
 * <tr>
 * <td>
 * \htmlonly Humidity \endhtmlonly Separation
 * </td>
 * <td>
 * The state for when adjustments for humidity on the Jet Line are Auxiliary Line are separate.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Op Mode Successes
 * </td>
 * <td>
 * The states for when the following Op Mode Procedures succeed or fail:
 * Dehumidification
 * O2 Calibration
 * End-Tidal Mode
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Subsystems
 * </td>
 * <td>
 * The states for when each subsystem is active or not:
 * - Primary Ventilation
 * - Secondary Ventilation
 * - Auxiliary Flow
 * - Oxygen Control
 * - Primary Humidification
 * - Secondary Humidification
 * - Auxiliary Humidification
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Pneumatic Settings
 * </td>
 * <td>
 * The states that represent the values set by the user. Settings include the following:
 * - Driving Pressure
 * - \htmlonly Rate \endhtmlonly
 * - Inspiratory Time
 * - Stacking Pressure
 * - Oxygen Concentration
 * - Peak Inspiratory Pressure
 * - Auxiliary Flow
 * - \htmlonly Humidity \endhtmlonly on the Jet Line
 * - \htmlonly Humidity \endhtmlonly on the Auxiliary Line
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Double Jet Pneumatic Settings
 * </td>
 * <td>
 * If a double jet is installed on the device, then the following additional pneumatic settings will be set by the user:
 * - Driving Pressure
 * - \htmlonly Rate \endhtmlonly
 * - Inspiratory Time
 * - Stacking Pressure
 * - \htmlonly Humidity \endhtmlonly on the Second Jet Line
 * </td>
 * </tr>
 * <tr>
 * <td>
 * End-Tidal Settings
 * </td>
 * <td>
 * The states that represent the pneumatic settings set by the user for when End-Tidal Mode is active. Settings include the following:
 * - ETCO<sub>2</sub> \htmlonly Rate \endhtmlonly
 * - ETCO<sub>2</sub> Inspiratory Time
 * - ETCO<sub>2</sub> Number of Breaths
 * - ETCO<sub>2</sub> Driving Pressure
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Limited O<sub>2</sub> Oxygen Concentration
 * </td>
 * <td>
 * The state set by the user for Oxygen Concentration during Limited O<sub>2</sub> Mode.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * \htmlonly Volume \endhtmlonly
 * </td>
 * <td>
 * State set by the user for the volume of the Display Controller Alarm Sound.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Oxygen Saved State - Limited O<sub>2</sub>
 * </td>
 * <td>
 * The state for the originally set Oxygen Concentration while Limited O<sub>2</sub> Mode is active.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * States of Limited O<sub>2</sub>
 * </td>
 * <td>
 * The states of Limited O<sub>2</sub> for when the oxygen measurement on the notification vector reaches the minimum oxygen and set oxygen.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Pressure Regulator Calibration
 * </td>
 * <td>
 * The state for when a calibration procedure is active for any of the Pressure Regulators.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Sensor Calibration Values
 * </td>
 * <td>
 * States of the following Sensor Calibration values:
 * - Inlet Air
 * - Inlet O<sub>2</sub>
 * - Peak Inspiratory Pressure
 * - Stacking Pressure
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Driving Pressure Save State - Pressure Regulator Calibration
 * </td>
 * <td>
 * The state for the originally set Driving Pressure while Pressure Regulator Calibration is active.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Notifications
 * </td>
 * <td>
 * Measurements for the following values sent from the System:
 * - Stacking Pressure
 * - Stacking Pressure on second Jet Line
 * - Oxygen Concentration
 * - Peak Inspiratory Pressure
 * - Auxiliary Flow
 * - Tidal \htmlonly Volume \endhtmlonly
 * - Tidal \htmlonly Volume \endhtmlonly on second Jet Line
 * - Map
 * - Alarm Time
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Oxygen Adjustment
 * </td>
 * <td>
 * The state for when to display the spinner icon when oxygen is adjusting.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Measurements
 * </td>
 * <td>
 * The states of the most recent measurements on the system:
 * - Driving Pressure
 * - Driving Pressure on Second Line
 * - \htmlonly Rate \endhtmlonly
 * - \htmlonly Rate \endhtmlonly on Second Line
 * - Inspiratory Time
 * - Inspiratory Time on Second Line
 * - Stacking Pressure
 * - Stacking Pressure on Second Line
 * - Oxygen Concentration
 * - Peak Inspiratory Pressure
 * - Auxiliary Flow
 * - \htmlonly Humidity \endhtmlonly on the Jet Line
 * - \htmlonly Humidity \endhtmlonly on the Second Line
 * - \htmlonly Humidity \endhtmlonly on the Auxiliary Line
 * - The Heater Temperature
 * - The Average Flow
 * - The Average Flow on the Second Line
 * - Water Sensor on the Jet Line
 * - Water Sensor on the Second Line
 * - Water Sensor on the Auxiliary Line
 * - Tidal \htmlonly Volume \endhtmlonly
 * - Tidal \htmlonly Volume \endhtmlonly on the Second Line
 * - Map
 * - Inlet Air Pressure
 * - Inlet O<sub>2</sub> Pressure
 * - \htmlonly PIP \endhtmlonly Zeroing Value
 * - Stacking Pressure Zeroing Value
 * - Stacking Pressure Zeroing Value on the Second Line
 * - Inlet Air Zeroing Value
 * - Inlet O<sub>2</sub> Zeroing Value
 * - Lowest Bounded O<sub>2</sub> Calibration Value
 * - Highest Bounded O<sub>2</sub> Calibration Value
 * - Lowest O<sub>2</sub> Calibration Voltage
 * - Highest O<sub>2</sub> Calibration Voltage
 * - Realtime O<sub>2</sub> Calibration Voltage
 * - Realtime Driving Pressure Regulator
 * - Stacking Pressure Average Data
 * - Stacking Pressure Instantaneous Data
 * - Peak Inspiratory Pressure Average Data
 * - Peak Inspiratory Pressure Instantaneous Data
 * </td>
 * </tr>
 * <tr>
 * <td>
 * IP Address
 * </td>
 * <td>
 * Text representation for the Display Controller IP Address (retrieves and sets IP Address from local network).
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Preset Implementation Progress
 * </td>
 * <td>
 * The state for when preset implementation is active or inactive, which is when the pneumatic settings stored on a preset are being sent to the system controller.
 *
 * <b>Note:</b> State exists due to the time it takes to implement preset and multiple pneumatic settings at once.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * \htmlonly Warning \endhtmlonly Banner Displayed
 * </td>
 * <td>
 * The state for when the warning banner on the GUI is visible or not.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Preset Creation
 * </td>
 * <td>
 * The state for when the user is creating or editing a preset.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Stacking Pressure Line
 * </td>
 * <td>
 * The state visibility for Stacking Pressure line on the home page graph.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * End-Tidal Button
 * </td>
 * <td>
 * The state for when the End-Tidal Button on the home page is enabled or disabled.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Service Log Count
 * </td>
 * <td>
 * State for the total number of service logs stored on the display controller.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Service Logs Exported
 * </td>
 * <td>
 * State for the number of service logs that are exported to the connected USB drive.
 * </td>
 * </tr>
 * <tr>
 * <td>
 * Service Notifications
 * </td>
 * <td>
 * Measurements for the following values sent from the System while the Service Menu is opened:
 * - Stacking Pressure Average Data
 * - Stacking Pressure Instantaneous Data
 * - Peak Inspiratory Pressure Average Data
 * - Peak Inspiratory Pressure Instantaneous Data
 * - O<sub>2</sub> Calibration Voltage Data

 * <b>Note:</b> More measurements will be added later on.
 * </td>
 * </tr>
 * </table>
 * @}
 */

/**
 * @ingroup backendModule
 * @defgroup warningsModule Warnings and the Warnings Manager
 * @brief Documentation for warnings and management of warnings.
 * @details
 *
 * \subsection warningsModule Warnings and Warning Manager
 *
 * There are a total of <b>72</b> warnings that can occur while running the NVENT-VITA. While the system determines which warnings need to be displayed and the alarms that need to be played, the display manages the data and procedures needed to handle and dismiss those warnings. Each warning consist of the following:
 * - A \htmlonly Warning \endhtmlonly ID
 * - The Title for the \htmlonly Warning \endhtmlonly
 * - The Class Type order of Priority
 * - The Troubleshooting Steps to end the issue coming from the \htmlonly Warning \endhtmlonly
 * - The clearing behavior
 * - The color of the warning
 * - The text for the clear button.
 *
 * \subsubsection warningsModule_classes Warning Classes
 *
 * There 3 types of warnings that will be triggered on the NVENT-Vita:
 * - <b>Patient Warnings:</b> Warnings that have the highest priority due to being directly related to a patient’s safety and health. Patient Warnings will be displayed in red. Patient Warnings will also have an audible component.
 * - <b>System Warnings:</b> Warnings that have second priority due to relating to issues with the system, but not directly with the patient. System Warnings will be displayed in blue. System Warnings will also have an audible component.
 * - <b>Notices:</b> Warnings that have the lowest priority due to being only small reminders for procedures and small system changes. Notices will be displayed in yellow.
 *
 * \subsubsection warningsModule_clear_behavior Warning Clear Behavior
 *
 * There are 3 types of Clear Behaviors for each warning:
 * - <b>Clear Autonomously:</b> Warnings that are cleared on schedule.
 *   For example, the O<sub>2</sub> Calibration In Progress will be cleared after the O<sub>2</sub> calibration Procedure is complete.
 * - <b>Clear On Demand:</b> Warnings that are cleared from the \htmlonly Warning \endhtmlonly Banner’s Clear Button.
 * - <b>Clear After Resolved:</b> Warnings that are cleared after the issue related to the warning is fixed.
 *   For example, the Stacking Pressure High \htmlonly Warning \endhtmlonly is cleared after the Stacking Pressure returns to an appropriate measured value.
 *
 * \subsubsection warningsModule_warnings List of Warnings
 *
 * The following tables contain all warnings available on the device.
 *
 * #### Patient Warnings
 *
 * <table>
 *  <tr>
 *      <th style="background-color: #202531; border-color: #202531">Warnings</th>
 *      <th style="background-color: #202531; border-color: #202531">Description</th>
 *      <th style="background-color: #202531; border-color: #202531">ID</th>
 *      <th style="background-color: #202531; border-color: #202531">Clear Behavior</th>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">\htmlonly PIP \endhtmlonly High!</th>
 *      <td>Triggered when the measured value for Peak Inspiratory Pressure is too high for the patient.</td>
 *      <td>0</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">Stacking Pressure High!</th>
 *      <td>Triggered when the measured value for Stacking Pressure is too high for the patient.</td>
 *      <td>1<br>2</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">\htmlonly PIP \endhtmlonly Disconnected!</th>
 *      <td>Triggered if \htmlonly PIP \endhtmlonly Disconnection Mode is enabled, and the \htmlonly PIP \endhtmlonly Tube is not connected to the patient.</td>
 *      <td>3</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Jet Line!</th>
 *      <td>Triggered when the system is ventilating, humidity on the jet line is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.</td>
 *      <td>4<br>5</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Auxiliary Line!</th>
 *      <td>Triggered when the system is ventilating, humidity on the auxiliary line is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.</td>
 *      <td>6</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Jet and Auxiliary Lines!</th>
 *      <td>Triggered when the system is ventilating, humidity on the jet and auxiliary lines is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.</td>
 *      <td>7</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  </table>
 *
 *  #### System Warnings
 *
 *  <table>
 *  <tr>
 *      <th style="background-color: #202531; border-color: #202531">Warnings</th>
 *      <th style="background-color: #202531; border-color: #202531">Description</th>
 *      <th style="background-color: #202531; border-color: #202531">ID</th>
 *      <th style="background-color: #202531; border-color: #202531">Clear Behavior</th>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet \htmlonly Switch \endhtmlonly Error!</th>
 *      <td>Triggered if the Jet \htmlonly Switch \endhtmlonly is defective.</td>
 *      <td>8<br>9</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Stacking Pressure Sensor Defective!</th>
 *      <td>Triggered if the sensor if the Stacking Pressure Measurement reading is inaccurate to what they should be.</td>
 *      <td>10<br>11</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Stacking Pressure Internally Disconnected!</th>
 *      <td>Triggered if the SP tube is not connected to the patient nor the device while ventilating.</td>
 *      <td>12<br>13</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Inappropriate Oxygen Sensor Detected</th>
 *      <td>Triggered if the oxygen cannot be detected.</td>
 *      <td>14</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Air Supply Pressure!</th>
 *      <td>Triggered if the measured inlet air pressure is too low.</td>
 *      <td>15</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Air Supply Pressure, Limited O<sub>2</sub> Adjustment In Progress!</th>
 *      <td>Triggered if the measured inlet air pressure is too low while oxygen concentration is too high, which is dangerous if the laser is active.</td>
 *      <td>16</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Oxygen Supply Pressure!</th>
 *      <td>Triggered if inlet O<sub>2</sub> Pressure is too low.</td>
 *      <td>17</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Proportional Valve Error!</th>
 *      <td>Trigger if the Air Proportional Valve is damaged.</td>
 *      <td>18</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Proportional Valve Error, Limited O<sub>2</sub> Adjustment in Progress!</th>
 *      <td>Trigger if the Air Proportional Valve is damaged and is recommended not to use laser while laser is active.</td>
 *      <td>19</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Proportional Valve Error!</th>
 *      <td>Triggers if Oxygen Proportional Valve is damaged.</td>
 *      <td>20</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Inlet Pressure Sensor Error!</th>
 *      <td>Triggered if the Air Inlet Pressure Sensor is damaged.</td>
 *      <td>21</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Inlet Pressure Sensor Error, Limited O<sub>2</sub> Adjustment in Progress!</th>
 *      <td>Triggered if the Air Inlet Pressure Sensor is damaged while the laser is active.</td>
 *      <td>22</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Inlet Pressure Sensor Error!</th>
 *      <td>Triggered if oxygen inlet pressure sensor is damaged.</td>
 *      <td>23</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Proportional Valve Error!</th>
 *      <td>Triggered if Auxiliary Proportional Valve Error is damaged.</td>
 *      <td>24</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Flow Sensor Error!</th>
 *      <td>Triggered if the Auxiliary Flow Sensor is damaged.</td>
 *      <td>25</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Speaker Defect!</th>
 *      <td>Triggered if the Speaker for the alarm is damaged.</td>
 *      <td>26</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Heater Failure!</th>
 *      <td>Triggered if the Heater is damaged.</td>
 *      <td>27</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Internal Temperature Measuring Defect!</th>
 *      <td></td>
 *      <td>28</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Flow Sensor!</th>
 *      <td></td>
 *      <td>29<br>30</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet \htmlonly Humidity \endhtmlonly Sensor Error!</th>
 *      <td></td>
 *      <td>31<br>32</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary \htmlonly Humidity \endhtmlonly Sensor Error!</th>
 *      <td></td>
 *      <td>33</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Real Time Clock Error!</th>
 *      <td></td>
 *      <td>34</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Exhaust Fan Error</th>
 *      <td></td>
 *      <td>35</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Driving Pressure Regulator Error!</th>
 *      <td></td>
 *      <td>36<br>37</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">\htmlonly PIP \endhtmlonly Sensor Error!</th>
 *      <td></td>
 *      <td>38</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">FiO<sub>2</sub> Failure!</th>
 *      <td></td>
 *      <td>39</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Display and System Disconnected!</th>
 *      <td></td>
 *      <td>40</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Calibration Failure!</th>
 *      <td></td>
 *      <td>41</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Water Pump Defect</th>
 *      <td></td>
 *      <td>42</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Water Pump Defect</th>
 *      <td></td>
 *      <td>43<br>44</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Failed to Restore Memory</th>
 *      <td></td>
 *      <td>45</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Dehumidification Failed</th>
 *      <td></td>
 *      <td>46</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Breath Timing Failure!</th>
 *      <td></td>
 *      <td>47</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Water Sensor Failure!</th>
 *      <td></td>
 *      <td>48</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Water Sensor Failure!</th>
 *      <td></td>
 *      <td>49</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Ambient Temperature Sensor Defect!</th>
 *      <td></td>
 *      <td>50</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Internal System Temperature High</th>
 *      <td></td>
 *      <td>51</td>
 *      <td>Clear After Resolved</td>
 *  </tr>
 *  </table>
 *
 *  #### Notices
 *
 *  <table>
 *  <tr>
 *      <th style="background-color: #202531; border-color: #202531">Warnings</th>
 *      <th style="background-color: #202531; border-color: #202531">Description</th>
 *      <th style="background-color: #202531; border-color: #202531">ID</th>
 *      <th style="background-color: #202531; border-color: #202531">Clear Behavior</th>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #6FCC68; border-color: #202531">Limited O<sub>2</sub> Safe</th>
 *      <td>Triggered when Limited O<sub>2</sub> is enabled and the oxygen measurement is within the Limited O<sub>2</sub> Oxygen Concentration Range.</td>
 *      <td>52</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Limited O<sub>2</sub> Prepping</th>
 *      <td>Triggered when Limited O<sub>2</sub> is enabled and the oxygen measurement is outside of the Limited O<sub>2</sub> Oxygen Concentration Range.</td>
 *      <td>53</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Low Static O<sub>2</sub> Pressure</th>
 *      <td></td>
 *      <td>54</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Low Static Air Pressure</th>
 *      <td></td>
 *      <td>55</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Manual Mode Active, \htmlonly PIP \endhtmlonly Monitoring Recommended</th>
 *      <td></td>
 *      <td>56</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">\htmlonly PIP \endhtmlonly Monitoring Recommended</th>
 *      <td></td>
 *      <td>57</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">End Tidal CO<sub>2</sub> Routine Active</th>
 *      <td></td>
 *      <td>58</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Service Due</th>
 *      <td></td>
 *      <td>59</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Battery Replacement Due</th>
 *      <td></td>
 *      <td>60</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Heater and Humidifier Off</th>
 *      <td></td>
 *      <td>61</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification System Deactivated</th>
 *      <td></td>
 *      <td>62</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification Deactivated on Jet Line</th>
 *      <td></td>
 *      <td>63<br>64</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification Deactivated on Auxiliary Line</th>
 *      <td></td>
 *      <td>65</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Auxiliary Flow Deactivated</th>
 *      <td></td>
 *      <td>66</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Only Use Distilled Water For Humidification</th>
 *      <td></td>
 *      <td>67</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Pump System Priming</th>
 *      <td></td>
 *      <td>68</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Ventilating without Humidifying for 30+ minutes. Consider adding humidity.</th>
 *      <td></td>
 *      <td>69</td>
 *      <td>Clear On Demand</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Oxygen Calibration in Progress, Limited O<sub>2</sub> Adjustment in Progress</th>
 *      <td></td>
 *      <td>70</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Oxygen Calibration in Progress</th>
 *      <td></td>
 *      <td>71</td>
 *      <td>Clear Autonomously</td>
 *  </tr>
 * </table>
 *
 * Additionally, for warnings <b>No Water Detected in Jet Line, No Water Detected in Auxiliary Line, </b> and <b>No Water Detected in Jet and Auxiliary Line,</b> the clear button is replaced with a prime buttonas an indication that the warnings will be cleared, but water will also be pumped into the system.
 *
 * The warning <b>Limited O<sub>2</sub> Safe</b> is colored Green to indicate Laser is active but oxygen is within safe range. Plus, depending on the different success values for the Op Mode in the State Manager, alternative titles include Limited O<sub>2</sub> Prepping to 21%, Limited O<sub>2</sub> Prepping at 21%, and Limited O<sub>2</sub> Prepping to (Set Value).
 *
 * The only notice raised exclusively from the display controller is <b>Service Due.</b> For information on the warnings troubleshooting steps, see @ref helpPagesModule "Help Pages."
 *
 * For when <b> Oxygen Calibration in Progress</b> and <b>Oxygen Calibration in Progress, Limited O<sub>2</sub> Adjustment in Progress</b> is active or inactive, a signal is sent to the O<sub>2</sub> Calibration Manager to start or stop the 1 minute timer on the Warning Banner.
 *
 * \subsubsection warningsModule_manager Warning Manager
 *
 * The warning manager tracks and clears the state of the following warnings on the system:
 * - All active warnings and notices that are displayed throughout the warning banner.
 * - All inactive warnings that are not displayed yet.
 * - All warnings that will be automatically cleared.
 *
 * The warning manager receives most warnings from the notifications via backend controller and will only raise the <b>No Communication \htmlonly Warning \endhtmlonly</b> itself if the system fails to send notifications for at least 3 seconds. Timer is created to track disconnection timer. The No Communication warning is prevented from being triggered when the Service Menu is opened due to notifications pausing.
 *
 * Most recent pneumatic settings are saved for warnings raised at the time, and will be utilized for logging purposes. All active and inactive warnings with settings are saved to the Log Manager.
 *
 * The number of active warnings, titles, ids, descriptions, class type, color, troubleshooting steps, and clearing behaviors are returned to the warning banner.
 *
 * For when Limited O2 Mode is active, the warning manager sends the states representing colors to QML components (the Pneumatic Button and the Limited O2 Switch) that are active alongside the Limited O2 Warnings:
 * - State 0: Limted O<sub>2</sub> Safe is green.
 * - State 1: Limted O<sub>2</sub> Prepping or O<sub>2</sub> Calibration warnings are yellow.
 * - State 2: Neither
 *
 * Updates the state of the Service Due \htmlonly Notice \endhtmlonly due it being the only warning solely raised by the display controller due to maintenance date data stored in the display controller.
 */

/**
 * @ingroup backendModule
 * @defgroup modelsModule Models
 * @brief Documentation for models utilized as contants.
 * @details
 *
 * \subsection modelsModule Models
 *
 * Constants and Models will be utilized throughout the backend as identifiers to distinguish between modes, pneumatic settings, and other settings.
 *
 * \subsubsection modelsModule_modes Op Mode IDs
 *
 * <table>
 *  <tr>
 *      <th>Mode</th>
 *      <th>ID</th>
 *  </tr>
 *  <tr>
 *      <td>Limited O<sub>2</sub></td>
 *      <td>0</td>
 *  </tr>
 *  <tr>
 *      <td>Double Jets</td>
 *      <td>1</td>
 *  </tr>
 *  <tr>
 *      <td>Manual</td>
 *      <td>2</td>
 *  </tr>
 *  <tr>
 *      <td>Screen Lock</td>
 *      <td>3</td>
 *  </tr>
 *  <tr>
 *      <td>Demo</td>
 *      <td>4</td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly PIP \endhtmlonly Disconnected Monitoring</td>
 *      <td>5</td>
 *  </tr>
 *  <tr>
 *      <td>End-Tidal (ETCO<sub>2</sub> Procedure</td>
 *      <td>6</td>
 *  </tr>
 *  <tr>
 *      <td>Dehumidification</td>
 *      <td>7</td>
 *  </tr>
 *  <tr>
 *      <td>O<sub>2</sub> Calibration</td>
 *      <td>8</td>
 *  </tr>
 *  <tr>
 *      <td>Alarm Sounding</td>
 *      <td>9</td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly Humidity \endhtmlonly Priming Reset Available</td>
 *      <td>10</td>
 *  </tr>
 *  <tr>
 *      <td>Listening To \htmlonly Knob \endhtmlonly</td>
 *      <td>11</td>
 *  </tr>
 *  <tr>
 *      <td>Sound Icon (Obsolute)</td>
 *      <td>12</td>
 *  </tr>
 *  <tr>
 *      <td>Service Calibration</td>
 *      <td>13</td>
 *  </tr>
 *  <tr>
 *      <td>Screen Lock Touched</td>
 *      <td>14</td>
 *  </tr>
 * </table>
 *
 * \subsubsection modelsModule_hmi HMI Input IDs
 *
 * The display tracks which button is pushed from the Display Controller's Human Machine Interface:
 *
 * <table>
 *  <tr>
 *      <th>HMI</th>
 *      <th>ID</th>
 *  </tr>
 *  <tr>
 *      <td>Power Button</td>
 *      <td>0</td>
 *  </tr>
 *  <tr>
 *      <td>Start/Stop Button</td>
 *      <td>1</td>
 *  </tr>
 *  <tr>
 *      <td>Silence Button</td>
 *      <td>2</td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly Encoder \endhtmlonly Dial Pushed Down</td>
 *      <td>3</td>
 *  </tr>
 * </table>
 *
 * \subsubsection modelsModule_settings Pneumatic Settings Models
 *
 * The Pneumatic Settings Models contain values used to distinguish between each Pneumatic Setting, and what limitations are required for adjustment. A model consists of the following:
 * - Setting ID
 * - The Minimum: the lowest value the user is allowed to adjust to.
 * - The Maximum: the highest value the user is allowed to adjust to.
 * - The Increment: The value that will increment or decrement the pneumatic setting value when turning the encoder knob.
 * - Minimum On Specific Value: Utilized to prevent a value to be set within a range.
 * - \htmlonly Warning \endhtmlonly Threshold: If a pneumatic setting is set greater than or equal to a warning threshold, then a warning will be sent to the GUI.
 *
 * <table>
 *  <tr>
 *      <th>Pneumatic Settings</th>
 *      <th>ID</th>
 *      <th>Unit</th>
 *      <th>Minimum</th>
 *      <th>Maximum</th>
 *      <th>Increment</th>
 *      <th>Minimum On</th>
 *      <th>\htmlonly Warning \endhtmlonly Threshold</th>
 *  </tr>
 *  <tr>
 *      <th>Driving Pressure 1</th>
 *      <td>0</td>
 *      <td>PSI</td>
 *      <td>5</td>
 *      <td>50</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>51</td>
 *  </tr>
 *  <tr>
 *      <th>Driving Pressure 2</th>
 *      <td>1</td>
 *      <td>PSI</td>
 *      <td>5</td>
 *      <td>50</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>51</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Rate \endhtmlonly 1</th>
 *      <td>2</td>
 *      <td>BPM</td>
 *      <td>5</td>
 *      <td>150</td>
 *      <td>5</td>
 *      <td>5</td>
 *      <td>151</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Rate \endhtmlonly 2</th>
 *      <td>3</td>
 *      <td>BPM</td>
 *      <td>5</td>
 *      <td>150</td>
 *      <td>5</td>
 *      <td>5</td>
 *      <td>151</td>
 *  </tr>
 *  <tr>
 *      <th>Inspiratory Time 1</th>
 *      <td>4</td>
 *      <td>%</td>
 *      <td>20</td>
 *      <td>70</td>
 *      <td>5</td>
 *      <td>20</td>
 *      <td>60</td>
 *  </tr>
 *  <tr>
 *      <th>Inspiratory Time 2</th>
 *      <td>5</td>
 *      <td>%</td>
 *      <td>20</td>
 *      <td>70</td>
 *      <td>5</td>
 *      <td>20</td>
 *      <td>60</td>
 *  </tr>
 *  <tr>
 *      <th>Stacking Pressure 1</th>
 *      <td>6</td>
 *      <td>cmH<sub>2</sub>O</td>
 *      <td>1</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>Stacking Pressure 2</th>
 *      <td>7</td>
 *      <td>cmH<sub>2</sub>O</td>
 *      <td>1</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>Oxygen</th>
 *      <td>8</td>
 *      <td>%</td>
 *      <td>21</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>21</td>
 *      <td>101</td>
 *  </tr>
 *  <tr>
 *      <th>Peak Inspiratory Pressure</th>
 *      <td>9</td>
 *      <td>cmH<sub>2</sub>O</td>
 *      <td>1</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>Auxiliary Flow</th>
 *      <td>10</td>
 *      <td>lpm</td>
 *      <td>0</td>
 *      <td>65</td>
 *      <td>1</td>
 *      <td>3</td>
 *      <td>66</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Humidity \endhtmlonly 1</th>
 *      <td>11</td>
 *      <td>level</td>
 *      <td>0</td>
 *      <td>4</td>
 *      <td>1</td>
 *      <td>0</td>
 *      <td>5</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Humidity \endhtmlonly 2</th>
 *      <td>12</td>
 *      <td>level</td>
 *      <td>0</td>
 *      <td>4</td>
 *      <td>1</td>
 *      <td>0</td>
 *      <td>5</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Humidity \endhtmlonly Auxiliary</th>
 *      <td>13</td>
 *      <td>level</td>
 *      <td>0</td>
 *      <td>4</td>
 *      <td>1</td>
 *      <td>0</td>
 *      <td>5</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal \htmlonly Rate \endhtmlonly</th>
 *      <td>14</td>
 *      <td>BPM</td>
 *      <td>5</td>
 *      <td>30</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>31</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal Inspiratory time</th>
 *      <td>15</td>
 *      <td>%</td>
 *      <td>20</td>
 *      <td>70</td>
 *      <td>5</td>
 *      <td>20</td>
 *      <td>71</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal Number of Breaths</th>
 *      <td>16</td>
 *      <td>Breaths</td>
 *      <td>1</td>
 *      <td>10</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>11</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal Driving Pressure</th>
 *      <td>17</td>
 *      <td>PSI</td>
 *      <td>5</td>
 *      <td>50</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>51</td>
 *  </tr>
 *  <tr>
 *      <th>Limited O<sub>2</sub></th>
 *      <td>18</td>
 *      <td>%</td>
 *      <td>21</td>
 *      <td>40</td>
 *      <td>1</td>
 *      <td>21</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Volume \endhtmlonly</th>
 *      <td>19</td>
 *      <td>%</td>
 *      <td>20</td>
 *      <td>100</td>
 *      <td>10</td>
 *      <td>20</td>
 *      <td>101</td>
 *  </tr>
 * </table>
 *
 * ### Notifications
 *
 * When the NVENT-VITA is running, there will be a constant flow of the following measured values on the home page:
 *
 * <table>
 *  <tr>
 *      <th>Notification</th>
 *      <th>ID (Notification Indxe)</th>
 *  </tr>
 *  <tr>
 *      <td>Stacking Pressure</th>
 *      <td>0</td>
 *  </tr>
 *  <tr>
 *      <td>Stacking Pressure (only available on the second jet line)</td>
 *      <td>1</td>
 *  </tr>
 *  <tr>
 *      <td>Oxygen Concentration</td>
 *      <td>2</td>
 *  </tr>
 *  <tr>
 *      <td>Peak Inspiratory Pressure</td>
 *      <td>3</td>
 *  </tr>
 *  <tr>
 *      <td>Auxiliary Flow</td>
 *      <td>4</td>
 *  </tr>
 *  <tr>
 *      <td>Tidal \htmlonly Volume \endhtmlonly</td>
 *      <td>5</td>
 *  </tr>
 *  <tr>
 *      <td>Tidal \htmlonly Volume \endhtmlonly (only available on the second jet line)</td>
 *      <td>6</td>
 *  </tr>
 *  <tr>
 *      <td>Mean Airway Pressure</td>
 *      <td>7</td>
 *  </tr>
 *  <tr>
 *      <td>Silence Time (only displayed on the warning banner's silence button)</td>
 *      <td>8</td>
 *  </tr>
 * </table>
 *
 * ### Service Notifications
 *
 * When the NVENT-VITA is running and the service menu is accessed, there will be a constant flow of the following measured values on the home page (Notifications is paused while active):
 *
 * <table>
 *  <tr>
 *      <th>Service Notification</th>
 *      <th>ID (notification Index)</th>
 *  </tr>
 *  <tr>
 *      <td>Stacking Pressure Average Data</td>
 *      <td>0</td>
 *  </tr>
 *  <tr>
 *      <td>Stacking Pressure Instantaneous Data</td>
 *      <td>1</td>
 *  </tr>
 *  <tr>
 *      <td>Peak Inspiratory Pressure Average Data</td>
 *      <td>2</td>
 *  </tr>
 *  <tr>
 *      <td>Peak Inspiratory Pressure Instantaneous Data</td>
 *      <td>3</td>
 *  </tr>
 *  <tr>
 *      <td>O<sub>2</sub> Calibration Voltage (only displayed through the Service Menu O<sub>2</sub> Calibration Page.</td>
 *      <td>4</td>
 *  </tr>
 * </table>
 */

/**
 * @ingroup backendModule
 * @defgroup loggerModule Log Manager and other Managers
 * @brief Documentation for how the display controller stores data internally through multiple directories.
 * @details
 *
 * ## CSV Manager
 *
 * The CSV Manager is the most important component to all data managers on the display controller, for it acts as a tool to read and write the rows and columns of CSV files (Comma-Separated Value). The CSV Manager can also update rows of CSV files, delete rows, and return the number of entries representing each row.
 *
 * ## Log Manager
 *
 * The Log Manager is tasked with writing all the service logs and warning logs on the system. Events on the service logs include settings requests, mode switches, warnings triggered, and other events. For whenever the NVENT-VITA display software starts up, two CSV files are created and stored onto the display controller's internal directory. One for writing all activities on the display, while another is specifically for when warnings are triggered. Each CSV filename will have the date and time of its creation. An incremented number will be added at the end of the filename for duplicates. Each service log entries will consists of the following:
 * - <b>TIMESTAMP:</b> The date and time for when the event occurred.
 * - <b>TYPE:</b> Which type and location for what activity is occuring. The label "(SERVICE)" will be written for activities involving the Service Menu.
 * - <b>EVENT:</b> A description for what is occurring on the device.
 *
 * The writing of all service log entries are triggered from qInfo statements in the backend source code. For the other managers, if CSV corruption occurs, the occurrence is logged to the Log Manager and a new CSV file is created. <b>IMPORTANT: Service log files are deleted after 2 weeks and warning logs are deleted after 3 months.</b>
 *
 * ## Brightness Manager
 *
 * Connects with the display controller's internal systems to update the brightness of the display controller screen. Brightness is adjusted via the knob controller.
 *
 * ## Contact Manager
 *
 * Updates and saves contact information for the servicing company (Susquehanna Micro) and the Sales Company (Lantern Medical) on to two CSV Files. Contact Information include the following:
 * - The Company Name
 * - Street Address
 * - City
 * - State
 * - Postal Code
 * - Email
 * - Phone Number
 *
 * ## DPR Manager
 *
 * Logs the dates and times of the lowest and highest Driving Pressure Regulator Calibration values (technically the same measurement types) onto a CSV file. The manager will store up to 5 entries and will delete the oldest entry when adding a new one. Updates the Log Manager for when new entries are added, and if entries are deleted.
 *
 * ## Maintenance Manager
 *
 * Updates and saves dates for the last service appointment and the next service appointment onto a CSV file. Updates the Log Manager for when dates are updated.
 *
 * ## O2 Calibration Manager
 *
 * Logs the dates and times of the lowest and highest O<sub>2</sub> Calibration Values and Voltages onto a CSV file. The manager will save up to 5 entries and will delete the oldest entry when adding a new one. Updates Log Manager for when entries are added or deleted. The manager is also tasked with running the timer for the Warning Banner's O<sub>2</sub> Calibration 1 minute progress time and is triggered when related warnings are active..
 *
 * ## Part Manager
 *
 * Manages and updates the data for all 23 parts that can be replaced on the device. The parts included:
 * - Oxygen Sensor
 * - 25 Micron Filter (Air Inlet Filter)
 * - 25 Micron Filter (Oxygen Inlet Filter)
 * - Water Injector (Jet Line)
 * - Water Injector (Auxiliary Line)
 * - \htmlonly Humidity \endhtmlonly Sensor (Jet Line)
 * - \htmlonly Humidity \endhtmlonly Sensor (Auxiliary Line)
 * - \htmlonly Humidity \endhtmlonly Sensor (PCB)
 * - Jet Line Water Pump
 * - Auxiliary Line Water Pump
 * - Internal Tubing Sets
 * - Water Tubing Sets
 * - Mechanical Pressure Regulator (Air)
 * - Mechanical Pressure Regulator (O<sub>2</sub>)
 * - Proportional Valve (Air)
 * - Proportional Valve (O<sub>2</sub>)
 * - Proportional Valve (Auxiliary)
 * - Flow Sensor (Jet Line)
 * - Flow Sensor (Auxiliary Line)
 * - Calibration Valve
 * - Driving Pressure Regulator
 * - Heater Cartridge
 * - Jet Valve
 *
 * The manager will update different CSV files. One for saving the part's name, serial number (if available), and installation/replacement date. Another CSV file tracks each parts' hours operating, the total number of hours and minutes for how long the part is running on the device. The last CSV files track each parts' hours of ventilation, the total number of hours and minutes for when the system is ventilating with each part. Both time CSV files are updated from managers internal timers that increment each second. The ventilation timer will only run when the system is ventilating. All parts installed will be logged to the Log Manager.
 *
 * ## Passcode Manager
 *
 * Updates and saves the 4 digit passcode used for creating, editing, and deleting presets, and passcode used for entering the service menu. While the main user will be able to update the preset passcode, the service technician can only update the service passcode and forcefully update the preset passcode. Updates the Log Manager for when passcodes are entered correctly, entered incorrectly, or changed.
 *
 * ## Preset Manager
 *
 * The preset manager is tasked with creating, editing, and deleting up to 12 presets onto a CSV file.
 * Each preset will include the following pneumatic settings to adjust: Driving Pressure, \htmlonly Rate\endhtmlonly, Inspiratory Time, Stacking Pressure, Oxygen Concentration,
 * Peak Inspiratory Pressure, Auxiliary Flow, and \htmlonly Humidity \endhtmlonly.
 *
 * The preset manager also creates edits and deletes the names for each preset on another CSV file. A name will be helpful in distinguishing the different presets for medical experts and are updated alongside presets.
 *
 * ## Time Manager
 *
 * The time manager runs timer to update the digital clock on the about and maintenance pages, and updates the following stored on a CSV files:
 * - <b>Date Time:</b> the date and time stored in milliseconds
 * - <b>Time Zone:</b> the time zone text display alongside digital clock
 * - <b>Internal Time:</b> the internal date and time that is never changed and is utilized for all user updates for time
 * - <b>Daylight Savings Time:</b> the state for when time zone should be in Daylight Savings Time or Standard Time
 *
 * All updates are logged to the Log Manager.
 *
 * ## Version Manager
 *
 * Manages and saves the version number for the HMI Controller and the NVENT-VITA serial number on the CSV file. Entries are logged to the Log Manager on startup.
 *
 * ## Zero Manager
 *
 * Manages and saves the sensor calibration data, including zeroing and verification values, and time stamps on CSV files. Each file will save up to 5 entries, and deletes the oldest one if new value is added.
 *
 * Sensor Calibration Procedures include the following:
 * - <b>Stacking Pressure</b>
 * - <b>Peak Inspiratory Pressure</b>
 * - <b>Inlet Air</b>
 * - <b>Inlet O<sub>2</sub></b>
 *
 */

/**
 * @ingroup backendModule
 * @defgroup gpioModule Knob Controller and other GPIO Components
 * @brief Documentation for how the software interacts with the display encoder knob through pins on the microcontroller.
 * @details
 *
 * ## Knob Controller
 *
 * The knob controller is responsible for monitoring the \htmlonly GPIO \endhtmlonly pins for the encoder and sending signals to the QML when the knob is turned or the button is pushed. It is composed of a switch object, and an encoder object. The switch object emits a signal when the button is pushed, and the encoder object emits a signal when the knob is turned. The \htmlonly GPIO \endhtmlonly object monitors pin numbers that they are given. The knob object itself uses poll to watch the file descriptors of the \htmlonly GPIO \endhtmlonly objects watching for changes. When a file descriptor is changed, the knob object updates the knob or encoder appropriately. The knob controller is also running on a QThread at the start of the display controller software. See \ref thread2 "Encoder Knob Thread"
 *
 * ## Calculating Pin Numbers
 *
 * From the SECO documentation, pin numbers are calclated using the following formula:
 *
 * (b - 1) * 32 + nn
 *
 * Using this documentation from <a href="https: * wikitech.seco.com/index.php/A62_-_J8_expansion_header_6.0/">SECO</a> is where one can fin the pin number.
 * On finds the b and nn values through the Pinout Configurations Options section of the documentation. The valeus are in the format: GPIOb_nn.
 *
 * ## Switch
 *
 * The \htmlonly Switch \endhtmlonly component of the knob controller is tasked with setting up the button in the rotary knob. The switch emits a signal for when the button is pushed and when the button is released.
 *
 * ## Encoder
 *
 * The \htmlonly Encoder \endhtmlonly component of the knob controller is tasked for listening for changes on pin A and pin B and emits signals when the knob is turned. Both pin A and pin B switch states everytime the knob is turned. If pin A changes, then this means that the signal value emitted is +1 and the knob turned clockwise. If pin B changes, then this means that signal value emitted is -1 and the knob turns counter clockwise.
 *
 * To ensure that the encoder continues to turn one direction, the encoder will read a pattern of sums representing pins as bits. A sum will be read where each bit represents a pin: [Last Pin A State, Last Pin B State, Current Pin A State, Current Pin B State]. If the sum is calculated between 13 (1101) and 2 (0010), then the encoder will continue to emit a signal of -1 for each turn. If the sum is calculated between 14 (1110) and 1 (0001), then the encoder will continue to emit a signal of +1.
 *
 * ## GPIO
 *
 * The \htmlonly GPIO \endhtmlonly object for the \htmlonly Knob \endhtmlonly Controller allows the developer to export and set the direction and edge of a pin. If the direction is "in" (the direction is always "in'' for our case), the developer can get the value of the pin in addition to exporting the pin, opening the file descriptor, getting the file descriptor, and setting the direction and edge of the pin. In Linux, the direction, edge, and value of a pin are all saved in files once the pin is exported. To modify the direction, edge, or value, the developer just needs to modify the file. One must never modify the file of a pin with direction "in '' though. To get the direction, edge, or value of a pin, one must simply read the file.
 *
 * There are 3 \htmlonly GPIO \endhtmlonly components to the knob controller, one representing pin A, one representing pin B, and one representing the switch used for the button; all are found in the <b>\htmlonly GPIO \endhtmlonly File Directory.</b>
 *
 * - <b>/sys/class/gpio</b> - root for where the \htmlonly GPIO \endhtmlonly updates any pins available
 * - <b>/sys/class/gpio/gpio9</b> - Pin A.
 * - <b>/sys/class/gpio/gpio57</b> - Pin B.
 * - <b>/sys/class/gpio/gpio55</b> - \htmlonly Switch \endhtmlonly Pin.
 *
 */

