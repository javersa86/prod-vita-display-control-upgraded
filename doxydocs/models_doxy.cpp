//Modules for different models.

/**
 * @ingroup modelsModule
 * @defgroup opModeModels Op Mode IDs
 * @brief Documention for the model of all Op Modes.
 * @{
 * @details
 *
 * \section opModeModels Op Mode IDs
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
 * @}
 */

/**
 * @ingroup modelsModule
 * @defgroup hmiModels HMI Input IDs
 * @brief Documentation for the model of HMI Buttons.
 * @{
 * @details
 *
 * \section hmiModels HMI Input IDs
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
 * @}
 */

/**
 * @ingroup modelsModule
 * @defgroup settingsModels Pneumatic Settings Models
 * @brief Documentation for the model of Settings.
 * @{
 * @details
 *
 * \section settingsModels Pneumatic Settings Models
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
 * @}
 */

/**
 * @ingroup modelsModule
 * @defgroup notificationModels Notifications
 * @brief Documentation for the model of Notifications.
 * @{
 * @details
 *
 * \section notificationModels Notifications
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
 * @}
 */

/**
 * @ingroup modelsModule
 * @defgroup serviceNotificationModels Service Notifications
 * @brief Documentation for the model of Service Notifications.
 * @{
 * @details
 *
 * \section serviceNotificationModels Service Notifications
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
 *
 * @}
 */

/**
 * @ingroup modelsModule
 * @defgroup measuredModels Measured models
 * @brief Documentation for the model of Measurements.
 */

/**
 * @ingroup modelsModule
 * @defgroup subsystemsModels Subsystem Models
 * @brief Documentation for the model of Subsystems.
 */
