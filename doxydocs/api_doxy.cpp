/**
 * @ingroup communicationModule
 * @defgroup serialModule Serial Port Communication (Comm Object)
 * @brief Documentation for Serial Port for the display and system controllers.
 * @{
 * @details
 *
 * \section serialModule Serial Port Communication (Comm Object)
 *
 * The <b>\htmlonly Comm \endhtmlonly Object</b> is the UART Serial Port between the Display Controller and the System Controller. The specified port from the Port Name and Baud \htmlonly Rate \endhtmlonly opens and reads the file descriptor to read and write bytes. After reading the existing settings and handling errors, it constructs the tty settings structure to raise the following port settings:
 * - Clears parity bit, disabling parity (most common)
 * - Clears stop field, only one stop bit used in communication (most common)
 * - Clear all bits that set the data size
 * - 8 bits per byte (most common)
 * - Disable RTS/CTS hardware flow control (most common)
 * - Turn on READ & ignore ctrl lines (CLOCAL = 1)
 * - Disable echo
 * - Disable erasure
 * - Disable new-line echo
 * - Disable interpretation of INTR, QUI and SUSP
 * - Turn off s/w flow ctrl
 * - Disable any special handling of received bytes
 * - Prevent special interpretation of output bytes (e.g. newline chars)
 * - Prevent conversion of newline  to carriage return/line feed
 * - Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
 *
 * When the API Cycle reads from the Serial Port, The Comm Objects reads to the file descriptor and stores the available bytes to an array buffer of at most 512 bytes. The API Cycle will then process the array buffer by reading the array by index until bytes are no longer available. A message from the array is structured as followed:
 * - <b>Start Charactor (255):</b> the beginning byte for all requests and responses.
 * - <b>Op Code:</b> The Byte to represent the type of request or response.
 * - <b>Body:</b> the number bytes representing the parameters for message if available. The body will also have different lengths.
 * - <b>CRC:</b> Byte to represent the ending of the message.
 *
 * Messages written to the file descriptor's are stored on an array buffer as well and are structured the same way.
 * @}
 */

/**
 * @ingroup communicationModule
 * @defgroup messageModule Message Object and Message Queue
 * @brief Documentation for \htmlonly Message \endhtmlonly component utilized for sending bytes to serial buffer and documentation for all messages that will be queued up to the serial buffer.
 * @{
 * @details
 *
 * \section messageModule Message Object and Message Queue
 *
 * A <b>\htmlonly Message \endhtmlonly object</b> for sending requests and responses to the system controller contains the following parameters:
 * - <b>The Input Buffer Array:</b> The array at the size of 512 bytes that store the bytes representing the request or response to the serial port. All input buffers will always include the following bytes:
 *   - The <b>Start Character,</b> the first byte of the message to indicate the beginning of the message, which will always be 255.
 *   - The <b>Op Code</b> that represents the message sent or received.
 * - <b>The CRC Byte:</b> The character representing the end of the message, and is a unique character used to represent the message.
 * - <b>TX Size:</b> The size or length of the message within the array buffer. The size will always include the Start Character, the Op Code
 *
 * The <b>\htmlonly Message \endhtmlonly Queue</b> is built from a QQueue object and stores all Message objects. While the backend and the rest of the application are enqueuing messages to the queue, up to 5 messages will be dequeued from the queue at the end of the \htmlonly API \endhtmlonly cycle. To ensure that no repeated messages are pushed to the queue before being sent to the system controller, the queue also tracks the unique crc bytes to an unordered set and checks if a new message contains an existing CRC byte before being pushed to the queue.
 * @}
 */

/**
 * @ingroup communicationModule
 * @defgroup apiModule API Requests and Responses
 * @brief Documentation for the main \htmlonly API \endhtmlonly Controller and for all \htmlonly API \endhtmlonly Contant values.
 * @{
 * @details
 *
 * \section apiModule API Requests and Responses
 *
 * There are multiple requests and responses that need to be sent between the display controller and system controller.
 *
 * ### API Message Exchanges
 *
 * <table>
 *     <tr>
 *         <th style="background-color: #202531; border-color: #202531"> Messages </th>
 *         <th style="background-color: #202531; border-color: #202531"> Description </th>
 *     </tr>
 *     <tr>
 *         <th> Power On </th>
 *         <td> The System Controller sends a request to confirm with a response that the Display Controller is powered on alongside the System controller. </td>
 *     </tr>
 *     <tr>
 *         <th> Get Settings </th>
 *         <td> On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all pneumatic settings stored on the system and will receive a response with setting values. </td>
 *     </tr>
 *     <tr>
 *         <th>Enable Notification</th>
 *         <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request to receive notifications from the system and will receive a response to confirm it.</td>
 *     </tr>
 *     <tr>
 *         <th>Get Op Modes</th>
 *         <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all modes enabled and disabled on the system and will receive a response with mode states.</td>
 *     </tr>
 *     <tr>
 *         <th>Get Subsystem States</th>
 *         <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all subsystems active on the system and will receive a response with subsystem status.</td>
 *     </tr>
 *     <tr>
 *         <th>Get System Version</th>
 *         <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for the system controller's version number and will receive a response with version number.</td>
 *     </tr>
 *     <tr>
 *         <th>Set Settings</th>
 *         <td>The Display's \htmlonly Backend \endhtmlonly will send a request to update the pneumatic settings to the system and will receive a response to confirm that the update succeeded.</td>
 *     </tr>
 *     <tr>
 *         <th>Get Measured</th>
 *         <td>The Display's \htmlonly Backend \endhtmlonly will request a measurement running on the system and will receive a response with the measured value.</td>
 *     </tr>
 *     <tr>
 *         <th>Clear \htmlonly Warning \endhtmlonly </th>
 *         <td>The Display's \htmlonly Backend \endhtmlonly will send a request to clear a warning running on the system and will receive a response with the warning id to clear the warning from the warning banner.</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Op Mode from Display to System</th>
 *         <td>The Display's \htmlonly Backend \endhtmlonly will send a request to enable or disable an op mode and will receive a response confirming that mode was enabled or disabled.</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Op Mode from System to Display</th>
 *         <td>The System will send a message that mode was enabled or disabled and the display will send a response to confirm that message was received.</td>
 *     </tr>
 *     <tr>
 *         <th>Notifications</th>
 *         <td>The System will send the constant measurments for Stacking Pressure, Oxygen, Peak Inspiratory Pressure, Auxiliary Flow, Tidal \htmlonly Volume\endhtmlonly, Mean Average Pressure, states of all warnings, and Alarm Silence Time. Display will send response message after every 10 updates.</td>
 *     </tr>
 *     <tr>
 *         <th>Subsystem Status</th>
 *         <td>The System sends changed states for subsystem states, and Display confirms received subsystem state change and saves new subsystem states.</td>
 *     </tr>
 *     <tr>
 *         <th>Ventilation Status</th>
 *         <td>The System sends the state of ventilation, and the Display confirms and saves the received ventilation state.</td>
 *     </tr>
 *     <tr>
 *         <th>HMI Button Pushed</th>
 *         <td>The System sends which HMI Button was pressed and the Display confirms which HMI Button was pushed.</td>
 *     </tr>
 *     <tr>
 *         <th>Shutdown</th>
 *         <td>The System sends request (triggered from user input of power button) to initiate the shutdown procedure, and the display confirms and will begin procedure.</td>
 *     </tr>
 *     <tr>
 *         <th>Shutdown Confirm or Cancel</th>
 *         <td>The Display sends a request to confirm or cancel the shutdown, and the system responses back.</td>
 *     </tr>
 *     <tr>
 *         <th>Set DPR Calibration Value</th>
 *         <td>The Display sends a request for the state of pressure regulator calibration, and system sends a response that calibration state is active.</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Pressure Sensor Zero</th>
 *         <td>The Display sends a request for sensor calibration, and system sends a response that completes the calibration completely.</td>
 *     </tr>
 *     <tr>
 *         <th>Service Notifications</th>
 *         <td>For when the Service Menu is accessed, the Service Calibration Op Mode will be enabled from the Display, and the System will send the constant measurments for SP Average Data, SP Instant Data, \htmlonly PIP \endhtmlonly Average Data, \htmlonly PIP \endhtmlonly Instant Data, and O<sub>2</sub> Calibration Voltage.</td>
 *     </tr>
 *     <tr>
 *         <th>Service Calibration</th>
 *         <td>The System sends a request to the display for calibration data for verification purposes. Data includes SP Zero Value, \htmlonly PIP \endhtmlonly Zero Value, lowest O<sub>2</sub> Calibration Voltage, highest O<sub>2</sub> Calibration Voltage, and other values.</td>
 *     </tr>
 * </table>

 * ### Display Messages

 * <table>
 *     <tr>
 *         <th style="background-color: #202531; border-color: #202531"> Display \htmlonly Message \endhtmlonly </th>
 *         <th style="background-color: #202531; border-color: #202531"> Display Op Code </th>
 *         <th style="background-color: #202531; border-color: #202531"> Display Bytes </th>
 *         <th style="background-color: #202531; border-color: #202531"> Display Length </th>
 *     </tr>
 *     <tr>
 *         <th> Power On Received </th>
 *         <td> 0 </td>
 *         <td></td>
 *         <td> 3 </td>
 *     </tr>
 *     <tr>
 *         <th>Get Settings Request</th>
 *         <td>1</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Notification Request</th>
 *         <td>2</td>
 *         <td>Enable or Disable State</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Get Op Modes Request</th>
 *         <td>3</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Get Subsystem States Request</th>
 *         <td>4</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Get System Version Request</th>
 *         <td>5</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Set Settings Request</th>
 *         <td>6</td>
 *         <td>All 20 Pneumatic Settings, with each setting stored as 4 bytes (4 * 20 = 80).</td>
 *         <td>83</td>
 *     </tr>
 *     <tr>
 *         <th>Get Measured Request</th>
 *         <td>7</td>
 *         <td>Requested Measurement ID</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Clear \htmlonly Warning \endhtmlonly Request</th>
 *         <td>8</td>
 *         <td>Requested \htmlonly Warning \endhtmlonly ID</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Op Mode Display Request</th>
 *         <td>9</td>
 *         <td>
 *         - Requested Op Mode ID
 *         - Enable or Disable State
 *         - Success State
 *         </td>
 *         <td>6</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Op Mode Display Response</th>
 *         <td>10</td>
 *         <td>
 *         - Requested Op Mode ID
 *         - Enable or Disable State
 *         </td>
 *         <td>5</td>
 *     </tr>
 *     <tr>
 *         <th>Notification Received Response</th>
 *         <td>11</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Subsystem Status Received</th>
 *         <td>12</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Ventilation Status Received</th>
 *         <td>13</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>HMI Button Pushed Received</th>
 *         <td>14</td>
 *         <td>HMI Button ID</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Shutdown Received</th>
 *         <td>15</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Shutdown Confirm or Cancel Request</th>
 *         <td>16</td>
 *         <td>Confirm or Cancel State</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Set DPR Calibration Value Request</th>
 *         <td>18</td>
 *         <td>Pressure Regulator Calibration State</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Pressure Sensor Zero Request</th>
 *         <td>20</td>
 *         <td>Sensor Calibration ID </td>
 *         <td>8</td>
 *     </tr>
 *     <tr>
 *         <th>Service Calibration Response</th>
 *         <td>22</td>
 *         <td>All 8 calibration values, with each calibration value stored as 4 bytes (4 * 8 = 32 Bytes).</td>
 *         <td>35</td>
 *     </tr>
 * </table>
 *
 * ### System Messages
 *
 * <table>
 *     <tr>
 *         <th style="background-color: #202531; border-color: #202531"> System \htmlonly Message \endhtmlonly </th>
 *         <th style="background-color: #202531; border-color: #202531"> System Op Code </th>
 *         <th style="background-color: #202531; border-color: #202531"> System Bytes </th>
 *         <th style="background-color: #202531; border-color: #202531"> System Length </th>
 *     </tr>
 *     <tr>
 *         <th> Power On Send </th>
 *         <td> 100 </td>
 *         <td></td>
 *         <td> 3 </td>
 *     </tr>
 *     <tr>
 *         <th>Get Settings Response</th>
 *         <td>101</td>
 *         <td>All 20 Pneumatic Settings, with settings stored as 4 bytes (4 * 20 = 80). Bytes representing settings are converted to float values.</td>
 *         <td>83</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Notification Response</th>
 *         <td>102</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Get Op Modes Response</th>
 *         <td>103</td>
 *         <td>All 15 Op Mode States</td>
 *         <td>18</td>
 *     </tr>
 *     <tr>
 *         <th>Get Subsystem States Response</th>
 *         <td>104</td>
 *         <td>All 7 Subsystem States</td>
 *         <td>10</td>
 *     </tr>
 *     <tr>
 *         <th>Get System Version Response</th>
 *         <td>105</td>
 *         <td>
 *         - Major Version Part of the Version Number
 *         - Minor Version Part of the Version Number
 *         - Patch Part of the Version Number
 *         </td>
 *         <td>6</td>
 *     </tr>
 *     <tr>
 *         <th>Set Settings Response</th>
 *         <td>106</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Get Measured Response</th>
 *         <td>107</td>
 *         <td>
 *         - Requested Measurement ID
 *         - Measurement Float Value represented as 4 Bytes
 *         </td>
 *         <td>8</td>
 *     </tr>
 *     <tr>
 *         <th>Clear \htmlonly Warning \endhtmlonly Response</th>
 *         <td>108</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Op Mode System Response</th>
 *         <td>109</td>
 *         <td>
 *         - Requested Op Mode ID
 *         - Enable or Disable State
 *         </td>
 *         <td>5</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Op Mode System Request</th>
 *         <td>110</td>
 *         <td>
 *         - Requested Op Mode ID
 *         - Enable or Disable State
 *         - Success State
 *         </td>
 *         <td>6</td>
 *     </tr>
 *     <tr>
 *         <th>Notification Received</th>
 *         <td>111</td>
 *         <td>
 *         - All 8 measurements, with each measurement stored as 4 bytes (4 * 8 = 32 Bytes)
 *         - 9 Bytes of warnings states, where each bit represents all 70 warning states
 *         - The Silence Button Time that would be displayed on the Silence Button
 *         </td>
 *         <td>45</td>
 *     </tr>
 *     <tr>
 *         <th>Subsystem Status Update</th>
 *         <td>112</td>
 *         <td>All 7 Subsystem States</td>
 *         <td>10</td>
 *     </tr>
 *     <tr>
 *         <th>Ventilation Status Update</th>
 *         <td>113</td>
 *         <td>Ventilation State</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>HMI Button Pushed Update</th>
 *         <td>114</td>
 *         <td>HMI Button ID</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Shutdown Request</th>
 *         <td>115</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Shutdown Confirm Received</th>
 *         <td>116</td>
 *         <td>Confirm or Cancel State</td>
 *         <td>4</td>
 *     </tr>
 *     <tr>
 *         <th>Set DPR Calibration Value Response</th>
 *         <td>118</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 *     <tr>
 *         <th>Enable Pressure Sensor Zero Response</th>
 *         <td>120</td>
 *         <td>Success or Failure Value</td>
 *         <td>5</td>
 *     </tr>
 *     <tr>
 *         <th>Service Notification Received Response</th>
 *         <td>121</td>
 *         <td>All 5 measurements, with each measurement stored as 4 bytes (4 * 5 = 20 Bytes).</td>
 *         <td>23</td>
 *     </tr>
 *     <tr>
 *         <th>Service Calibration Request</th>
 *         <td>122</td>
 *         <td></td>
 *         <td>3</td>
 *     </tr>
 * </table>
 * @}
 */

/**
 * @ingroup communicationModule
 * @defgroup devicesModule Devices Object
 * @brief Documentation for tracking mounted devices to the display controller.
 * @{
 * @details
 *
 * \section devicesModule Devices Object
 *
 * The device object tracks the connection between the system controller and display controller by tracking the number of devices mounted to the display controller via USB. On an API Cycle, if the system controller is disconnected, then the display will no longer receive notifications or other requests and responses, and the warning manager will raise "Display and System Disconnected!" itself. It is important to note that if the system controller is disconnected, there should only be 2 USB devices mounted, the Linux Foundation 2.0 root hub and Standard Microsystems Corp. USB 2.0 Hub. It is also important to note that when the system controller does get disconnected, the Portname will flip between "ttyUSB0" and "ttyUSB1". Because of this, and when the System Controller and the Display Controller is reconnected via USB and the devices object to 3 mounted devices, the serial port will be reopened and reconfigured.
 *
 * @}
 */
