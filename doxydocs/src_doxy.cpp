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
 * - A \htmlonly Warning \endhtmlonly ID
 * - The Title for the \htmlonly Warning \endhtmlonly
 * - The Class Type order of Priority
 * - The Troubleshooting Steps to end the issue coming from the \htmlonly Warning \endhtmlonly
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
 * - Clear On Demand: Warnings that are cleared from the \htmlonly Warning \endhtmlonly Banner’s Clear Button.
 * - Clear After Resolved: Warnings that are cleared after the issue related to the warning is fixed.
 *   For example, the Stacking Pressure High \htmlonly Warning \endhtmlonly is cleared after the Stacking Pressure returns to an appropriate measured value.
 *
 * ## List of Warnings
 *
 * <table>
 *  <tr>
 *      <th style="background-color: #202531; border-color: #202531">Warnings</th>
 *      <th style="background-color: #202531; border-color: #202531">Description</th>
 *      <th style="background-color: #202531; border-color: #202531">ID</th>
 *      <th style="background-color: #202531; border-color: #202531">Type</th>
 *      <th style="background-color: #202531; border-color: #202531">Clear Behavior</th>
 *      <th style="background-color: #202531; border-color: #202531">Troubleshooting Step</th>
 *      <th style="background-color: #202531; border-color: #202531">Additional Information</th>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">\htmlonly PIP \endhtmlonly High!</th>
 *      <td>Triggered when the measured value for Peak Inspiratory Pressure is too high for the patient.</td>
 *      <td>0</td>
 *      <td>Patient</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *      - The \htmlonly PIP \endhtmlonly of the patient may be higher than the set \htmlonly PIP \endhtmlonly threshold, ensure there is egress.
 *      - Patient compliance may be low, causing rapid rise of \htmlonly PIP\endhtmlonly. Adjust settings to allow ventilation to resume within safe parameters.
 *      - Patient may be gas trapping causing the stacking of breaths and/or an increased baseline.
 *      - The \htmlonly PIP \endhtmlonly line may be occluded and/or pinched.
 *      - Patient may be spontaneously breathing.
 *      - The \htmlonly PIP \endhtmlonly sensor may be defective.
 *      - Contact support @ 888-730-5463.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">Stacking Pressure High!</th>
 *      <td>Triggered when the measured value for Stacking Pressure is too high for the patient.</td>
 *      <td>1<br>2</td>
 *      <td>Patient</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *      - The Stacking Pressure of the patient may be higher than the set SP threshold, ensure there is egress.
 *      - Patient may be gas trapping causing the stacking of breaths and/or an increased baseline.
 *      - The Jet Line may be occluded and/or pinched.
 *      - Patient may be spontaneously breathing.
 *      - The SP sensor may be defective.
 *      - Contact support @ 888-730-5463.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">\htmlonly PIP \endhtmlonly Disconnected!</th>
 *      <td>Triggered if \htmlonly PIP \endhtmlonly Disconnection Mode is enabled, and the \htmlonly PIP \endhtmlonly Tube is not connected to the patient.</td>
 *      <td>3</td>
 *      <td>Patient</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *      - Ensure the \htmlonly PIP \endhtmlonly line is connected to the patient.
 *      - Ensure the \htmlonly PIP \endhtmlonly line is connected to the NVENT Vita.
 *      - The \htmlonly PIP \endhtmlonly line may see no pressure even when the red line is used depending on the point of reference and how open the system is.
 *      - Monitoring of this warning may be disabled through the settings menu \htmlonly PIP \endhtmlonly Disconnection Page, and the \htmlonly PIP \endhtmlonly Adjustment Page.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Jet Line!</th>
 *      <td>Triggered when the system is ventilating, humidity on the jet line is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.</td>
 *      <td>4<br>5</td>
 *      <td>Patient</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Press prime in the warning banner to prime the pumps.
 *      </td>
 *      <td>The clear button is replaced with a prime button.</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Auxiliary Line!</th>
 *      <td>Triggered when the system is ventilating, humidity on the auxiliary line is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.</td>
 *      <td>6</td>
 *      <td>Patient</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Press prime in the warning banner to prime the pumps.
 *      </td>
 *      <td>The clear button is replaced with a prime button.</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Jet and Auxiliary Lines!</th>
 *      <td>Triggered when the system is ventilating, humidity on the jet and auxiliary lines is greater than 0, and water isn’t detected.
 *     The heat might be uncomfortable to the patient.</td>
 *      <td>7</td>
 *      <td>Patient</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Press prime in the warning banner to prime the pumps.
 *      </td>
 *      <td>The Clear button is replaced with a prime button.</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet \htmlonly Switch \endhtmlonly Error!</th>
 *      <td>Triggered if the Jet \htmlonly Switch \endhtmlonly is defective.</td>
 *      <td>8<br>9</td>
 *      <td>System</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Stacking Pressure Sensor Defective!</th>
 *      <td>Triggered if the sensor if the Stacking Pressure Measurement reading is inaccurate to what they should be.</td>
 *      <td>10<br>11</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *      - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Stacking Pressure Internally Disconnected!</th>
 *      <td>Triggered if the SP tube is not connected to the patient nor the device while ventilating.</td>
 *      <td>12<br>13</td>
 *      <td>System</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Ensure the jet line is connected to the patient.
 *     - Ensure the jet line is connected to the NVENT Vita.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Inappropriate Oxygen Sensor Detected</th>
 *      <td>Triggered if the oxygen cannot be detected.</td>
 *      <td>14</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Oxygen sensor cannot be read.
 *     - Ensure that you are using a "INSERT KIND OF OXYGEN SENSOR HERE".
 *     - Ensure that oxygen sensor is securely inserted.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Air Supply Pressure!</th>
 *      <td>Triggered if the measured inlet air pressure is too low.</td>
 *      <td>15</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - The measured inlet air pressure is too low.
 *     - Ensure that the NVENT is securely connected to the air source.
 *     - The delivered oxygen concentration may be higher that expected as a result of this warning.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Air Supply Pressure, Limited O<sub>2</sub> Adjustment In Progress!</th>
 *      <td>Triggered if the measured inlet air pressure is too low while oxygen concentration is too high, which is dangerous if the laser is active.</td>
 *      <td>16</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - The delivered oxygen concentration may be higher than expected. Do not use a laser.
 *     - The measured inlet air pressure is too low.
 *     - Ensure that the NVENT is securely connected to the air source.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Oxygen Supply Pressure!</th>
 *      <td>Triggered if inlet O<sub>2</sub> Pressure is too low.</td>
 *      <td>17</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - The measured inlet oxygen pressure is too low.
 *     - Ensure the NVENT is securely connected to the oxygen source.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Proportional Valve Error!</th>
 *      <td>Trigger if the Air Proportional Valve is damaged.</td>
 *      <td>18</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support & 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Proportional Valve Error, Limited O<sub>2</sub> Adjustment in Progress!</th>
 *      <td>Trigger if the Air Proportional Valve is damaged and is recommended not to use laser while laser is active.</td>
 *      <td>19</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Do not use a laser 100% oxygen is delivered to the patient.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Proportional Valve Error!</th>
 *      <td>Triggers if Oxygen Proportional Valve is damaged.</td>
 *      <td>20</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Inlet Pressure Sensor Error!</th>
 *      <td>Triggered if the Air Inlet Pressure Sensor is damaged.</td>
 *      <td>21</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Inlet Pressure Sensor Error, Limited O<sub>2</sub> Adjustment in Progress!</th>
 *      <td>Triggered if the Air Inlet Pressure Sensor is damaged while the laser is active.</td>
 *      <td>22</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Do not use a laser 100% oxygen is delivered to the patient.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Inlet Pressure Sensor Error!</th>
 *      <td>Triggered if oxygen inlet pressure sensor is damaged.</td>
 *      <td>23</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Proportional Valve Error!</th>
 *      <td>Triggered if Auxiliary Proportional Valve Error is damaged.</td>
 *      <td>24</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Flow Sensor Error!</th>
 *      <td>Triggered if the Auxiliary Flow Sensor is damaged.</td>
 *      <td>25</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Speaker Defect!</th>
 *      <td>Triggered if the Speaker for the alarm is damaged.</td>
 *      <td>26</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Heater Failure!</th>
 *      <td>Triggered if the Heater is damaged.</td>
 *      <td>27</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Internal Temperature Measuring Defect!</th>
 *      <td></td>
 *      <td>28</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Flow Sensor!</th>
 *      <td></td>
 *      <td>29<br>30</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet \htmlonly Humidity \endhtmlonly Sensor Error!</th>
 *      <td></td>
 *      <td>31<br>32</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary \htmlonly Humidity \endhtmlonly Sensor Error!</th>
 *      <td></td>
 *      <td>33</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Real Time Clock Error!</th>
 *      <td></td>
 *      <td>34</td>
 *      <td>System</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Exhaust Fan Error</th>
 *      <td></td>
 *      <td>35</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Driving Pressure Regulator Error!</th>
 *      <td></td>
 *      <td>36<br>37</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">\htmlonly PIP \endhtmlonly Sensor Error!</th>
 *      <td></td>
 *      <td>38</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">FiO<sub>2</sub> Failure!</th>
 *      <td></td>
 *      <td>39</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Check that Air and Oxygen supplies are connected correctly.
 *     - Attempt to recalibrate the oxygen sensor in the Settings/Oxygen Calibration Menu.
 *     - The oxygen sensor may need to be replaced.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Display and System Disconnected!</th>
 *      <td></td>
 *      <td>40</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Unable to retrieve settings, operating in headless mode.
 *     - Restart when possible.
 *     - Contact service when possible @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Calibration Failure!</th>
 *      <td></td>
 *      <td>41</td>
 *      <td>System</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Check that Air and Oxygen supplies are connected correctly.
 *     - The oxygen sensor may need to be replaced.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Water Pump Defect</th>
 *      <td></td>
 *      <td>42</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Service is required to change water pump.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Water Pump Defect</th>
 *      <td></td>
 *      <td>43<br>44</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Service is required to change water pump.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Failed to Restore Memory</th>
 *      <td></td>
 *      <td>45</td>
 *      <td>System</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - The system has failed to restore data from memory.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Dehumidification Failed</th>
 *      <td></td>
 *      <td>46</td>
 *      <td>System</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Water may still be connected to the water inlet port.
 *     - The water inlet port may be plugged.
 *     - The output port may be plugged.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Breath Timing Failure!</th>
 *      <td></td>
 *      <td>47</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Water Sensor Failure!</th>
 *      <td></td>
 *      <td>48</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Water Sensor Failure!</th>
 *      <td></td>
 *      <td>49</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Ambient Temperature Sensor Defect!</th>
 *      <td></td>
 *      <td>50</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Internal System Temperature High</th>
 *      <td></td>
 *      <td>51</td>
 *      <td>System</td>
 *      <td>Clear After Resolved</td>
 *      <td>
 *     - Check that the exhaust fan (located on the device posterior) is not blocked.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #6FCC68; border-color: #202531">Limited O<sub>2</sub> Safe</th>
 *      <td>Triggered when Limited O<sub>2</sub> is enabled and the oxygen measurement is within the Limited O<sub>2</sub> Oxygen Concentration Range.</td>
 *      <td>52</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - Limited O<sub>2</sub> mode is active, excess oxygen has been flushed from the system, and the set oxygen concentration is below the set limited oxygen value.
 *      </td>
 *      <td>
 *   - Note: Colored Green to indicate Laser is active but oxygen is within safe range.
 *   - Note: Depending on the different states of Oxygen Concentration, alternative titles include Limited O<sub>2</sub> Prepping to 21%, Limited O<sub>2</sub> Prepping at 21%, and Limited O<sub>2</sub> Prepping to (Set Value).</td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Limited O<sub>2</sub> Prepping</th>
 *      <td>Triggered when Limited O<sub>2</sub> is enabled and the oxygen measurement is outside of the Limited O<sub>2</sub> Oxygen Concentration Range.</td>
 *      <td>53</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - Limited O<sub>2</sub> mode is active. The system is prepping for laser use.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Low Static O<sub>2</sub> Pressure</th>
 *      <td></td>
 *      <td>54</td>
 *      <td>System</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The input oxygen pressure is below 35 PSI.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Low Static Air Pressure</th>
 *      <td></td>
 *      <td>55</td>
 *      <td>System</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The input air pressure is below 35 PSI.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Manual Mode Active, \htmlonly PIP \endhtmlonly Monitoring Recommended</th>
 *      <td></td>
 *      <td>56</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Manual mode is active. Consider monitoring \htmlonly PIP\endhtmlonly.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">\htmlonly PIP \endhtmlonly Monitoring Recommended</th>
 *      <td></td>
 *      <td>57</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - The set breath rate is below 80 BPM. Consider monitoring \htmlonly PIP\endhtmlonly.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">End Tidal CO<sub>2</sub> Routine Active</th>
 *      <td></td>
 *      <td>58</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - End-tidal CO<sub>2</sub> is in progress.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Service Due</th>
 *      <td></td>
 *      <td>59</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - The system is due for servicing. Schedule an appointment.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Battery Replacement Due</th>
 *      <td></td>
 *      <td>60</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - The battery is low. Schedule a servicing appointment.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Heater and Humidifier Off</th>
 *      <td></td>
 *      <td>61</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The heater is defective. Schedule a servicing appointment.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification System Deactivated</th>
 *      <td></td>
 *      <td>62</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The water sensors may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification Deactivated on Jet Line</th>
 *      <td></td>
 *      <td>63<br>64</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The water sensor on the jet line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification Deactivated on Auxiliary Line</th>
 *      <td></td>
 *      <td>65</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The water sensor on the auxiliary line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Auxiliary Flow Deactivated</th>
 *      <td></td>
 *      <td>66</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The water sensor on the auxiliary line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Only Use Distilled Water For Humidification</th>
 *      <td></td>
 *      <td>67</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - Only Use Distilled Sterile Water.
 *     - Using Saline or other composite fluids WILL clog water injectors.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Pump System Priming</th>
 *      <td></td>
 *      <td>68</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The system is preparing to humidify the critical gases.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Ventilating without Humidifying for 30+ minutes. Consider adding humidity.</th>
 *      <td></td>
 *      <td>69</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear On Demand</td>
 *      <td>
 *     - The NVENT Vita has been ventilating for 30 minutes without humidification. Consider humidifying the critical gases.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Oxygen Calibration in Progress, Limited O<sub>2</sub> Adjustment in Progress</th>
 *      <td></td>
 *      <td>70</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The system is calibrating the oxygen sensor. Do not use a laser.
 *      </td>
 *      <td></td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Oxygen Calibration in Progress</th>
 *      <td></td>
 *      <td>71</td>
 *      <td>\htmlonly Notice \endhtmlonly</td>
 *      <td>Clear Autonomously</td>
 *      <td>
 *     - The system is calibrating the oxygen sensor.
 *     - You may proceed ventilation.
 *     - The oxygen controller has been temporarily suspended.
 *      </td>
 *      <td></td>
 *  </tr>
 * </table>
 *
 * ## Warning Manager
 *
 * The warning manager tracks the state of all warnings on the system.
 * - Tracks all active warnings and notices that are displayed throughout the warning banner.
 * - Tracks all inactive warnings that are not displayed yet.
 * - Tracks all warnings that will be automatically cleared.
 *
 * The warning manager also conducts the following tasks:
 * - Receives most warnings from the notifications via backend controller and will only raise the Disconnection \htmlonly Warning \endhtmlonly itself if the system fails to send notifications for at least 3 seconds. Timer is created to track disconnection timer.
 *   - Prevents the No Communication warning from triggering when Service Menu is opened due to notifications pausing.
 * - Saves the most recent pneumatic settings for warnings raised at the time, and will be utilized for logging purposes.
 * - Returns the number of active warnings, titles, ids, descriptions, class type, color, troubleshooting steps, and clearing behavior to the warning banner.
 * - Manages the clearing of all warnings.
 * - For when Limted O<sub>2</sub> Mode is enabled:
 *   - Returns the states to updated the colors for Limted O<sub>2</sub> related QML components (the Pneumatic Button and the Limted O<sub>2</sub> Switch):
 *     - State 0: Limted O<sub>2</sub> Safe
 *     - State 1: Limted O<sub>2</sub> Prepping or O<sub>2</sub> Calibration
 *     - State 2: Neither
 *   - Updates the Limted O<sub>2</sub> \htmlonly Warning \endhtmlonly Title Text based on the different states of mode adjustments.
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
 * - Minimum On Specific Value: Utilized by the \htmlonly Humidity \endhtmlonly Adjustment Pages to prevent a value to be set within a range.
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
 *      <td>70</td>
 *      <td>1</td>
 *      <td>0</td>
 *      <td>71</td>
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
 * ## Notifications
 *
 * When the NVENT-VITA is running, there will be a constant flow of the following measured values on the home page:
 * - Stacking Pressure
 * - Stacking Pressure (only available on the second jet line)
 * - Oxygen Concentration
 * - Peak Inspiratory Pressure
 * - Auxiliary Flow
 * - Tidal \htmlonly Volume \endhtmlonly
 * - Tidal \htmlonly Volume \endhtmlonly (only available on the second jet line)
 * - Mean Airway Pressure
 * - Silence Time (only displayed on the warning banner's silence button)
 *
 * ## Service Notifications
 *
 * When the NVENT-VITA is running and the service menu is accessed, there will be a constant flow of the following measured values on the home page (Notifications is paused while active):
 * - Stacking Pressure Average Data
 * - Stacking Pressure Instantaneous Data
 * - Peak Inspiratory Pressure Average Data
 * - Peak Inspiratory Pressure Instantaneous Data
 * - O<sub>2</sub> Calibration Voltage (only displayed through the Service Menu O<sub>2</sub> Calibration Page.
 */

/**
 * @ingroup backendModule
 * @defgroup loggerModule Log Manager and other Managers
 * @brief Documentation for how the display controller stores data internally through multiple directories.
 * @details
 *
 * ## CSV Manager
 *
 * The CSV Manager is the most important component to all data managers on the display controller, for it acts as a tool to read and write the rows and columns of CSV files (Comma-Separated Value).
 * The CSV Manager can also update rows of CSV files, delete rows, and return the number of entries representing each row.
 *
 * ## Log Manager
 *
 * The Log Manager is tasks with writing all the service logs and warning logs on the system. Events on the service logs include settings requests, mode switches, warnings triggered, and other events.
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
 * The manager is also tasked with running the timers for the \htmlonly Warning \endhtmlonly Banner's O<sub>2</sub> Calibration 1 minute progress time and for the
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
 * Each preset will include the following pneumatic settings to adjust: Driving Pressure, \htmlonly Rate\endhtmlonly, Inspiratory Time, Stacking Pressure, Oxygen Concentration,
 * Peak Inspiratory Pressure, Auxiliary Flow, and \htmlonly Humidity \endhtmlonly.
 *
 * The preset manager also creates edits and deletes the names for each preset on another CSV file. A name will be helpful in distinguishing the
 * different presets for medical experts and are updated alongside presets.
 *
 * ## Time Manager
 *
 * The time manager runs timer to update the digital clock on the about and maintenance pages, and updates the following stored on a CSV files:
 * - <b>Date Time:</b> the date and time stored in milliseconds
 * - <b>Time Zone:</b> the time zone text display alongside digital clock
 * - <b>Internal Time:</b> the internal date and time that is never changed and is utilized for all user updates for time
 * - <b>Daylight Savings Time:</b> the state for when time zone should be in Daylight Savings Time or Standard Time
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
 * The knob controller is responsible for monitoring the \htmlonly GPIO \endhtmlonly pins for the encoder and sending signals to the QML when the knob is turned or the button is pushed. It is composed of a switch object, and an encoder object. The switch object emits a signal when the button is pushed, and the encoder object emits a signal when the knob is turned. The \htmlonly GPIO \endhtmlonly object monitors pin numbers that they are given. The knob object itself uses poll to watch the file descriptors of the \htmlonly GPIO \endhtmlonly objects watching for changes. When a file descriptor is changed, the knob object updates the knob or encoder appropriately. The knob controller is also running on a QThread at the start of the display controller software. See \ref thread2 "Encoder Knob Thread"
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
 * The \htmlonly Switch \endhtmlonly component of the knob controller is tasked with setting up the button in the rotary knob.
 * The switch emits a signal for when the button is pushed and when the button is released.
 *
 * ## Encoder
 *
 * The \htmlonly Encoder \endhtmlonly component of the knob controller is tasked for listening for changes on pin A and pin B and emits signals when the knob is turned.
 * Both pin A and pin B switch states everytime the knob is turned.
 * If pin A changes, then this means that the signal value emitted is +1 and the knob turned clockwise.
 * If pin B changes, then this means that signal value emitted is -1 and the knob turns counter clockwise.
 *
 * To ensure that the encoder continues to turn one direction, the encoder will read a pattern of sums representing pins as bits. A sum will be read where each bit represents a pin: [Last Pin A State, Last Pin B State, Current Pin A State, Current Pin B State]. If the sum is calculated between 13 (1101) and 2 (0010), then the encoder will continue to emit a signal of -1 for each turn. If the sum is calculated between 14 (1110) and 1 (0001), then the encoder will continue to emit a signal of +1.
 *
 * ## GPIO
 *
 * <b>Definitions</b>
 *
 * - <b> \htmlonly GPIO \endhtmlonly (General Purpose Input/Output):</b> a set of pins on a microcontroller or single-board computer that can be configured to either read input signals from external devices or provide output signals to control external devices. \htmlonly GPIO \endhtmlonly pins can be used to interact with various electronic components and peripherals, such as sensors, LEDS, motors, buttons, and more.
 *
 * The \htmlonly GPIO \endhtmlonly object for the \htmlonly Knob \endhtmlonly Controller allows the developer to export and set the direction and edge of a pin. If the direction is "in" (the direction is always "in'' for our case), the developer can get the value of the pin in addition to exporting the pin, opening the file descriptor, getting the file descriptor, and setting the direction and edge of the pin. In Linux, the direction, edge, and value of a pin are all saved in files once the pin is exported. To modify the direction, edge, or value, the developer just needs to modify the file. One must never modify the file of a pin with direction "in '' though. To get the direction, edge, or value of a pin, one must simply read the file.
 *
 * <b>GPIO File Directory Access</b>
 * There are 3 \htmlonly GPIO \endhtmlonly components to the knob controller, one representing pin A, one representing pin B, and one representing the switch used for the button.
 *
 * - /sys/class/gpio - root for where the GPIO updates any pins available
 * - /sys/class/gpio/gpio9 - Pin A.
 * - /sys/class/gpio/gpio57 - Pin B.
 * - /sys/class/gpio/gpio55 - Switch Pin.
 *
 */

