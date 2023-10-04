\mainpage Display Overview

This page is the main introduction page that will outline all major design paramters for the display controller. \n\n

\tableofcontents

# NVENT-VITA Display Controller Software

## Introduction

The NVENT-VITA Display Controller software is the graphical user interface application that allows the user to interact with NVENT VITA’s system features. The software is designed to manage and track the different pneumatic settings, measurements, modes, data, and other features available on the device. For the display controller software, it consists of frontend components, the backend controller, and the API Thread where the display controller communicates with the system controller. 

## Technologies Used

The display controller software is a Qt cross platform application that utilizes QML files for the frontend and C++ header and source code for the backend. The application utilizes multiple libraries from the following modules from Qt 5.12.3: 
* Qt Core
* Qt Quick
* Qt Widgets
* Qt Charts
* Qt Tests

The project is built from the following components:
* <b>“CMakeList.txt” file:</b> used by the display controller’s CMake build system to define how the project should be built.
* <b>“main.cpp” file:</b> the entry point for running the application. The application utilizes the following libraries:
  - QApplication for the core application
  - QQmlApplicationEngine for pushing QML pages and contexts
  - QObject to connect data between classes
* <b>“qml.qrc” file:</b> the XML-based resource collection file used by Qt to bundle QML files and other assets.

## Directory Structure

The project is organized as followed:
* <b>/qml:</b> Contains all UI components built from QML.
* <b>/scripts:</b> Contains CMake and shell scripts required to run the QT Project and utilize all display GPIO components of the A62 board.
* <b>/src:</b> Contains all source files for executing the application.

## Modules

The NVENT-VITA is divided in the following modules:
- \subpage frontendModule "Frontend Module (GUI)": Handles multiple pages, and navigates through and utilizes all features of the system.
- \subpage backendModule "Backend Module (Backend Controller)": Handles all the data management of the NVENT-VITA.
- \subpage communicationModule "Communication Module (API Controller)": Handles all communication between the display controller and the system controller.

<!--- defines major modules -->

\page modules Modules

\tableofcontents

@defgroup frontendModule Frontend Module (GUI)
@brief Documentation for all QML files.

# NVENT VITA Frontend Module Documentation

## Introduction
The frontend software is the Graphical User Interface that the user will interact with to trigger and change events in the backend module. The GUI will be composed of multiple pages, objects, images, and styling tools.

## Technologies used
The frontend is built using QML, a markup language used in the Qt framework for designing the Graphical User Interface. It utilizes the following QT 5 libraries:
* QtQuick 2.12
* QtQuick.Controls 2.12
* QtQuick.Controls.impl 2.12
* QtQuick.Layouts 1.12
* QtQuick.Templates 2.12 as T
* QtGraphicalEffects 1.12
* QtQML 2.12
* Qt.labs.qmlmodels 1.0
* QtCharts 2.3

The font libraries are constructed from TrueType Font (.ttf) files and the Iconography is constructed from Scalable Vector Graphics (.svg).

JavaScript is also utilized on the pages and objects for different purposes. Most JavaScript functions are triggered from the onCompleted signal for the following purposes:
- To Navigate between different pages and popup windows through StackViews.
- Get and Set values and trigger events in the backend module through signals.
- Trigger minor frontend events like starting animations, timers, and color changes.

The <b>“qml.qrc” file</b> is also XML-based resource collection file used by Qt to bundle QML files and the other assets together.

## Directory Structure

The GUI pages are ordered as followed:
- <b>/qml:</b> Header directory for the Graphical User Interface.
- <b>/qml/CustomObjects:</b> Contains all objects that will be implemented onto the pages.
- <b>/qml/CustomObjects/ContactKeyboard:</b> Contains the objects used for the keyboard used for inputting contact information.
- <b>/qml/CustomObjects/Keyboard:</b> Contains the objects used for the keyboards for Preset Titles and Serial Numbers.
- <b>/qml/Pages:</b> Contains all the pages for the Graphical User Interface.
- <b>/qml/Pages/Humidity:</b> Contains the pages used for adjusting the humidity pneumatic settings.
- <b>/qml/Pages/Service:</b> Contains the pages used for the Service Menu.
- <b>/qml/Pages/Settings:</b> Contains the pages used for the Settings Menu.
- <b>/qml/Styles:</b> Contains all Style and Font Properties.
- <b>/qml/fonts:</b> Contains all Font Libraries.
- <b>/qml/iconography:</b> Contains all iconography.

## Additional Information

Information for the other components of the GUI is available in the following links:

- @ref pagesModule "Pages"
- @ref customObjectsModule "Custom Objects"
- @ref stylingModule "Styling"
- @ref iconographyModule "Iconography"

@defgroup backendModule Backend Module (Backend Controller)
@brief Documentation for backend functions and features.
@details 

# NVENT VITA Backend Module Documentation

## Introduction
The backend software is responsible for managing all tasks and settings available on the display controller. The backend consists of the backend controller, the state manager, the GPIO module, constant models, and multiple loggers and managers for other backend components. This documentation is intended for developers, FDA officials, and medical service technicians who will be working with software.

## Technologies Used
The backend is built using C++ classes, which consists of header files and source files. It utilizes the following QT 5 libraries: 
* QObject
* QVector
* QHostAddress
* QNetworkInterface
* QNetworkConfigurationManager
* QTimer
* QDirIterator
* QString
* QDebug

The backend also utilizes C++ standard library as well.

## Directory Structure

The backend code is organizaed as followed:
* <b>/src:</b> Header source directory for the backend controller that handles all tasks, and the state manager that manages the state of all settings.
* <b>/src/gpio:</b> Contains the logic for managing the microcontroller connected to the encoder knob.
* <b>/src/logger:</b> Contains the main log manager for writing service logs, the CSV Manager to write all CSV files for service logs, and other managers.
* <b>/src/models:</b> Defines the constant values and models for pneumatic settings, modes, measurements, subsystems, notifications, HMI Buttons, and other settings.
* <b>/src/warnings:</b> Defines the constant values related to warnings, the model structure for all warnings, and contains the management for all warnings running on the system.

## Functionality
The backend consists of the following components:
* Backend Controller: main application that handles tasks from the requests and responses from the API and QML inputs.
* State Manager: manages the state of pneumatic settings, modes, subsystems, measurements, and other settings.
* Warnings Manager: Manages the number of warnings that are running on the system.
* Models: Constants and Models for all files.
* Log Manager and other managers: the main log manager that writes service logs, and other managers on the display controller.
* GPIO Module: Manages the pins connected to the microcontroller that enables the display controller’s encoder knob.

## Backend Controller
The backend controller is where all activity occurs from the user inputs on the Graphical User Interface and the updates from the system controller. The following functions are triggered from the backend controller:
- Trigger a timer that will continue to send requests to the API via emitting QObject signals until responses are sent via QObject slots. The following requests are sent from the backend to the API:
  - <b>Get Settings Request:</b> Retrieve all pneumatic settings from the API on startup.
  - <b>Enable Notifications Request:</b> Enable the constant retrieval of notifications from the system on startup. Notification updates will be sent to the state manager and the warning manager.
  - <b>Get Op Modes Request:</b> Retrieve the state of all op modes enabled or disabled on the system on startup.
  - <b>Get Subsystem State Request:</b> Retrieve the state of all subsystems on the system on startup.
  - <b>Get System Version Request:</b> Retrieve the most recent version number of the system controller on startup. Also saves the most recent version of the display controller.
  - <b>Set Settings Request:</b> Updates the values for pneumatic settings requests updates to the system controller. 
    - One pneumatic setting can be changed, such as updating the rate from 30 BPM to 90 BPM.
    - All pneumatic settings can be changed, such as implementing a preset.
    - When Laser-Safe Oxygen Concentration is less than the current oxygen concentration, oxygen concentration is updated.
    - Humidity on the jet line and the auxiliary line is updated at once.
  - <b>Get Measured Request:</b> Retrieves measurements running on the system, such as for detecting water on the system, O<sub>2</sub> Calibration Voltages, or low and high O<sub>2</sub> Calibration values.
    - Utilized so that when calibration procedures are conducted, the system is sending the constant measurements for the following: Inlet Air, Inlet O<sub>2</sub>, Peak Inspiratory Pressure, Stacking Pressure, and the Driving Pressure Regulator.
  - <b>Enable Op Mode Request:</b> Enable or disable an Op Mode on the system. Multiple activities occur between updating op modes:
    - Screen Lock Mode and Screen Lock Touched Mode need to be enabled at once.
    - If the system is venting or manual mode is enabled, enabling ETCO<sub>2</sub> Mode is prevented.
    - If ETCO<sub>2</sub> Mode is enabled, enabling manual mode is prevented.
    - Emits signal to knob controller when enabling the Listening Knob Op Mode.
    - When enabling Laser-Safe Mode, and if the Oxygen Concentration is greater than Laser-Safe Oxygen Concentration, Oxygen Concentration is updated to match it. Also, when the minimum value for Oxygen Concentration is reached, the Laser-Safe Timer in the O<sub>2</sub> Calibration Manager will start.
    - When disabling Laser-Safe Mode, oxygen concentration sets back to its original value.
    - When enabling or disabling the O<sub>2</sub> Calibration Op Mode, the 1 minute timer stored in the O<sub>2</sub> Calibration Manager will start or stop.
    - When enabling service calibration mode, the following occur: 
      - The warning banner will not be displayed (even if warnings are running).
      - The current Driving Pressure Pneumatic Setting will be saved. 
      - Signal is emitted for the API service variable.
      - The Set DPR Cal Val Request is sent at its default state.
    - When disabling service calibration mode, the following occur:
      - The saved Driving Pressured Pneumatic Setting will be set again.
      - The warning banner will be displayed.
      - Signal is emitted for the API service variable.
    - When Disabling the Humidity Priming Reset Available Mode, the Humidity on the Jet Line and the Auxiliary Line is set to 0.
    - When Disabling Dehumidification, the Dehumidification Timer will stop.
  - <b>Shutdown Confirm Send Request:</b> Send request to the system to confirm that the device can shutdown completely, can cancel the shutdown procedure.
  - <b>Set DPR Cal Val Request:</b> Request to update the state of calibration for pressure regulators: 
    - Low DPR: requests constant measurements for DPR, and sets Driving Pressure to 0. Saves DPR value from system to DPR Calibration Manager.
    - High DPR: requests constant measurements for DPR, and sets Driving pressure to 45. Sets precise float values for Driving Pressure during calibration and saves DPR value from system to DPR Calibration Manager.
    - Air Regulator: sets Driving Pressure to 48.
    - O<sub>2</sub> Regulator: sets Driving Pressure to 48.
    - Default
  - <b>Enable Pressure Sensor Zero Request:</b> Requests calibration for the following sensors: Inlet Air, Inlet O<sub>2</sub>, PIP, and SP. Saves value to Zero Calibration Manager for Sensor values.
- For Modes Requested from the system, the following will occur:
  - When the system enables the O<sub>2</sub> Calibration Op Mode, the 1 minute timer stored in the O<sub>2</sub> Calibration Manager will start and O<sub>2</sub> Calibration values and voltages are requested.
  - When the system disables the O<sub>2</sub> Calibration Op Mode, the 1 minute timer stored in the O<sub>2</sub> Calibration Manager will stop.
  - When the system enables dehumidification, the Humidity on the Jet Line and the Auxiliary Line is set to 0.
- Detect the dev port for a USB drive, and find and create the directories to send service logs to.
- Eject dev port for USB drive.
- Update log manager for when the service menu is opened.
- Runs a 2 minute countdown timer for when the dehumidification progress page is up.
- Receives ventilation status updates from the system, which will be utilized for the state manager, the End-Tidal Button, and the part manager.
- Receiving the ids for which the HMI button is pushed, is especially useful for screen lock mode.
- When the system begins the shutdown procedure, the backend requests measurements for Water Sensors to determine if water is detected on Jet and Auxiliary Lines.

## State Manager

The State Manager stores and controls the following from the backend controller and the Graphical User Interface:
- The state for the Shutdown Procedure.
- The state for when the system is ventilating.
- The version numbers for the Display Controller and the System Controller.
- Flags for when the start up procedure is active and complete.
- The state of the following Op Modes:
  - Laser-Safe Mode
  - Manual Mode
  - PIP Monitoring Mode
  - Demo Mode
  - Screen Lock Mode
  - Double Jets Mode
  - EndTidal Procedure
  - Dehumidification Procedure
  - O2 Calibration Procedure
  - Alarm Sounding Mode
  - Humidity Priming Reset Available
  - Listening to Knob Mode
  - Sound Icon Mode (obsolete)
  - Service Calibration Mode
- State for when adjustments for humidity on the Jet Line and Auxiliary Line are separated.
- The state of successes for the following procedures:
  - Dehumidification
  - O<sub>2</sub> Calibration
  - End-Tidal
- State of the following subsystems:
  - Primary Ventilation
  - Secondary Ventilation
  - Auxiliary Flow
  - Oxygen Control
  - Primary Humidification
  - Secondary Humidification
  - Auxiliary Humidification
- The values for the following pneumatic settings:
  - Driving Pressure 
  - Rate
  - Inspiratory Time
  - Stacking Pressure
  - Oxygen Concentration
  - Peak Inspiratory Pressure
  - Auxiliary Flow
  - Humidity on the Jet Line
  - Humidity on the Auxiliary Line
- If a double jet is installed on the device, then the following pneumatic settings will have secondary values:
  - Driving Pressure
  - Rate
  - Inspiratory Time
  - Stacking Pressure
  - Humidity on the Second Jet Line
- The values for settings utilized for the End-Tidal Procedure:
  - ETCO2 Rate
  - ETCO2 Inspiratory Time
  - ETCO2 Number of Breaths
  - ETCO2 Driving Pressure
- The value for Laser-Safe Oxygen Concentration.
- The volume of the Display Controller Alarm.
- The saved value for Oxygen Concentration during Laser-Safe.
- The Calibration State for the Pressure Regulator Calibration.
- The Calibration Values for Sensor Calibration:
  - Inlet Air
  - Inlet O<sub>2</sub>
  - Peak Inspiratory Pressure
  - Stacking Pressure
- The Saved Driving Pressure before Pressure Regulator Calibration.
- The measured values for Notifications:
  - Stacking Pressure
  - Stacking Pressure on second Jet Line
  - Oxygen Concentration
  - Peak Inspiratory Pressure
  - Auxiliary Flow
  - Tidal Volume 
  - Tidal Volume on second Jet Line
  - Map
  - O<sub>2</sub> Calibration Voltage
  - Alarm Time
- The measurement values:
  - Driving Pressure
  - Driving Pressure on Second Line
  - Rate
  - Rate on Second Line
  - Inspiratory Time
  - Inspiratory Time on Second Line 
  - Stacking Pressure
  - Stacking Pressure on Second Line
  - Oxygen Concentration
  - Peak Inspiratory Pressure
  - Auxiliary Flow
  - Humidity on the Jet Line
  - Humidity on the Second Line
  - Humidity on the Auxiliary Line
  - The Heater Temperature
  - The Average Flow
  - The Average Flow on the Second Line
  - Water Sensor on the Jet Line
  - Water Sensor on the Second Line
  - Water Sensor on the Auxiliary Line
  - Tidal Volume
  - Tidal Volume on the Second Line
  - Map
  - Inlet Air Pressure
  - Inlet O<sub>2</sub> Pressure
  - PIP Zeroing Value
  - Stacking Pressure Zeroing Value
  - Stacking Pressure Zeroing Value on the Second Line
  - Inlet Air Zeroing Value
  - Inlet O<sub>2</sub> Zeroing Value
  - Lowest Bounded O<sub>2</sub> Calibration Value
  - Highest Bounded O<sub>2</sub> Calibration Value
  - Lowest O<sub>2</sub> Calibration Voltage
  - Highest O<sub>2</sub> Calibration Voltage
  - Realtime O<sub>2</sub> Calibration Voltage
  - Realtime Driving Pressure Regulator
- The Display Controller’s IP Address (retrieves and sets IP Address from local network).
- State of the Preset Implementation Progress.
- State of Warning Banner Displayed.
- State of when Presets are being created or edited.
- State of visibility for Stacking Pressure line on graph.
- State of functionality for End-Tidal Button.
- Total number of service logs stored on the device.
- The number of service logs that are being exported to USB Drive.

## Additional Information

Information for the other components of the Backend is available in the following links:

- @ref warningsModule "Warnings"
- @ref modelsModule "Models"
- @ref loggerModule "Log Manager and other Managers"
- @ref gpioModule "GPIO Module"

@defgroup communicationModule Communication Module (API Controller)
@brief Documentation for how the Display Controller and the System Controller communication between each other.
@details

## Introduction
The API software works separately from the backend and frontend module, for its single tasked requesting and responding to messages from the system controller. The Communication Module is composed of the main API Controller that runs on a looping thread, the Serial Port object, and other components to make commuication more structured.

## Technologies Used
The api, like the backend, is built using C++ classes, which consists of header files and source files. It utilizes the following QT  5 libraries:
* QObject
* QThread
* QString
* QVector
* QMutex
* QQueue
* QWaitCondition
* QDebug

The api also utilizes C++ standard libraries:
* stdio.h
* time.h
* unistd.h
* cstdint.h
* iostream.h
* iterator.h
* map.h
* queue.h
* unordered_set.h
* string.h
* cstring.h
* sstream.h
* fcntl.h
* errno.h
* termios.h
* libusb-1.0/libusb.h

Libusb is a C library that provides generic access to USB devices is utilized for devices object.
Link: <a href="https://libusb.info/">Libusb Documentation</a>

## Directory Structure
The api code is organized as followed:
* <b>/src/communication:</b> Header source directory for the api controller that handles all tasks, the serial port object that send input buffer messages to system, 
queue to send message objects storing input buffers, and the devices object to ensure that there is a usb connection between the display controller and the system controller.

## Functionality
The api consists of the following:
* <b>API Controller:</b> the main thread that runs on a repeating loop that reads and writes messages to the serial port object.
* <b>API Constants:</b> Objects that contain the Transmitted and Received Message ID and Message Lengths for the type of messages that will be sent.
* <b>Communication Object:</b> Reads and writes the messages created from buffer objects from a file descriptor.
* <b>Message Queue and Message:</b> Queue that will be utilized to sends a request or a response to the serial port for every loop.
* <b>Devices Object:</b> Checks to see if USB is connected between system and display controllers.

## API Controller

The API Controller is built and running from QThread that starts at the start of the application. 
The thread will begin by opening the serial port to the system controller through the serial port object with the following Port Name and Baud Rate:
- Port Name: "/dev/ttyUSB0"
- Baud Rate: 115200

If the serial object fails to open the serial port, then an attempt will be made to close port and exit the thread. If the port does open, 
then the appropriate configurations will be made. Afterwards, an infinite while loop will be triggered and will only be interrupted by request.
Each loop represents an API Cycle of at least 30 milliseconds.
Here is the following sequence for the while loop:
- Checks to see if System Controller is connected to the Display Controller via devices object.
- Reads and processes bytes from the MCU.
- Handles the different requests and responses from the system controller and sends signals to backend controller for updates.
- While the API Controller is handling messages from the system, it is also adding messages to a message queue from requests and responses from the backend controller via signals.
- After handling the different requests and responses and if the queue is not empty, the message queue will lock the mutex for the thread, pop up to 5 messages from the queue, and write those messages to the serial object. The thread and other running threads will wake up again.
- The thread will sleep for at least 25 milliseconds.

## Serial Port Communication (Comm Object)

The Comm Object is the UART Serial Port between the Display Controller and the System Controller. The specified port from the Port Name and Baud Rate opens and reads the file descriptor to read and write bytes.
After reading the existing settings and handling errors, it constructs the tty settings structure to raise the following port settings:
- Clears parity bit, disabling parity (most common)
- Clears stop field, only one stop bit used in communication (most common)
- Clear all bits that set the data size
- 8 bits per byte (most common)
- Disable RTS/CTS hardware flow control (most common)
- Turn on READ & ignore ctrl lines (CLOCAL = 1)
- Disable echo
- Disable erasure
- Disable new-line echo
- Disable interpretation of INTR, QUI and SUSP
- Turn off s/w flow ctrl
- Disable any special handling of received bytes
- Prevent special interpretation of output bytes (e.g. newline chars)
- Prevent conversion of newline  to carriage return/line feed
- Wait for up to 1s (10 deciseconds), returning as soon as any data is received.

When the API Cycle reads from the Serial Port, The Comm Objects reads to file descriptor and stores the available bytes to an array buffer of at most 512 bytes.
The API Cycle will then process the array buffer by reading the array by index until bytes are no longer available. A message from the array is structured as followed:
- <b>Start Charactor (255):</b> the beginning byte for all requests and responses.
- <b>Op Code:</b> The Byte to represent the type of request or response.
- <b>Body:</b> the number bytes representing the parameters for message if available. The body will also have different lengths.
- <b>CRC:</b> Byte to represent the ending of the message.

Messages written to the file descriptor's are stored on an array buffer as well and are structured the same way.

## Message Object and Message Queue

The queue is built from a QQueue object.

Definitions:
- <b>Queue:</b> A data structure that follows the First-In-First-Out (FIFO) Principle, where the element added first will be the first to be removed. 
  Elements are added to the "tail" of the queue, and removed from the "head" of the queue.
- <b>Enqueue:</b> The operation of adding (pushing) an element to the rear end of a queue.
- <b>Dequeue:</b> The operation of removing (popping) an element from the front end of a queue.

A Message object for sending requests and responses to the system controller contains the following parameters:
- <b>The Input Buffer Array:</b> The array at the size of 512 bytes that store the bytes representing the request or response to the serial port.
- <b>The CRC Byte:</b> The character representing the end of the message, and is a unique character used to represent the message.
- <b>TX Size:</b> The size of the message within the array buffer.

While the backend and the rest of the application are enqueuing messages to the queue, up to 5 messages will be dequeued from the queue at the end of the API cycle.
To ensure that no repeated messages are pushed to the queue before being sent to the system controller, the queue also tracks the unique crc bytes to an unordered set
and checks if a new message contains an exisitng CRC byte before being pushed to the queue.

## API Requests and Responses

There are multiple requests and responses that need to be sent between the display controller and system controller. Each request and response will include a start character and a crc, both representing 2 bytes.
- Power On Send Request and Power On Receive Response
  - The System Controller sends a request to confirm with a response that the Display Controller is powered on alongside the System controller.
  - Power On Received Response:
    - Op Code: 0
    - Length: 3
  - Power On Send Request:
    - Op Code: 100
    - Length: 3
- Get Settings Request and Response
  - On startup, the Display Controller's Backend Controller will send a request for all pneumatic settings stored on the system and will receive a response with setting values.
  - Get Settings Request: 
    - Op Code: 1
    - Length: 3
  - Get Settings Response:
    - Op Code: 101
    - All 20 Pneumatic Settings, with settings stored as 4 bytes (4 * 20 = 80)
    - Length: 83
    - Note: Bytes representing settings are converted to float values.
- Enable Notification Request and Response
  - On startup, the Display Controller's Backend Controller will send a request to receive notifications from the system and will receive a response to confirm it.
  - Enable Notification Request:
    - Op Code: 2
    - Enable or Disable State
    - Length: 4
  - Enable Notification Response:
    - Op Code: 102
    - Length: 3
- Get Op Modes Request and Response
  - On startup, the Display Controller's Backend Controller will send a request for all modes enabled and disabled on the system and will receive a response with mode states.
  - Get Op Modes Request:
    - Op Code: 3
    - Length: 3
  - Get Op Modes Response:
    - Op Code: 103
    - All 15 Op Mode States
    - Length: 18
- Get Subsystem States Request and Response
  - On startup, the Display Controller's Backend Controller will send a request for all subsystems active on the system and will receive a response with subsystem status.
  - Get Subsystem States Request:
    - Op Code: 4
    - Length: 3
  - Get Subsystem States Response:
    - Op Code: 104
    - All 7 Subsystem States
    - Length: 10
- Get System Version Request and Response
  - On startup, the Display Controller's Backend Controller will send a request for the system controller's version number and will receive a response with version number.
  - Get System Version Request:
    - Op Code: 5
    - Length: 3
  - Get System Version Response:
    - Op Code: 105
    - Major Version Part of the Version Number
    - Minor Version Part of the Version Number
    - Patch Part of the Version Number
    - Length: 6
- Set Settings Request and Response
 - The Display's Backend will send a request to update the pneumatic settings to the system and will receive a response to confirm that the update succeeded.
 - Set Settings Request:
   - Op Code: 6
   - All 20 Pneumatic Settings, with each setting stored as 4 bytes (4 * 20 = 80)
   - Length: 83
 - Set Settings Response:
   - Op Code: 106
   - Length: 3
- Get Measured Request and Response
  - The Display's Backend will request a measurement running on the system and will receive a response with the measured value.
  - Get Measured Request:
    - Op Code: 7
    - Requested Measurement ID
    - Length: 4
  - Get Measured Response:
    - Op Code: 107
    - Requested Measurement ID
    - Measurement Float Value represented as 4 Bytes
    - Length: 8
- Clear Warning Request and Response
  - The Display's Backend will send a request to clear a warning running on the system and will receive a response with the warning id to clear the warning from the warning banner.
  - Clear Warning Request:
    - Op Code: 8
    - Requested Warning ID
    - Length: 4
  - Clear Warning Response:
    - Op Code: 108
    - Length: 3
- Enable Op Mode Display Request and System Response
  - The Display's Backend will send a request to enable or disable an op mode and will receive a response confirming that mode was enabled or disabled.
  - Enable Op Mode Display Request:
    - Op Code: 9
    - Requested Op Mode ID
    - Enable or Disable State
    - Success State
    - Length: 6
  - Enable Op Mode System Response:
    - Op Code: 109
    - Requested Op Mode ID
    - Enable or Disable State
    - Length 5
- Enable Op Mode System Request and Display Response
  - The System will send a message that mode was enabled or disabled and the display will send a response to confirm that message was received.
  - Enable Op Mode Display Response:
    - Op Code: 10
    - Requested Op Mode ID
    - Enable or Disable State
    - Length 5
  - Enable Op Mode System Request:
    - Op Code: 110
    - Requested Op Mode ID
    - Enable or Disable State
    - Success State
    - Length: 6 
- Notifications Received
  - The System will send the constant measurments for Stacking Pressure, Oxygen, Peak Inspiratory Pressure, Auxiliary Flow, Tidal Volume, Mean Average Pressure, O<sub>2</sub> Calibration Voltage, states of all warnings, and Alarm Silence Time.
  - Notification Received Request:
    - Op Code: 111
    - All 9 measurements, with each measurement stored as 4 bytes (4 * 9 = 36 Bytes)
    - 9 Bytes of warnings states, where each bit represents all 68 warning states
    - The Silence Button Time that would be displayed on the Silence Button
    - Length: 49
- Subsystem Status Received and Updated
  - The System sends changed states for subsystem states, and Display confirms received subsystem state change and saves new subsystem states.
  - Subsystem Status Received:
    - Op Code: 12
    - Length: 3
  - Subsystem Status Update:
    - Op Code: 112
    - All 7 Subsystem States
    - Length: 10
- Ventilation Status Received and Updated
  - The System sends the state of ventilation, and the Display confirms and saves the received ventilation state.
  - Ventilation Status Received:
    - Op Code: 13
    - Length: 3
  - Ventilation Status Update:
    - Op Code: 113
    - Ventilation State
    - Length: 4
- HMI Button Pushed Received and Update
  - The System sends which HMI Button was pressed and the Display confirms which HMI Button was pushed.
  - HMI Button Pushed Received
    - Op Code: 14
    - HMI Button ID
    - Length: 4
  - HMI Button Pushed Update:
    - Op Code: 114
    - HMI Button ID
    - Length: 4
- Shutdown Received and Request
  - The System sends request (triggered from user input of power button) to initiate the shutdown procedure, and the display confirms and will begin procedure.
  - Shutdown Received
    - Op Code: 15
    - Length: 3
  - Shutdown Request
    - Op Code: 115
    - Length: 3
- Shutdown Confirm or Cancel Request and Shutdown Confirm Receceived
  - The Display sends a request to confirm or cancel the shutdown, and the system responses back.
  - Shutdown Confirm or Cancel Request
    - Op Code: 16
    - Confirm or Cancel State
    - Length: 4
  - Shutdown Confirm Received
    - Op Code: 116
    - Confirm or Cancel State
    - Length: 4
- Set DPR Calibration Value Request and Response
  - The Display sends a request for the state of pressure regulator calibration, and system sends a response that calibration state is active.
  - Set DPR Calibration Value Request:
    - Op Code: 18
    - Pressure Regulator Calibration State
    - Length: 4
  - Set DPR Calibration Value Response:
    - Op Code: 118
    - Length: 3
- Enable Pressure Sensor Zero Request and Response
  - The Display sends a request for sensor calibration, and system sends a response that completes the calibration completely.
  - Enable Pressure Sensor Zero Request:
    - Op Code: 20
    - Sensor Calibration ID 
    - Length: 4
  - Enable Pressure Sensor Zero Response:
    - Op Code: 220
    - Success or Failure Value
    - Length: 4
    
## Devices Object

The device object tracks the connection between the system controller and display controller by tracking the number of devices mounted to the display controller via USB. On an API Cycle, if the system controller is disconnected, then the display will no longer receive notifications or other requests and responses, and the warning manager will raise "Display and System Disconnected!" itself. It is important to note that if the system controller is disconnected, there should only be 2 USB devices mounted, the Linux Foundation 2.0 root hub and Standard Microsystems Corp. USB 2.0 Hub. It is also important to note that when the system controller does get disconnected, the Portname will flip between "ttyUSB0" and "ttyUSB1". Because of this, and when the System Controller and the Display Controller is reconnected via USB and the devices object to 3 mounted devices, the serial port will be reopened and reconfigured.
