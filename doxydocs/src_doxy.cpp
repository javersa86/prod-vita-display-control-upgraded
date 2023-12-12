/**
 * @ingroup backendModule
 * @defgroup backendController Backend Controller
 * @brief Documentation for backend of the Display Controller.
 * @{
 * @details
 *
 * \section backendController Backend Controller
 *
 * \subsection backendController_description Backend Description
 *
 * The backend controller is where all activity occurs from the user inputs on the Graphical User Interface and the updates from the system controller. Note that all activities interact with all the managers on the application; see State Manager, Warnings and \htmlonly Warning \endhtmlonly Manager, and Log Manager and other Managers for detail on how data and log entries are saved on the display.
 *
 * \subsection backendController_request_function Backend Request Function
 *
 * Requests functions construct Op Code Requests that are sent to the system controller through the \htmlonly API \endhtmlonly Thread. The process of sending messages to the \htmlonly API \endhtmlonly go as followed:
 * 1. Requests are contructed through different datetypes like unsigned characters, ints, and QVectors.
 * 2. The requests are sent to the \htmlonly API \endhtmlonly thread via emitted QObject signals.
 * 3. After the first signal is sent, the associated unsigned char variable called a flag will be set to true (raised).
 * 4. While a flag is raised, the associated signal will continue to be emitted with the contructed request.
 * 5. The flag will be set to false (lowered) when the \htmlonly API \endhtmlonly thread emits their response signal and trigger the \htmlonly Backend \endhtmlonly QObject response slot.
 *
 * \subsection backendController_startup_requests Backend Startup Requests
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
 * \subsection backendController_requests Backend Requests
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
 * \subsection backendController_functions Other Backend Functions
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
 * \section stateManager State Manager
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
 * \section warningsModule Warnings and Warning Manager
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
 * \subsection warningsModule_classes Warning Classes
 *
 * There 3 types of warnings that will be triggered on the NVENT-Vita:
 * - <b>Patient Warnings:</b> Warnings that have the highest priority due to being directly related to a patient’s safety and health. Patient Warnings will be displayed in red. Patient Warnings will also have an audible component.
 * - <b>System Warnings:</b> Warnings that have second priority due to relating to issues with the system, but not directly with the patient. System Warnings will be displayed in blue. System Warnings will also have an audible component.
 * - <b>Notices:</b> Warnings that have the lowest priority due to being only small reminders for procedures and small system changes. Notices will be displayed in yellow.
 *
 * \subsection warningsModule_clear_behavior Warning Clear Behavior
 *
 * There are 3 types of Clear Behaviors for each warning:
 * - <b>Clear Autonomously:</b> Warnings that are cleared on schedule.
 *   For example, the O<sub>2</sub> Calibration In Progress will be cleared after the O<sub>2</sub> calibration Procedure is complete.
 * - <b>Clear On Demand:</b> Warnings that are cleared from the \htmlonly Warning \endhtmlonly Banner’s Clear Button.
 * - <b>Clear After Resolved:</b> Warnings that are cleared after the issue related to the warning is fixed.
 *   For example, the Stacking Pressure High \htmlonly Warning \endhtmlonly is cleared after the Stacking Pressure returns to an appropriate measured value.
 *
 */

/**
 * @ingroup backendModule
 * @defgroup modelsModule Models
 * @brief Documentation for models utilized as contants.Constants and Models will be utilized throughout the backend as identifiers to distinguish between modes, pneumatic settings, and other settings.
 */

/**
 * @ingroup backendModule
 * @defgroup loggerModule Log Manager and other Managers
 * @brief Documentation for how the display controller stores data internally through multiple directories.
 *
 */

/**
 * @ingroup backendModule
 * @defgroup gpioModule Knob Controller and other GPIO Components
 * @brief Documentation for how the software interacts with the display encoder knob through pins on the microcontroller.
 *
 */

