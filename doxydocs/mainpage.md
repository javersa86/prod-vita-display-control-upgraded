\mainpage Display Overview
\tableofcontents

This page is the main introduction page that will outline all major design parameters for the display controller. \n\n

This manual is divided in the following sections:
* \subpage introduction
* \subpage mainThread
* \subpage modules

\page introduction Introduction
\tableofcontents

## Display Background

The NVENT-VITA Display Controller software is the graphical user interface application that allows the user to interact with NVENT VITA’s system features. The software is designed to manage and track the different pneumatic settings, measurements, modes, data, and other features available on the device. For the display controller software, it consists of frontend components, the backend controller, and the \htmlonly API \endhtmlonly Thread where the display controller communicates with the system controller. 

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
* <b>/scripts:</b> Contains CMake and shell scripts required to run the QT Project and utilize all display \htmlonly GPIO \endhtmlonly components of the A62 board.
* <b>/src:</b> Contains all source files for executing the application.

## Thread Overview

The following contains the threads running on the application:
- \ref thread1 "API Thread"
- \ref thread2 "Encoder Knob Thread"

## Modules

The NVENT-VITA is divided in the following modules:
- \subpage frontendModule "Frontend Module (GUI)": Handles multiple pages, and navigates through and utilizes all features of the system.
- \subpage backendModule "Backend Module (Backend Controller)": Handles all the data management of the NVENT-VITA.
- \subpage communicationModule "Communication Module (API Controller)": Handles all communication between the display controller and the system controller.
- \subpage main "Main": Where is all begins.

<!--- defines main thread -->

\page mainThread Threading Architecture
\tableofcontents
This page gives detailed information on threading.

\section thread_list List of Threads

\subsection thread1 API Thread

#### Background

The user will power on the device and startup the display application. On Startup, and after the main functions declares the important variable and initiate the different managers and controllers, the API Controller will start the main thread.

#### Sequence of Events

The \htmlonly API \endhtmlonly Controller is built and running from QThread that starts at the start of the application. Each loop represents an \htmlonly API \endhtmlonly Cycle of at least 30 milliseconds.

1. Open the Serial Port connected to the system controller through the serial port object with the following Port Name and Baud \htmlonly Rate\endhtmlonly:
    - Serial Port Parameters:
      - Port Name: "/dev/ttyUSB0"
      - Baud \htmlonly Rate\endhtmlonly: 115200
    - If the serial object fails to open the serial port, then an attempt will be made to close the port and exit the thread.
    - If the port does open, then the appropriate configurations will be made. 
2. Afterwards, an infinite while loop will be triggered and will only be interrupted by request. 
3. Checks to see if System Controller is connected to the Display Controller via devices object.
4. Reads and processes bytes from the MCU.
5. Handles the different requests and responses from the system controller and sends signals to backend controller for updates.
6. While the \htmlonly API \endhtmlonly Controller is handling messages from the system, it is also adding messages to a message queue from requests and responses from the backend controller via signals.
7. After handling the different requests and responses and if the queue is not empty, the message queue will lock the mutex for the thread, pop up to 5 messages from the queue, and write those messages to the serial object. The thread and other running threads will wake up again.
8. The thread will sleep for at least 25 milliseconds.

#### Module References

- \ref communicationModule "Communication Module"

\subsection thread2 Encoder Knob Thread

#### Background

Activities available on the NVENT-VIta include adjusting pneumatic settings in the system. For when adjustment pages are displayed, the Op Mode "Listening Knob" will be enabled (usually when backend emits signal to the knob controller).

#### Sequence of Events

For when the op mode is enabled, the QThread for the knob controller will restart with following sequence:

1. Open the file descriptors for \htmlonly GPIO \endhtmlonly objects representing Pin A, Pin B, and the \htmlonly Switch \endhtmlonly Pin.
2. Sets the state of the switch of the button object with \htmlonly GPIO \endhtmlonly object switch, and the states of the encoder object with the Pin A and B \htmlonly GPIO \endhtmlonly objects.
3. The while loop will then trigger and while only be disabled when Op Mode is disabled.
4. Constructs the pollfd "fdset", the data structure that tracks the file descriptors for each \htmlonly GPIO \endhtmlonly object and sets each event notification to POLLPRI.
   - POLLPRI: to read urgent data
5. Poll the memory of the fdset for the number of events that changed.
6. If the file descriptor for Pin A is updated, the state representing Pin A on the encoder object changes.
7. If the file descriptor for Pin B is updated, the state representing Pin B on the encoder object changes.
8. If the file descriptor for \htmlonly Switch \endhtmlonly Pin is updated, the state of the Button object changes.
   - Thread will sleep for 75.
9. At the ending, flushes out the standard output.

#### Module References

- \ref gpioModule "Knob Controller and other GPIO Components"
- \ref pneumaticSettingPagesModule "Pneumatic Settings Adjustment Pages"

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
The backend software is responsible for managing all tasks and settings available on the display controller. The backend consists of the backend controller, the state manager, the \htmlonly GPIO \endhtmlonly module, constant models, and multiple loggers and managers for other backend components. This documentation is intended for developers, FDA officials, and medical service technicians who will be working with software.

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
* \htmlonly Backend \endhtmlonly Controller: main application that handles tasks from the requests and responses from the \htmlonly API \endhtmlonly and QML inputs.
* State Manager: manages the state of pneumatic settings, modes, subsystems, measurements, and other settings.
* Warnings Manager: Manages the number of warnings that are running on the system.
* Models: Constants and Models for all files.
* Log Manager and other managers: the main log manager that writes service logs, and other managers on the display controller.
* \htmlonly GPIO \endhtmlonly Module: Manages the pins connected to the microcontroller that enables the display controller’s encoder knob.

## Backend Controller
The backend controller is where all activity occurs from the user inputs on the Graphical User Interface and the updates from the system controller.
The following functions are triggered from the backend controller:

### Request Functions

Requests functions construct Op Code Requests that are sent to the system controller through the \htmlonly API \endhtmlonly Thread. The process of sending messages to the \htmlonly API \endhtmlonly go as followed: 
1. Requests are contructed through different datetypes like unsigned characters, ints, and QVectors.
2. The requests are sent to the \htmlonly API \endhtmlonly thread via emitted QObject signals. 
3. After the first signal is sent, the associated unsigned char variable called a flag will be set to true (raised). 
4. While a flag is raised, the associated signal will continue to be emitted with the contructed request. 
5. The flag will be set to false (lowered) when the \htmlonly API \endhtmlonly thread emits their response signal and trigger the \htmlonly Backend \endhtmlonly QObject response slot. 

The following requests are sent from the backend to the \htmlonly API \endhtmlonly:

  - <b>Get Settings Request:</b> Retrieve all pneumatic settings from the \htmlonly API \endhtmlonly on startup.
    - If \htmlonly Humdity \endhtmlonly levels do not equal each other, Separate Humdities Mode will be set.
    - The \htmlonly Humidity \endhtmlonly Percentages will be converted to the following levels:
      - 100% to level 4
      - 70% to level 3
      - 50% to level 2
      - 30% to level 1
      - 0% to level 0
      
  - <b>Enable Notifications Request:</b> Enable the constant retrieval of notifications from the system on startup. Notification updates will be sent to the state manager and the warning manager.
  
  - <b>Get Op Modes Request:</b> Retrieve the state of all op modes enabled or disabled on the system on startup.
  
  - <b>Get Subsystem State Request:</b> Retrieve the state of all subsystems on the system on startup.
  
  - <b>Get System Version Request:</b> Retrieve the most recent version number of the system controller on startup. Also saves the most recent version of the display controller.
  
  - <b>Set Settings Request:</b> Updates the values for pneumatic settings requests updates to the system controller. 
    - One pneumatic setting can be changed, such as updating the rate from 30 BPM to 90 BPM.
    - All pneumatic settings can be changed, such as implementing a preset.
    - When Limited O<sub>2</sub> Oxygen Concentration is less than the current oxygen concentration, oxygen concentration is updated.
    - \htmlonly Humidity \endhtmlonly on the jet line and the auxiliary line is updated at once.
    - When updating \htmlonly Humidity\endhtmlonly, levels will be converted to the following percentages:
      - level 4 to 100%
      - level 3 to 70%
      - level 2 to 50%
      - level 1 to 30%
      - level 0 to 0%
      
  - <b>Get Measured Request:</b> Retrieves measurements running on the system, such as for detecting water on the system, O<sub>2</sub> Calibration Voltages, or low and high O<sub>2</sub> Calibration values.
    
  - <b>Clear \htmlonly Warning \endhtmlonly Request:</b> Clears warning running on the system by ID.
  
  - <b>Enable Op Mode Request:</b> Enable or disable an Op Mode on the system. Based on which Op Mode is enabled or disabled, different activities in the \htmlonly Backend \endhtmlonly occur:
    - 
    <table>
        <tr>
            <th>Op Mode</th>
            <th>Enabled</th>
            <th>Disabled</th>
        </tr>
        <tr>
            <td>Manual Mode</td>
            <td>
            - The SP Line is hidden on the QML graph.
            </td>
            <td>
            - The SP Line returns to its original state.
            </td>
        </tr>
        <tr>
            <td>Listening \htmlonly Knob \endhtmlonly Op Mode</td>
            <td>
            - Emits signal to knob controller to be enabled.
            </td>
            <td>
            - Emits signal to knob controller to be disabled.
            </td>
        </tr>
        <tr>
            <td>Limited O<sub>2</sub> Mode</td>
            <td>
            - If the Oxygen Concentration is greater than Limited O<sub>2</sub> Oxygen Concentration, Oxygen Concentration is updated to match it.
            - The states for mode reset in the state manager.
            </td>
            <td>
            - Oxygen Concentration is set back to its original value.
            - The states for mode reset in the state manager.
            </td>
        </tr>
        <tr>
            <td>O<sub>2</sub> Calibration Mode</td>
            <td>
            - The 1 minute timer stored in the O<sub>2</sub> Calibration Manager will start.
            </td>
            <td>
            - The 1 minute timer stored in the O<sub>2</sub> Calibration Manager will stop.
            </td>
        </tr>
        <tr>
            <td>Service Calibration Mode</td>
            <td>
            - The warning banner will not be displayed (even if warnings are running).
            - The current Driving Pressure Pneumatic Setting will be saved. 
            - Signal is emitted for the \htmlonly API \endhtmlonly service variable.
            - The Set DPR Cal Val Request is sent at its default state.
            - Updates the warning manager to stop raising the No Communication warning.
            </td>
            <td>
            - The saved Driving Pressured Pneumatic Setting will be set again.
            - The warning banner will be displayed.
            - Signal is emitted for the \htmlonly API \endhtmlonly service variable.
            - Updates the warning manager to raise the No Communication warning again when there is no communication between system and display.
            </td>
        </tr>
        <tr>
            <td>\htmlonly Humidity \endhtmlonly Priming Reset Available Mode</td>
            <td></td>
            <td>
            - The \htmlonly Humidity \endhtmlonly on the Jet Line and the Auxiliary Line is set to 0.
            </td>
        </tr>
        <tr>
            <td>Dehumidification Mode</td>
            <td></td>
            <td>Dehumidification Timer will stop.</td>
        </tr>
    </table>
    - The following Op Modes Requested will not proceed if different criterias are met:
        - If ventilation is inactive or Manual Mode is enabled, enabling <b>ETCO<sub>2</sub> Mode</b> is prevented.
        - If ETCO<sub>2</sub> Mode is enabled, enabling <b>Manual Mode</b> is prevented.
    - The only Op Modes that will be enabled or disbaled together at the same time are <b>Screen Lock Mode</b> and <b>Screen Lock Touched Mode</b>.
    
  - <b>Shutdown Confirm Send Request:</b> Send request to the system to confirm that the device can shutdown completely, can cancel the shutdown procedure.
  
  - <b>Set DPR Cal Val Request:</b> Request to update the state of calibration for pressure regulators. Depending on which state is active, different activities in the \htmlonly Backend \endhtmlonly will occur:
    -    <table>
            <tr>
                <th>Pressure Regulator State</th>
                <th>Activities</th>
            </tr>
            <tr>
                <td>Low DPR</td>
                <td>Requests constant measurements for DPR, and sets Driving Pressure to 0. Saves DPR value from system to DPR Calibration Manager.</td>
            </tr>
            <tr>
                <td>High DPR</td>
                <td>Requests constant measurements for DPR, and sets Driving pressure to 45. Sets precise float values for Driving Pressure during calibration and saves DPR value from system to DPR Calibration Manager.</td>
            </tr>
            <tr>
                <td>Air Regulator</td>
                <td>Sets Driving Pressure to 48.</td>
            </tr>
            <tr>
                <td>O<sub>2</sub> Regulator</td>
                <td>Sets Driving Pressure to 48.</td>
            </tr>
            <tr>
                <td>Default</td>
                <td></td>
            </tr>
        </table>

    
  - <b>Enable Pressure Sensor Zero Request:</b> Requests calibration verification for the following sensors: Inlet Air, Inlet O<sub>2</sub>, \htmlonly PIP\endhtmlonly, and SP. Saves value to Zero Calibration Manager for Sensor values.
  
### Backend Functions
- For Modes Requested from the system, the following will occur:
  - When the system enables the O<sub>2</sub> Calibration Op Mode, the 1 minute timer stored in the O<sub>2</sub> Calibration Manager will start and O<sub>2</sub> Calibration values and voltages are requested.
  - When the system disables the O<sub>2</sub> Calibration Op Mode, the 1 minute timer stored in the O<sub>2</sub> Calibration Manager will stop.
  - When the system enables dehumidification, the \htmlonly Humidity \endhtmlonly on the Jet Line and the Auxiliary Line is set to 0.
- Detect the dev port for a USB drive, and find and create the directories to send service logs to.
- Eject dev port for USB drive.
- Update log manager for when the service menu is opened.
- Runs a 2 minute countdown timer for when the dehumidification progress page is up.
- Receives ventilation status updates from the system, which will be utilized for the state manager, the End-Tidal Button, and the part manager.
- Receiving the ids for which the HMI button is pushed, is especially useful for screen lock mode.
- When the system begins the shutdown procedure, the backend requests measurements for Water Sensors to determine if water is detected on Jet and Auxiliary Lines.
- Receive notifications and service notifications from the \htmlonly API \endhtmlonly.
- Sends service calibration data as a QVector back to the system via signal to \htmlonly API \endhtmlonly.

## State Manager

The State Manager stores and controls the following from the backend controller and the Graphical User Interface:
- The state for the Shutdown Procedure.
- The state for when the system is ventilating.
- The version numbers for the Display Controller and the System Controller.
- Flags for when the start up procedure is active and complete.
- The state of the following Op Modes:
  - Limited O<sub>2</sub> Mode
  - Manual Mode
  - \htmlonly PIP \endhtmlonly Monitoring Mode
  - Demo Mode
  - Screen Lock Mode
  - Double Jets Mode
  - End-Tidal Procedure
  - Dehumidification Procedure
  - O<sub>2</sub> Calibration Procedure
  - Alarm Sounding Mode
  - \htmlonly Humidity \endhtmlonly Priming Reset Available
  - Listening to \htmlonly Knob \endhtmlonly Mode
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
  - \htmlonly Rate \endhtmlonly
  - Inspiratory Time
  - Stacking Pressure
  - Oxygen Concentration
  - Peak Inspiratory Pressure
  - Auxiliary Flow
  - \htmlonly Humidity \endhtmlonly on the Jet Line
  - \htmlonly Humidity \endhtmlonly on the Auxiliary Line
- If a double jet is installed on the device, then the following pneumatic settings will have secondary values:
  - Driving Pressure
  - \htmlonly Rate \endhtmlonly
  - Inspiratory Time
  - Stacking Pressure
  - \htmlonly Humidity \endhtmlonly on the Second Jet Line
- The values for settings utilized for the End-Tidal Procedure:
  - ETCO<sub>2</sub> \htmlonly Rate \endhtmlonly
  - ETCO<sub>2</sub> Inspiratory Time
  - ETCO<sub>2</sub> Number of Breaths
  - ETCO<sub>2</sub> Driving Pressure
- The value for Limited O<sub>2</sub> Oxygen Concentration.
- The volume of the Display Controller Alarm.
- The saved value for Oxygen Concentration during Limited O<sub>2</sub>.
- The states of Limited O<sub>2</sub> for when the oxygen measurement on the notification vector reaches the minimum oxygen and set oxygen.
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
  - Tidal \htmlonly Volume \endhtmlonly
  - Tidal \htmlonly Volume \endhtmlonly on second Jet Line
  - Map
  - Alarm Time
- The state for when to display the spinner icon when oxygen is adjusting.
- The measurement values:
  - Driving Pressure
  - Driving Pressure on Second Line
  - \htmlonly Rate \endhtmlonly
  - \htmlonly Rate \endhtmlonly on Second Line
  - Inspiratory Time
  - Inspiratory Time on Second Line 
  - Stacking Pressure
  - Stacking Pressure on Second Line
  - Oxygen Concentration
  - Peak Inspiratory Pressure
  - Auxiliary Flow
  - \htmlonly Humidity \endhtmlonly on the Jet Line
  - \htmlonly Humidity \endhtmlonly on the Second Line
  - \htmlonly Humidity \endhtmlonly on the Auxiliary Line
  - The Heater Temperature
  - The Average Flow
  - The Average Flow on the Second Line
  - Water Sensor on the Jet Line
  - Water Sensor on the Second Line
  - Water Sensor on the Auxiliary Line
  - Tidal \htmlonly Volume \endhtmlonly
  - Tidal \htmlonly Volume \endhtmlonly on the Second Line
  - Map
  - Inlet Air Pressure
  - Inlet O<sub>2</sub> Pressure
  - \htmlonly PIP \endhtmlonly Zeroing Value
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
  - Stacking Pressure Average Data
  - Stacking Pressure Instantaneous Data
  - Peak Inspiratory Pressure Average Data
  - Peak Inspiratory Pressure Instantaneous Data
- The Display Controller’s IP Address (retrieves and sets IP Address from local network).
- State of the Preset Implementation Progress.
- State of \htmlonly Warning \endhtmlonly Banner Displayed.
- State of when Presets are being created or edited.
- State of visibility for Stacking Pressure line on graph.
- State of functionality for End-Tidal Button.
- Total number of service logs stored on the device.
- The number of service logs that are being exported to USB Drive.
- The measured values for Service Notifications:
  - Stacking Pressure Average Data
  - Stacking Pressure Instantaneous Data
  - Peak Inspiratory Pressure Average Data
  - Peak Inspiratory Pressure Instantaneous Data
  - O<sub>2</sub> Calibration Voltage Data

## Additional Information

Information for the other components of the \htmlonly Backend \endhtmlonly is available in the following links:

- @ref warningsModule "Warnings"
- @ref modelsModule "Models"
- @ref loggerModule "Log Manager and other Managers"
- @ref gpioModule "GPIO Module"

@defgroup communicationModule Communication Module (API Controller)
@brief Documentation for how the Display Controller and the System Controller communication between each other.
@details

## Introduction
The \htmlonly API \endhtmlonly software works separately from the backend and frontend module, for its single tasked requesting and responding to messages from the system controller. The Communication Module is composed of the main \htmlonly API \endhtmlonly Controller that runs on a looping thread, the Serial Port object, and other components to make commuication more structured.

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
* <b>\htmlonly API \endhtmlonly Controller:</b> the main thread that runs on a repeating loop that reads and writes messages to the serial port object. See @ref thread1 "API Thread"
* <b>\htmlonly API \endhtmlonly Constants:</b> Objects that contain the Transmitted and Received \htmlonly Message \endhtmlonly ID and \htmlonly Message \endhtmlonly Lengths for the type of messages that will be sent.
* <b>Communication Object:</b> Reads and writes the messages created from buffer objects from a file descriptor.
* <b>\htmlonly Message \endhtmlonly Queue and \htmlonly Message \endhtmlonly:</b> Queue that will be utilized to sends a request or a response to the serial port for every loop.
* <b>Devices Object:</b> Checks to see if USB is connected between system and display controllers.

## Serial Port Communication (Comm Object)

The \htmlonly Comm \endhtmlonly Object is the UART Serial Port between the Display Controller and the System Controller. The specified port from the Port Name and Baud \htmlonly Rate \endhtmlonly opens and reads the file descriptor to read and write bytes.
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

When the \htmlonly API \endhtmlonly Cycle reads from the Serial Port, The \htmlonly Comm \endhtmlonly Objects reads to file descriptor and stores the available bytes to an array buffer of at most 512 bytes.
The \htmlonly API \endhtmlonly Cycle will then process the array buffer by reading the array by index until bytes are no longer available. A message from the array is structured as followed:
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

A \htmlonly Message \endhtmlonly object for sending requests and responses to the system controller contains the following parameters:
- <b>The Input Buffer Array:</b> The array at the size of 512 bytes that store the bytes representing the request or response to the serial port.
- <b>The CRC Byte:</b> The character representing the end of the message, and is a unique character used to represent the message.
- <b>TX Size:</b> The size of the message within the array buffer.

While the backend and the rest of the application are enqueuing messages to the queue, up to 5 messages will be dequeued from the queue at the end of the \htmlonly API \endhtmlonly cycle.
To ensure that no repeated messages are pushed to the queue before being sent to the system controller, the queue also tracks the unique crc bytes to an unordered set
and checks if a new message contains an exisitng CRC byte before being pushed to the queue.

## API Requests and Responses

There are multiple requests and responses that need to be sent between the display controller and system controller. Each request and response will include a start character and a crc, both representing 2 bytes.

<table>
    <tr>
        <th style="background-color: #202531; border-color: #202531"> Messages </th>
        <th style="background-color: #202531; border-color: #202531"> Description </th>
        <th style="background-color: #202531; border-color: #202531"> Display \htmlonly Message \endhtmlonly </th>
        <th style="background-color: #202531; border-color: #202531"> Display Op Code </th>
        <th style="background-color: #202531; border-color: #202531"> Display Bytes </th>
        <th style="background-color: #202531; border-color: #202531"> Display Length </th>
        <th style="background-color: #202531; border-color: #202531"> System \htmlonly Message \endhtmlonly </th>
        <th style="background-color: #202531; border-color: #202531"> System Op Code </th>
        <th style="background-color: #202531; border-color: #202531"> System Bytes </th>
        <th style="background-color: #202531; border-color: #202531"> System Length </th>
    </tr>
    <tr>
        <th> Power On </th>
        <td> The System Controller sends a request to confirm with a response that the Display Controller is powered on alongside the System controller. </td>
        <th> Power On Received </th>
        <td> 0 </td>
        <td></td>
        <td> 3 </td>
        <th> Power On Send </th>
        <td> 100 </td>
        <td></td>
        <td> 3 </td>
    </tr>
    <tr>
        <th> Get Settings </th>
        <td> On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all pneumatic settings stored on the system and will receive a response with setting values. </td>
        <th>Get Settings Request</th>
        <td>1</td>
        <td></td>
        <td>3</td>
        <th>Get Settings Response</th>
        <td>101</td>
        <td>All 20 Pneumatic Settings, with settings stored as 4 bytes (4 * 20 = 80). Bytes representing settings are converted to float values.</td>
        <td>83</td>
    </tr>
    <tr>
        <th>Enable Notification</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request to receive notifications from the system and will receive a response to confirm it.</td>
        <th>Enable Notification Request</th>
        <td>2</td>
        <td>Enable or Disable State</td>
        <td>4</td>
        <th>Enable Notification Response</th>
        <td>102</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Get Op Modes</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all modes enabled and disabled on the system and will receive a response with mode states.</td>
        <th>Get Op Modes Request</th>
        <td>3</td>
        <td></td>
        <td>3</td>
        <th>Get Op Modes Response</th>
        <td>103</td>
        <td>All 15 Op Mode States</td>
        <td>18</td>
    </tr>
    <tr>
        <th>Get Subsystem States</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all subsystems active on the system and will receive a response with subsystem status.</td>
        <th>Get Subsystem States Request</th>
        <td>4</td>
        <td></td>
        <td>3</td>
        <th>Get Subsystem States Response</th>
        <td>104</td>
        <td>All 7 Subsystem States</td>
        <td>10</td>
    </tr>
    <tr>
        <th>Get System Version</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for the system controller's version number and will receive a response with version number.</td>
        <th>Get System Version Request</th>
        <td>5</td>
        <td></td>
        <td>3</td>
        <th>Get System Version Response</th>
        <td>105</td>
        <td>
        - Major Version Part of the Version Number
        - Minor Version Part of the Version Number
        - Patch Part of the Version Number
        </td>
        <td>6</td>
    </tr>
    <tr>
        <th>Set Settings</th>
        <td>The Display's \htmlonly Backend \endhtmlonly will send a request to update the pneumatic settings to the system and will receive a response to confirm that the update succeeded.</td>
        <th>Set Settings Request</th>
        <td>6</td>
        <td>All 20 Pneumatic Settings, with each setting stored as 4 bytes (4 * 20 = 80).</td>
        <td>83</td>
        <th>Set Settings Response</th>
        <td>106</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Get Measured</th>
        <td>The Display's \htmlonly Backend \endhtmlonly will request a measurement running on the system and will receive a response with the measured value.</td>
        <th>Get Measured Request</th>
        <td>7</td>
        <td>Requested Measurement ID</td>
        <td>4</td>
        <th>Get Measured Response</th>
        <td>107</td>
        <td>
        - Requested Measurement ID
        - Measurement Float Value represented as 4 Bytes
        </td>
        <td>8</td>
    </tr>
    <tr>
        <th>Clear \htmlonly Warning \endhtmlonly </th>
        <td>The Display's \htmlonly Backend \endhtmlonly will send a request to clear a warning running on the system and will receive a response with the warning id to clear the warning from the warning banner.</td>
        <th>Clear \htmlonly Warning \endhtmlonly Request</th>
        <td>8</td>
        <td>Requested \htmlonly Warning \endhtmlonly ID</td>
        <td>4</td>
        <th>Clear \htmlonly Warning \endhtmlonly Response</th>
        <td>108</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Enable Op Mode from Display to System</th>
        <td>The Display's \htmlonly Backend \endhtmlonly will send a request to enable or disable an op mode and will receive a response confirming that mode was enabled or disabled.</td>
        <th>Enable Op Mode Display Request</th>
        <td>9</td>
        <td>
        - Requested Op Mode ID
        - Enable or Disable State
        - Success State
        </td>
        <td>6</td>
        <th>Enable Op Mode System Response</th>
        <td>109</td>
        <td>
        - Requested Op Mode ID
        - Enable or Disable State
        </td>
        <td>5</td>
    </tr>
    <tr>
        <th>Enable Op Mode from System to Display</th>
        <td>The System will send a message that mode was enabled or disabled and the display will send a response to confirm that message was received.</td>
        <th>Enable Op Mode Display Response</th>
        <td>10</td>
        <td>
        - Requested Op Mode ID
        - Enable or Disable State
        </td>
        <td>5</td>
        <th>Enable Op Mode System Request</th>
        <td>110</td>
        <td>
        - Requested Op Mode ID
        - Enable or Disable State
        - Success State
        </td>
        <td>6</td>
    </tr>
    <tr>
        <th>Notifications</th>
        <td>The System will send the constant measurments for Stacking Pressure, Oxygen, Peak Inspiratory Pressure, Auxiliary Flow, Tidal \htmlonly Volume\endhtmlonly, Mean Average Pressure, states of all warnings, and Alarm Silence Time. Display will send response message after every 10 updates.</td>
        <th>Notification Received Response</th>
        <td>11</td>
        <td></td>
        <td>3</td>
        <th>Notification Received</th>
        <td>111</td>
        <td>
        - All 8 measurements, with each measurement stored as 4 bytes (4 * 8 = 32 Bytes)
        - 9 Bytes of warnings states, where each bit represents all 70 warning states
        - The Silence Button Time that would be displayed on the Silence Button
        </td>
        <td>45</td>
    </tr>
    <tr>
        <th>Subsystem Status</th>
        <td>The System sends changed states for subsystem states, and Display confirms received subsystem state change and saves new subsystem states.</td>
        <th>Subsystem Status Received</th>
        <td>12</td>
        <td></td>
        <td>3</td>
        <th>Subsystem Status Update</th>
        <td>112</td>
        <td>All 7 Subsystem States</td>
        <td>10</td>
    </tr>
    <tr>
        <th>Ventilation Status</th>
        <td>The System sends the state of ventilation, and the Display confirms and saves the received ventilation state.</td>
        <th>Ventilation Status Received</th>
        <td>13</td>
        <td></td>
        <td>3</td>
        <th>Ventilation Status Update</th>
        <td>113</td>
        <td>Ventilation State</td>
        <td>4</td>
    </tr>
    <tr>
        <th>HMI Button Pushed</th>
        <td>The System sends which HMI Button was pressed and the Display confirms which HMI Button was pushed.</td>
        <th>HMI Button Pushed Received</th>
        <td>14</td>
        <td>HMI Button ID</td>
        <td>4</td>
        <th>HMI Button Pushed Update</th>
        <td>114</td>
        <td>HMI Button ID</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Shutdown</th>
        <td>The System sends request (triggered from user input of power button) to initiate the shutdown procedure, and the display confirms and will begin procedure.</td>
        <th>Shutdown Received</th>
        <td>15</td>
        <td></td>
        <td>3</td>
        <th>Shutdown Request</th>
        <td>115</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Shutdown Confirm or Cancel</th>
        <td>The Display sends a request to confirm or cancel the shutdown, and the system responses back.</td>
        <th>Shutdown Confirm or Cancel Request</th>
        <td>16</td>
        <td>Confirm or Cancel State</td>
        <td>4</td>
        <th>Shutdown Confirm Received</th>
        <td>116</td>
        <td>Confirm or Cancel State</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Set DPR Calibration Value</th>
        <td>The Display sends a request for the state of pressure regulator calibration, and system sends a response that calibration state is active.</td>
        <th>Set DPR Calibration Value Request</th>
        <td>18</td>
        <td>Pressure Regulator Calibration State</td>
        <td>4</td>
        <th>Set DPR Calibration Value Response</th>
        <td>118</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Enable Pressure Sensor Zero</th>
        <td>The Display sends a request for sensor calibration, and system sends a response that completes the calibration completely.</td>
        <th>Enable Pressure Sensor Zero Request</th>
        <td>20</td>
        <td>Sensor Calibration ID </td>
        <td>8</td>
        <th>Enable Pressure Sensor Zero Response</th>
        <td>120</td>
        <td>Success or Failure Value</td>
        <td>5</td>
    </tr>
    <tr>
        <th>Service Notifications</th>
        <td>For when the Service Menu is accessed, the Service Calibration Op Mode will be enabled from the Display, and the System will send the constant measurments for SP Average Data, SP Instant Data, \htmlonly PIP \endhtmlonly Average Data, \htmlonly PIP \endhtmlonly Instant Data, and O<sub>2</sub> Calibration Voltage.</td>
        <th></th>
        <td></td>
        <td></td>
        <td></td>
        <th>Service Notification Received Response</th>
        <td>121</td>
        <td>All 5 measurements, with each measurement stored as 4 bytes (4 * 5 = 20 Bytes).</td>
        <td>23</td>
    </tr>
    <tr>
        <th>Service Calibration</th>
        <td>The System sends a request to the display for calibration data for verification purposes. Data includes SP Zero Value, \htmlonly PIP \endhtmlonly Zero Value, lowest O<sub>2</sub> Calibration Voltage, highest O<sub>2</sub> Calibration Voltage, and other values.</td>
        <th>Service Calibration Response</th>
        <td>22</td>
        <td>All 8 calibration values, with each calibration value stored as 4 bytes (4 * 8 = 32 Bytes).</td>
        <td>35</td>
        <th>Service Calibration Request</th>
        <td>122</td>
        <td></td>
        <td>3</td>
    </tr>
</table>

## Devices Object

The device object tracks the connection between the system controller and display controller by tracking the number of devices mounted to the display controller via USB. On an \htmlonly API \endhtmlonly Cycle, if the system controller is disconnected, then the display will no longer receive notifications or other requests and responses, and the warning manager will raise "Display and System Disconnected!" itself. It is important to note that if the system controller is disconnected, there should only be 2 USB devices mounted, the Linux Foundation 2.0 root hub and Standard Microsystems Corp. USB 2.0 Hub. It is also important to note that when the system controller does get disconnected, the Portname will flip between "ttyUSB0" and "ttyUSB1". Because of this, and when the System Controller and the Display Controller is reconnected via USB and the devices object to 3 mounted devices, the serial port will be reopened and reconfigured.
