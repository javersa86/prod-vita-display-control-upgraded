//Module for warnings.

/**
 * @ingroup warningsModule
 * @defgroup warningsParent List of Warnings
 * @brief Documentation for all warnings on the NVENT-VITA.
 * @{
 * @details
 *
 * \section warningsParent List of Warnings
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
 * @}
 */

/**
 * @ingroup warningsModule
 * @defgroup warningsManager Warnings Manager
 * @brief Documentation for managing all warnings on the Display Controller.
 * @{
 * @details
 *
 * \section warningsManager Warning Manager
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
 * For when Limited O<sub>2</sub> Mode is active, the warning manager sends the states representing colors to QML components (the Pneumatic Button and the Limited O<sub>2</sub> Switch) that are active alongside the Limited O<sub>2</sub> Warnings:
 * - State 0: Limted O<sub>2</sub> Safe is green.
 * - State 1: Limted O<sub>2</sub> Prepping or O<sub>2</sub> Calibration warnings are yellow.
 * - State 2: Neither
 *
 * Updates the state of the Service Due \htmlonly Notice \endhtmlonly due it being the only warning solely raised by the display controller due to maintenance date data stored in the display controller.
 *
 * @}
 */
