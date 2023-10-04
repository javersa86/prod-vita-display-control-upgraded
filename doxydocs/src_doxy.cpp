//Modules for all backend components.

/**
 * @ingroup backendModule
 * @defgroup backendController Backend Controller
 * @brief Documentation for backend of the Display Controller.
 */

/**
 * @ingroup backendModule
 * @defgroup stateManager State Manager
 * @brief Documentation for managing the states of settings, modes, and other parts of the NVENT-VITA.
 */

/**
 * @ingroup backendModule
 * @defgroup warningsModule Warnings and the Warnings Manager
 * @brief Documentation for warnings and management of warnings.
 * @details
 *
 * ## Warnings
 *
 * There are a total of 70 warnings that can occur while running the NVENT-VITA. While the system determines which warnings need to be displayed and the alarms that need to be played, the display manages the data and procedures needed to handle and dismiss those warnings.
 *
 * Each warning will consist will include:
 * - A Warning ID
 * - The Title for the Warning
 * - The Class Type order of Priority
 * - The Troubleshooting Steps to end the issue coming from the Warning
 * - The clearing behavior
 * - The color of the warning
 * - The text for the clear button.
 *
 * ## Warning Classes
 *
 * There 3 types of warnings that will be triggered on the NVENT-Vita:
 * - Patient Warnings: Warnings that have the highest priority due to being directly related to a patient’s safety and health.
 *   Patient Warnings will be displayed in red. Patient Warnings will also have an audible component.
 * - System Warnings: Warnings that have second priority due to relating to issues with the system, but not directly with the patient.
 *   System Warnings will be displayed in blue. System Warnings will also have an audible component.
 * - Notices: Warnings that have the lowest priority due to being only small reminders for procedures and small system changes.
 *   Notices will be displayed in yellow.
 *
 * ## Warning Clear Behavior
 * There are 3 types of Clear Behaviors for each warning:
 * - Clear Autonomously: Warnings that are cleared on schedule.
 *   For example, the O<sub>2</sub> Calibration In Progress will be cleared after the O<sub>2</sub> calibration Procedure is complete.
 * - Clear On Demand: Warnings that are cleared from the Warning Banner’s Clear Button.
 * - Clear After Resolved: Warnings that are cleared after the issue related to the warning is fixed.
 *   For example, the Stacking Pressure High Warning is cleared after the Stacking Pressure returns to an appropriate measured value.
 *
 * ## List of Warnings
 * - PIP High!
 *   - Triggered when the measured value for Peak Inspiratory Pressure is too high for the patient.
 *   - ID: 0
 *   - Patient
 *   - Clear After Resolved
 *   - Troubleshooting Steps:
 *     - The PIP of the patient may be higher than the set PIP threshold, ensure you have egress.
 *     - Patient compliance may be low, causing rapid rise of PIP. Adjust ventilation to allow breathing to be delivered,
 *       or increase your threshold to a higher limit within safety parameters.
 *     - Patient may be gas trapping to much, causing an increased baseline.
 *     - The PIP line may be occluded and/or pinched.
 *     - The PIP sensor may need to be serviced.
 *     - Contact clinical support @ 888-730-5463.
 * - Stacking Pressure High!
 *   - Triggered when the measured value for Stacking Pressure is too high for the patient.
 *   - ID: 1
 *   - Patient
 *   - Clear After Resolved
 *   - Troubleshooting Steps:
 *     - The stacking pressure for the patient may be higher than the set stacking pressure threshold, ensure you have egress.
 *     - Patient may be gas trapping due to being obstructive. Change ventilation timing to allow for proper egress.
 *     - You may have too much Inspiratory Time, causing stacking to allow for more expiratory time and less TV.
 *     - The jet line may be occluded or pinched.
 *     - The stacking pressure sensor may need to be serviced.
 *     - Contact clinical support @ 888-730-5463.
 * - Stacking Pressure High!
 *   - Same warning as before, only on the potential second line.
 *   - ID: 2
 * - PIP Disconnected!
 *   - Triggered if PIP Disconnection Mode is enabled, and the PIP Tube is not connected to the patient.
 *   - ID: 3
 *   - Patient
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Ensure the PIP line is connected to the patient.
 *     - Ensure the PIP line is connected to the NVENT Vita.
 *     - Monitoring of this warning may be disabled through the settings menu PIP Disconnection Page, and the PIP Adjustment Page.
 * - No Water in Jet Line!
 *   - Triggered when the system is ventilating, humidity on the jet line is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.
 *   - ID: 4
 *   - Patient
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - No Water is detected in the jet line.
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Clear warning to prime the pumps.
 *   - Note: The clear button is replaced with a prime button.
 * - No Water in Jet Line!
 *   - Same warning as before, only on the potential second line.
 *   - ID: 5
 * - No Water in Auxiliary Line!
 *   - Triggered when the system is ventilating, humidity on the auxiliary line is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.
 *   - ID: 6
 *   - Patient
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - No water is detected in the auxiliary line.
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Clear warning to prime the pumps.
 *   - Note: The clear button is replaced with a prime button.
 * - No Water Prime
 *   - Triggered when the system is ventilating, humidity on the jet and auxiliary lines is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.
 *   - ID: 7
 *   - Patient
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - No water is detected when priming.
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Clear warning to prime the pumps.
 *   - Note: The clear button is replaced with a prime button.
 * - Jet Switch Error!
 *   - Triggered if the Jet Switch is defective.
 *   - ID: 8
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Jet Switch Error!
 *   - Same as before, only on the potential second line.
 *   - ID: 9
 * - Stacking Pressure Sensor Defective!
 *   - Triggered if the sensor if the Stacking Pressure Measurement reading is inaccurate to what they should be.
 *   - ID: 10
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Stacking Pressure Sensor Defective!
 *   - Same as before, only on the potential second line.
 *   - ID: 11
 * - Stacking Pressure Sensor Pneumatically Disconnected!
 *   - Triggered if the SP tube is not connected to the patient nor the device while ventilating.
 *   - ID: 12
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Ensure the jet line is connected to the patient.
 *     - Ensure the jet line is connected to the NVENT Vita.
 * - Stacking Pressure Sensor Pneumatically Disconnected!
 *   - Same as before, only on the potential second line.
 *   - ID: 13
 * - Inappropriate Oxygen Sensor Detected
 *   - Triggered if the oxygen cannot be detected.
 *   - ID: 14
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Oxygen sensor cannot be read.
 *     - Ensure that you are using a "INSERT KIND OF OXYGEN SENSOR HERE".
 *     - Ensure that oxygen sensor is securely inserted.
 * - Low Air Supply Pressure!
 *   - Triggered if the measured inlet air pressure is too low.
 *   - ID: 15
 *   - System
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The measured inlet air pressure is too low.
 *     - Ensure that the NVENT is securely connected to the air source.
 *     - The delivered oxygen concentration may be higher that expected as a result of this warning.
 * - Low Air Supply Pressure, Do Not Use Laser!
 *   - Triggered if the measured inlet air pressure is too low while oxygen concentration is too high, which is dangerous if the laser is active.
 *   - ID: 16
 *   - System
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The delivered oxygen concentration may be higher than expected. Do not use a laser.
 *     - The measured inlet air pressure is too low.
 *     - Ensure that the NVENT is securely connected to the air source.
 * - Low Oxygen Supply Pressure!
 *   - Triggered if inlet O2 Pressure is too low.
 *   - ID: 17
 *   - System
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The measured inlet oxygen pressure is too low.
 *     - Ensure the NVENT is securely connected to the oxygen source.
 * - Air Proportional Valve Error!
 *   - Trigger if the Air Proportional Valve is damaged.
 *   - ID: 18
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support & 888-730-5463
 * - Air Proportional Valve Error, Do Not Use Laser!
 *   - Trigger if the Air Proportional Valve is damaged and is recommended not to use laser while laser is active.
 *   - ID: 19
 *   - System
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - Do not use a laser 100% oxygen is delivered to the patient.
 * - Oxygen Proportional Valve Error!
 *   - Triggers if Oxygen Proportional Valve is damaged.
 *   - ID: 20
 *   - System
 *   - Clear on Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Air Inlet Pressure Sensor Error!
 *   - Triggered if the Air Inlet Pressure Sensor is damaged.
 *   - ID: 21
 *   - System
 *   - Clear on Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Air Inlet Pressure Sensor Error, Do Not Use Laser!
 *   - Triggered if the Air Inlet Pressure Sensor is damaged while the laser is active.
 *   - ID: 22
 *   - System
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - Do not use a laser 100% oxygen is delivered to the patient.
 * - Oxygen Inlet Pressure Sensor Error!
 *   - Triggered if oxygen inlet pressure sensor is damaged.
 *   - ID: 23
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Auxiliary Proportional Valve Error!
 *   - Triggered if Auxiliary Proportional Valve Error is damaged.
 *   - ID: 24
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Auxiliary Flow Sensor Error!
 *   - Triggered if the Auxiliary Flow Sensor is damaged.
 *   - ID: 25
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Speaker Defect!
 *   - Triggered if the Speaker for the alarm is damaged.
 *   - ID: 26
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Heater Failure!
 *   - Triggered if the Heater is damaged.
 *   - ID: 27
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Internal Temperature Measuring Defect!
 *   - ID: 28
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Jet Flow Sensor!
 *   - ID: 29
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Jet Flow Sensor!
 *   - ID: 30
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Jet Humidity Sensor Error!
 *   - ID: 31
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Jet Humidity Sensor Error!
 *   - ID: 32
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Auxiliary Humidity Sensor Error!
 *   - ID: 33
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Real Time Clock Error!
 *   - ID: 34
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Exhaust Fan Error
 *   - ID: 35
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Driving Pressure Regulator Error!
 *   - ID: 36
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Driving Pressure Regulator Error!
 *   - ID: 37
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - PIP Sensor Error!
 *   - ID: 38
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - FiO<sub>2</sub> Failure!
 *   - ID: 39
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Check that Air and Oxygen supplies are connected correctly.
 *     - Attempt to recalibrate the oxygen sensor in the Settings/Oxygen Calibration Menu.
 *     - The oxygen sensor may need to be replaced.
 * - Display and System Disconnected!
 *   - ID: 40
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Unable to retrieve settings, operating in headless mode.
 *     - Restart when possible.
 *     - Contact service when possible @ 888-730-5463
 * - Oxygen Calibration Failure!
 *   - ID: 41
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Check that Air and Oxygen supplies are connected correctly.
 *     - The oxygen sensor may need to be replaced.
 * - Auxiliary Water Pump Defect
 *   - ID: 42
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Service is required to change water pump.
 * - Jet Water Pump Defect
 *   - ID: 43
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Service is required to change water pump.
 * - Jet Water Pump Defect
 *   - ID: 44
 *   - Troubleshooting Steps:
 *     - Service is required to change water pump.
 * - Failed to Restore Memory
 *   - ID: 45
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The system has failed to restore data from memory.
 * - Dehumidification Failed
 *   - ID: 46
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Water may still be connected to the water inlet port.
 *     - The water inlet port may be plugged.
 *     - The output port may be plugged.
 * - Limited O<sub>2</sub>
 *   - ID: 47
 *   - Notice
 *   - Clear Autonomously
 *   - Note: Colored Green to indicate Laser is active.
 *   - Troubleshooting Steps:
 *     - Limited O<sub>2</sub> mode is active, excess oxygen has been flushed from the system, and the set oxygen concentration is below the set limited oxygen value.
 * - Limited O<sub>2</sub> Mode Prepping
 *   - ID: 48
 *   - Notice
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - Limited O<sub>2</sub> mode is active. The system is prepping for laser use.
 * - Low Static O<sub>2</sub> Pressure
 *   - ID: 49
 *   - System
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The input oxygen pressure is below 35 PSI.
 * - Low Static Air Pressure
 *   - ID: 50
 *   - System
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The input air pressure is below 35 PSI.
 * - Internal Temperature High
 *   - ID: 51
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Check that the exhaust fan (located on the device posterior) is not blocked.
 * - Manual Mode Active, PIP Monitoring Recommended
 *   - ID: 52
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Manual mode is active. Consider monitoring PIP.
 * - PIP Monitoring Recommended
 *   - ID: 53
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The set breath rate is below 80 BPM. Consider monitoring PIP.
 * - End Tidal CO<sub>2</sub> Routine Active
 *   - ID: 54
 *   - Notice
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - End-tidal CO<sub>2</sub> is in progress.
 * - Service Due
 *   - ID: 55
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The system is due for servicing. Schedule an appointment.
 * - Battery Replacement Due
 *   - ID: 56
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The battery is low. Schedule a servicing appointment.
 * - Heater and Humidifier Off
 *   - ID: 57
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The heater is defective. Schedule a servicing appointment.
 * - Humidification System Deactivated
 *   - ID: 58
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The water sensors may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 * - Humidification Deactivated on Jet Line
 *   - ID: 59
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The water sensor on the jet line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 * - Humidification Deactivated on Jet Line
 *   - ID: 60
 *   - Troubleshooting Steps:
 *     - The water sensor on the jet line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 * - Humidification Deactivated on Auxiliary Line
 *   - ID: 61
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The water sensor on the auxiliary line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 * - Auxiliary Flow Deactivated
 *   - ID: 62
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The water sensor on the auxiliary line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 * - Only Use Distilled Water For Humidification
 *   - ID: 63
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Only Use Distilled Sterile Water.
 *     - Using Saline or other composite fluids WILL clog water injectors.
 * - Pump System Priming
 *   - ID: 64
 *   - Notice
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The system is preparing to humidify the critical gases.
 * - Ventilating without Humidifying for 30+ minutes. Consider adding humidity.
 *   - ID: 65
 *   - Notice
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - The NVENT Vita has been ventilating for 30 minutes without humidification. Consider humidifying the critical gases.
 * - Oxygen Calibration in Progress
 *   - ID: 66
 *   - Notice
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The system is calibrating the oxygen sensor.
 *     - You may proceed ventilation.
 *     - The oxygen controller has been temporarily suspended.
 * - Oxygen Calibration in Progress - Do Not Use Laser
 *   - ID: 67
 *   - Notice
 *   - Clear Autonomously
 *   - Troubleshooting Steps:
 *     - The system is calibrating the oxygen sensor. Do not use a laser.
 * - Breath Failure!
 *   - ID: 68
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 * - Inspiratory Time Failure!
 *   - ID: 69
 *   - System
 *   - Clear On Demand
 *   - Troubleshooting Steps:
 *     - Contact clinical support @ 888-730-5463
 *
 * ## Warning Manager
 *
 * The warning manager tracks the state of all warnings on the system.
 * - Tracks all active warnings and notices that are displayed throughout the warning banner.
 * - Tracks all inactive warnings that are not displayed yet.
 * - Tracks all warnings that will be automatically cleared.
 *
 * The warning manager also conducts the following tasks:
 * - Receives most warnings from the notifications via backend controller and will only raise the Disconnection Warning itself if the system fails to send notifications for at least 3 seconds. Timer is created to track disconnection timer.
 * - Saves the most recent pneumatic settings for warnings raised at the time, and will be utilized for logging purposes.
 * - Returns the number of active warnings, titles, ids, descriptions, class type, color, troubleshooting steps, and clearing behavior to the warning banner.
 * - Manages the clearing of all warnings.
 * - For when Laser-Safe Mode is enabled:
 *   - Returns the states to updated the colors for Laser-Safe related QML components (the Pneumatic Button and the Laser-Safe Switch):
 *     - State 0: Laser-Safe
 *     - State 1: Laser Prepping
 *     - State 2: Neither
 *   - Updates the Laser-Safe Warning Title Text based on the different states of mode adjustments.
 */

/**
 * @ingroup backendModule
 * @defgroup modelsModule Models
 * @brief Documentation for models utilized as contants.
 * @details
 *
 * ## Models
 *
 * Constants and Models will be utilized for the the backend module.
 *
 * ## Pneumatic Settings Models
 *
 * The Pneumatic Settings Models consists of the following:
 * - Setting ID
 * - Minimum Value
 * - Maximum Value
 * - The increment value: The value that will increment or decrement the pneumatic setting value when turning the encoder knob.
 * - Minimum On Specific Value: Utilized by the Humidity Adjustment Pages to prevent a value to be set within a range.
 * - Warning Threshold: If a pneumatic setting is set greater than or equal to a warning threshold, then a warning will be sent to the GUI.
 *
 * <table>
 *  <tr>
 *      <th></th>
 *      <th>ID</th>
 *      <th>Minimum</th>
 *      <th>Maximum</th>
 *      <th>Increment</th>
 *      <th>Minimum On</th>
 *      <th>Warning Threshold</th>
 *  </tr>
 *  <tr>
 *      <th>Driving Pressure 1</th>
 *      <td>0</td>
 *      <td>5</td>
 *      <td>50</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>51</td>
 *  </tr>
 *  <tr>
 *      <th>Driving Pressure 2</th>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>50</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>51</td>
 *  </tr>
 *  <tr>
 *      <th>Rate 1</th>
 *      <td>2</td>
 *      <td>5</td>
 *      <td>150</td>
 *      <td>5</td>
 *      <td>5</td>
 *      <td>151</td>
 *  </tr>
 *  <tr>
 *      <th>Rate 2</th>
 *      <td>3</td>
 *      <td>5</td>
 *      <td>150</td>
 *      <td>5</td>
 *      <td>5</td>
 *      <td>151</td>
 *  </tr>
 *  <tr>
 *      <th>Inspiratory Time 1</th>
 *      <td>4</td>
 *      <td>20</td>
 *      <td>70</td>
 *      <td>5</td>
 *      <td>20</td>
 *      <td>60</td>
 *  </tr>
 *  <tr>
 *      <th>Inspiratory Time 2</th>
 *      <td>5</td>
 *      <td>20</td>
 *      <td>70</td>
 *      <td>5</td>
 *      <td>20</td>
 *      <td>60</td>
 *  </tr>
 *  <tr>
 *      <th>Stacking Pressure 1</th>
 *      <td>6</td>
 *      <td>1</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>Stacking Pressure 2</th>
 *      <td>7</td>
 *      <td>1</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>Oxygen</th>
 *      <td>8</td>
 *      <td>21</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>21</td>
 *      <td>101</td>
 *  </tr>
 *  <tr>
 *      <th>Peak Inspiratory Pressure</th>
 *      <td>9</td>
 *      <td>1</td>
 *      <td>100</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>Auxiliary Flow</th>
 *      <td>10</td>
 *      <td>0</td>
 *      <td>70</td>
 *      <td>1</td>
 *      <td>0</td>
 *      <td>71</td>
 *  </tr>
 *  <tr>
 *      <th>Humidity 1</th>
 *      <td>11</td>
 *      <td>0</td>
 *      <td>100</td>
 *      <td>10</td>
 *      <td>30</td>
 *      <td>101</td>
 *  </tr>
 *  <tr>
 *      <th>Humidity 2</th>
 *      <td>12</td>
 *      <td>0</td>
 *      <td>100</td>
 *      <td>10</td>
 *      <td>30</td>
 *      <td>101</td>
 *  </tr>
 *  <tr>
 *      <th>Humidity Auxiliary</th>
 *      <td>13</td>
 *      <td>0</td>
 *      <td>100</td>
 *      <td>10</td>
 *      <td>30</td>
 *      <td>101</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal Rate</th>
 *      <td>14</td>
 *      <td>5</td>
 *      <td>30</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>31</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal Inspiratory time</th>
 *      <td>15</td>
 *      <td>20</td>
 *      <td>70</td>
 *      <td>5</td>
 *      <td>20</td>
 *      <td>71</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal Number of Breaths</th>
 *      <td>16</td>
 *      <td>1</td>
 *      <td>10</td>
 *      <td>1</td>
 *      <td>1</td>
 *      <td>11</td>
 *  </tr>
 *  <tr>
 *      <th>End-Tidal Driving Pressure</th>
 *      <td>17</td>
 *      <td>5</td>
 *      <td>50</td>
 *      <td>1</td>
 *      <td>5</td>
 *      <td>51</td>
 *  </tr>
 *  <tr>
 *      <th>Laser-Safe Oxygen</th>
 *      <td>18</td>
 *      <td>21</td>
 *      <td>40</td>
 *      <td>1</td>
 *      <td>21</td>
 *      <td>41</td>
 *  </tr>
 *  <tr>
 *      <th>Volume</th>
 *      <td>19</td>
 *      <td>20</td>
 *      <td>100</td>
 *      <td>10</td>
 *      <td>20</td>
 *      <td>101</td>
 *  </tr>
 * </table>
 *
 * ## Notifications
 *
 * When the NVENT-VITA is running, there will be a constant flow of the following measured values on the home page:
 * - Stacking Pressure
 * - Stacking Pressure (only available on the second jet line)
 * - Oxygen Concentration
 * - Peak Inspiratory Pressure
 * - Auxiliary Flow
 * - Tidal Volume
 * - Tidal Volume (only available on the second jet line)
 * - Mean Airway Pressure
 * - O2 Calibration Voltage (only displayed through the Service Menu O<sub>2</sub> Calibration Page.
 * - Silence Time (only displayed on the warning banner's silence button)
 */

/**
 * @ingroup backendModule
 * @defgroup loggerModule Log Manager and other Managers
 * @brief Documentation for how the display controller stores data internally through multiple directories.
 * @details
 *
 * ## CSV Manager
 *
 * The CSV Manager is the most important component to all data managers on the display controller,
 * for it acts as a tool to read and write the rows and columns of CSV files (Comma-Separated Value).
 * The CSV Manager can also update rows of CSV files, delete rows, and return the number of entries representing each row.
 *
 * ## Log Manager
 *
 * The Log Manager is tasks with writing all the service logs and warning logs on the system. Events on the service logs include settings requests,
 * mode switches, warnings triggered, and other events.
 * For whenever the NVENT-VITA display software starts up, two CSV files are created and stored onto the display controller's internal directory.
 * One for writing all activites on the display, while another is specifically for when warnings are triggered.
 * Each CSV filename will have the date and time of its creation. An incremented number will be added at the end of the filename for duplicates.
 * Each service log entries will consists of the following:
 * - TIMESTAMP: The date and time for when the event occurred.
 * - TYPE: Which type and location for what activity is occuring. The label "(SERVICE)" will be written for activities involving the Service Menu.
 * - EVENT: A description for what is occuring on the device.
 *
 * The writing of all service log entries are triggered from qInfo statements in the backend source code.
 * IMPORTANT: Service log files are deleted after 2 weeks and warning logs are deleted after 3 months.
 *
 * ## Brightness Manager
 *
 * Connects with the display controller's internal systems to update the brightness of the display controller screen.
 * Brightness is adjusted via the knob controller.
 *
 * ## Contact Manager
 *
 * Updates and saves contact information for the servicing company (Susquehanna Micro) and the Sales Company (Lantern Medical) on to two CSV Files.
 * Contact Information include the following:
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
 * Logs the dates and times of the lowest and highest Driving Pressure Regulator Calibration values (technically the same measurement types) onto a CSV file.
 * The manager will store up to 5 entries and will delete oldest entry when adding a new one.
 *
 * ## Maintenance Manager
 *
 * Updates and saves dates for the last service appointment and the next service appointment onto a CSV file.
 *
 * ## O2 Calibration Manager
 *
 * Logs the dates and times of the lowest and highest O<sub>2</sub> Calibration Values and Voltages onto a CSV file.
 * The manager will save up to 5 entries and will delete the oldest entry when adding a new one.
 * The manager is also tasked with running the timers for the Warning Banner's O<sub>2</sub> Calibration 1 minute progress time and for the
 * Lase-Safe 45 second Rest Period.
 *
 * ## Part Manager
 *
 * Manages and updates the data for all 23 parts that can be replaced on the device. The parts included:
 * - Oxygen Sensor
 * - 25 Micron Filter (Air Inlet Filter)
 * - 25 Micron Filter (Oxygen Inlet Filter)
 * - Water Injector (Jet Line)
 * - Water Injector (Auxiliary Line)
 * - Humidity Sensor (Jet Line)
 * - Humidity Sensor (Auxiliary Line)
 * - Humidity Sensor (PCB)
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
 * The manager will update different CSV files. One for saving the part's name, serial number (if available), and installation/replacement date.
 * Another CSV file tracks each parts' hours operating, the total number of hours and minutes for how long the part is running on the device.
 * The last CSV files tracks each parts' hours of ventilation, the total number of hours and minutes for when the system is ventilating with each part.
 * Both time CSV files are updated from managers internal timers that increment each second. The ventilation timer will only run when system is ventilating.
 *
 * ## Passcode Manager
 *
 * Updates and saves the 4 digit passcode used for creating, editing, and deleting presets, and passcode used for entering the service menu.
 * While the main user will be able to update the preset passcode, the service technician can only update the service passcode and forcefully
 * update the preset passcode.
 *
 * ## Preset Manager
 *
 * The preset manager is tasked with creating, editing, and deleting up to 12 presets onto a CSV file.
 * Each preset will include the following pneumatic settings to adjust: Driving Pressure, Rate, Inspiratory Time, Stacking Pressure, Oxygen Concentration,
 * Peak Inspiratory Pressure, Auxiliary Flow, and Humidity.
 *
 * The preset manager also creates edits and deletes the names for each preset on another CSV file. A name will be helpful in distinguishing the
 * different presets for medical experts and are updated alongside presets.
 *
 * ## Time Manager
 *
 * The time manager runs timer to update the digital clock on the about and maintenance pages, and updates the following stored on a CSV files:
 * - <b>Date Time:</b> the date and time stored in milliseconds
 * - <b>Time Zone:</b> the time zone text display alongside digital clock
 * - <b>Internal Time:</b> the internal date and time that is never changed and is utilized for all user updates for time.
 *
 * ## Version Manager
 *
 * Manages and saves the version number for the HMI Controller and the NVENT-VITA serial number on the CSV file.
 *
 * ## Zero Manager
 *
 * Manages and saves the sensor calibration data, including zeroing and verification values, and time stamps on CSV files.
 * Each file will save up to 5 entries, and deletes the oldest on if new value is added.
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
 * The knob controller is responsible for monitoring the GPIO pins for the encoder and sending signals to the QML when the knob is turned or the button is pushed. It is composed of a switch object, and an encoder object. The switch object emits a signal when the button is pushed, and the encoder object emits a signal when the knob is turned. The GPIO object monitors pin numbers that they are given. The knob object itself uses poll to watch the file descriptors of the GPIO objects watching for changes. When a file descriptor is changed, the knob object updates the knob or encoder appropriately. The knob controller is also running on a QThread at the start of the display controller software.
 *
 * ## Calculating Pin Numbers
 *
 * From the SECO documentation, pin numbers are calclated using the following formula:
 *
 * (b - 1) * 32 + nn
 *
 * Using this documentation from <a href="https://wikitech.seco.com/index.php/A62_-_J8_expansion_header_6.0/">SECO</a> is where one can fin the pin number.
 * On finds the b and nn values through the Pinout Configurations Options section of the documentation. The valeus are in the format: GPIOb_nn.
 *
 * ## Switch
 *
 * The Switch component of the knob controller is tasked with setting up the button in the rotary knob.
 * The switch emits a signal for when the button is pushed and when the button is released.
 *
 * ## Encoder
 *
 * The Encoder component of the knob controller is tasked for listening for changes on pin A and pin B and emits signals when the knob is turned.
 * Both pin A and pin B switch states everytime the knob is turned.
 * If pin A changes, then this means that the signal value emitted is +1 and the knob turned clockwise.
 * If pin B changes, then this means that signal value emitted is -1 and the knob turns counter clockwise.
 *
 * ## GPIO
 *
 * <b>Definitions</b>
 *
 * - <b>GPIO (General Purpose Input/Output):</b> a set of pins on a microcontroller or single-board computer that can be configured to either read input signals
 *   from external devices or provide output signals to control external devices.
 *   GPIO pins can be used to interact with various electronic components and peripherals, such as sensors, LEDS, motors, buttons, and more.
 *
 * The GPIO object for the Knob Controller allows the developer to export and set the direction and edge of a pin. If the direction is "in" (the direction is always "in'' for our case), the developer can get the value of the pin in addition to exporting the pin, opening the file descriptor, getting the file descriptor, and setting the direction and edge of the pin. In Linux, the direction, edge, and value of a pin are all saved in files once the pin is exported. To modify the direction, edge, or value, the developer just needs to modify the file. One must never modify the file of a pin with direction "in '' though. To get the direction, edge, or value of a pin, one must simply read the file.
 *
 * There are 3 GPIO components to the knob controller, one representing pin A, one representing pin B, and one representing the switch used for the button.
 *
 */

