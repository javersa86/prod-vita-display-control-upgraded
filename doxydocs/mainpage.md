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

<b>Display Version: 1.1.5</b>

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

## Definitions

<b>Thread</b> - A sequence of software code the application must execute.f

## Background

For the display application to run alongside the system controller, multiple threads need to run continuously with the system and concurrently with each other.

\section thread_list List of Threads

\subsection thread1 API Thread

### Background

The user will power on the device and startup the display application. On Startup, and after the main functions declare the important variables and initiate the different managers and controllers, the API Controller will start the main thread.

### Sequence of Events

1. The \htmlonly API \endhtmlonly Controller is built and running from QThread that starts at the start of the application. Each loop represents an \htmlonly API \endhtmlonly Cycle of at least 30 milliseconds.
2. Starts by opening the Serial Port connected to the system controller through the serial port object with the following Port Name and Baud \htmlonly Rate\endhtmlonly:
    - Serial Port Parameters:
      - Port Name: "/dev/ttyUSB0"
      - Baud \htmlonly Rate\endhtmlonly: 115200
    - If the serial object fails to open the serial port, then an attempt will be made to close the port and exit the thread.
    - If the port is opened, then the appropriate configurations will be made. 
3. Afterwards, an infinite while loop will be triggered and will only be interrupted by request. 
4. Checks to see if the System Controller is connected to the Display Controller via devices object.
5. Reads and processes bytes from the MCU.
6. Handles the different requests and responses from the system controller and sends signals to the backend controller for updates.
7. While the \htmlonly API \endhtmlonly Controller is handling messages from the system, it is also adding messages to a message queue from requests and responses from the backend controller via signals.
8. After handling the different requests and responses and if the queue is not empty, the message queue will lock the mutex for the thread, pop up to 5 messages from the queue, and write those messages to the serial object. The thread and other running threads will wake up again.
9. The thread will sleep for at least 25 milliseconds.

### Module References

- \ref communicationModule "Communication Module"

\subsection thread2 Encoder Knob Thread

### Background

Activities available on the NVENT-VITA include adjusting pneumatic settings in the system. For when adjustment pages are displayed, the Op Mode "Listening Knob" will be enabled (usually when the backend emits a signal to the knob controller).

### Sequence of Events

1. Open the file descriptors for \htmlonly GPIO \endhtmlonly objects representing Pin A, Pin B, and the \htmlonly Switch \endhtmlonly Pin.
2. Sets the state of the switch of the button object with \htmlonly GPIO \endhtmlonly object switch, and the states of the encoder object with the Pin A and B \htmlonly GPIO \endhtmlonly objects.
3. The while loop will then trigger and only be disabled when Op Mode is disabled.
4. Constructs the POLLFD "fdset", the data structure that tracks the file descriptors for each \htmlonly GPIO \endhtmlonly object and sets each event notification to POLLPRI.
   - POLLPRI: to read urgent data
5. Poll the memory of the fd_set for the number of events that changed.
6. If the file descriptor for Pin A is updated, the state representing Pin A on the encoder object changes.
7. If the file descriptor for Pin B is updated, the state representing Pin B on the encoder object changes.
8. If the file descriptor for \htmlonly Switch \endhtmlonly Pin is updated, the state of the Button object changes.
   - Thread will sleep for 75 ms.
9. At the ending, flushes out the standard output.

### Module References

- \ref gpioModule "Knob Controller and other GPIO Components"
- \ref pneumaticSettingPagesModule "Pneumatic Settings Adjustment Pages"
- \ref humidityAdjustmentModule "HumidityAdjustment Page"
- \ref settingsMenuPagesModule "Settings Menu"
- \ref serviceMenuPagesModule "Service Menu"
- \ref customObjectsModule "Custom Objects"

<!--- defines major modules -->

\page modules Modules
\tableofcontents

@defgroup moduleDefinitions Definitions
@brief Definitions available for all modules.
@details

<b>Module</b> - Any of a number of distinct but interrelated units from which a program may be built up or into which a complex activity may be analyzed.<br>
<b>Main</b> - Section of a program that is entered first and from which program units and procedures are called.<br>
<b>Frontend</b> - Everything a user sees and interacts with.<br>
<b>\htmlonly Backend \endhtmlonly</b> - The portion of the code the user doesn’t see.<br>
<b>State</b> - information designed to remember preceding events or user interactions.<br>
<b>Manager</b> - Organizes and stores extra data on the display.<br>
<b>\htmlonly API \endhtmlonly</b> - Application Programming Interface, a way for two or more computer programs to communicate with each other.<br>
<b>\htmlonly GPIO \endhtmlonly</b> (General Purpose Input/Output) - A set of pins on a microcontroller or single-board computer that can be configured to either read input signals from external devices or provide output signals to control external devices. \htmlonly GPIO \endhtmlonly pins can be used to interact with various electronic components and peripherals, such as sensors, LEDS, motors, buttons, and more.<br>
<b>Queue</b> - A data structure that follows the First-In-First-Out (FIFO) Principle, where the element added first will be the first to be removed. Elements are added to the "tail" of the queue, and removed from the "head" of the queue.<br>
<b>Enqueue</b> - The operation of adding (pushing) an element to the rear end of a queue.<br>
<b>Dequeue</b> - The operation of removing (popping) an element from the front end of a queue.<br>

@defgroup frontendModule Frontend Module (GUI)
@brief Documentation for all QML files.
@details

# NVENT VITA Frontend Module Documentation

## GUI Background
The frontend software is the Graphical User Interface that the user will interact with to trigger and change events in the backend module. The GUI will be composed of multiple pages, objects, images, and styling tools.

## GUI Technologies used
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

## GUI Directory Structure

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

## Backend Background
The backend software is responsible for managing all tasks and settings available on the display controller. The backend consists of the backend controller, the state manager, the \htmlonly GPIO \endhtmlonly module, constant models, and multiple loggers and managers for other backend components. This documentation is intended for developers, FDA officials, and medical service technicians who will be working with software.

## Backend Technologies Used
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

## Backend Directory Structure

The backend code is organizaed as followed:
* <b>/src:</b> Header source directory for the backend controller that handles all tasks, and the state manager that manages the state of all settings.
* <b>/src/gpio:</b> Contains the logic for managing the microcontroller connected to the encoder knob.
* <b>/src/logger:</b> Contains the main log manager for writing service logs, the CSV Manager to write all CSV files for service logs, and other managers.
* <b>/src/models:</b> Defines the constant values and models for pneumatic settings, modes, measurements, subsystems, notifications, HMI Buttons, and other settings.
* <b>/src/warnings:</b> Defines the constant values related to warnings, the model structure for all warnings, and contains the management for all warnings running on the system.

## Operational Modes

The Operational Modes (Op Modes) are the distinct settings in which user input produces different results compared to the standard setting of the device.

<table>
    <tr>
    <th>Mode</th><th>Description</th></tr>
    <tr><td>Limited O<sub>2</sub></td><td>The laser on the system is active and the measured oxygen is required to be within a safer threshold to avoid ignition.</td></tr>
    <tr><td>Double Jets</td><td>The device is venting on two jet lines.</td></tr>
    <tr><td>Manual</td><td>Disables automatic ventilation, and the user needs to manually vent the system by pressing down on the encoder knob.</td></tr>
    <tr><td>Screen Lock</td><td>Disables functionality for the screen and the HMI inputs that are not the encoder pushdown button.</td></tr>
    <tr><td>Demo</td><td>Displays all functions of the device, but only for demonstration purposes. Warnings will be hidden.</td></tr>
    <tr><td>\htmlonly PIP \endhtmlonly Disconnected Monitoring</td><td>The \htmlonly PIP \endhtmlonly line is monitored for pressure that is used for a connected patient. Ventilation is disabled if a patient is not found.</td></tr>
    <tr><td>End-Tidal (ETCO<sub>2</sub>) Procedure</td><td>The device ventilates at a state where the level of carbon dioxide is released at the end of an exhaled breath.</td></tr>
    <tr><td>Dehumidification</td><td>Water vapor is being removed from the device.</td></tr>
    <tr><td>O<sub>2</sub> Calibration</td><td>The oxygen sensor is calibrating the accurately read the measurement for oxygen concentration.</td></tr>
    <tr><td>Alarm Sounding</td><td>The device is raising an alarm sound to indicate a warning that needs to be addressed at a high priority, for when the mode is disabled and the warning is still active, a countdown timer will be displayed.</td></tr>
    <tr><td>\htmlonly Humidity \endhtmlonly Priming Reset Available</td><td>The humidification system will be deactivated after the user fails to pump water after 3 attempts. Button will be available in the humidity adjustment page to disabled mode and reset pumps.</td></tr>
    <tr><td>Listening To \htmlonly Knob \endhtmlonly </td><td>The encoder knob is active and listening for input.</td></tr>
    <tr><td>Service Calibration</td><td>Mode only active when the Service Menu is accessed. The Notifications will be disabled, and the Service Notifications will be enabled. The measurements required for calibration will be available and displayed in the Service Menu Calibration page.</td></tr>
    <tr><td>Screen Lock Touched</td><td>Temporary mode that is triggered when Screen Lock Mode is enabled and the user touches the screen or other HMI Inputs.</td></tr>
</table>

## Functionality
The backend consists of the following components:
* \htmlonly Backend \endhtmlonly Controller: main application that handles tasks from the requests and responses from the \htmlonly API \endhtmlonly and QML inputs.
* State Manager: manages the state of pneumatic settings, modes, subsystems, measurements, and other settings.
* Warnings Manager: Manages the number of warnings that are running on the system.
* Models: Constants and Models for all files.
* Log Manager and other managers: the main log manager that writes service logs, and other managers on the display controller.
* \htmlonly GPIO \endhtmlonly Module: Manages the pins connected to the microcontroller that enables the display controller’s encoder knob.

## Backend Controller

### Backend Description

The backend controller is where all activity occurs from the user inputs on the Graphical User Interface and the updates from the system controller. Note that all activities interact with all the managers on the application; see State Manager, Warnings and \htmlonly Warning \endhtmlonly Manager, and Log Manager and other Managers for detail on how data and log entries are saved on the display.

### Backend Request Function

Requests functions construct Op Code Requests that are sent to the system controller through the \htmlonly API \endhtmlonly Thread. The process of sending messages to the \htmlonly API \endhtmlonly go as followed: 
1. Requests are contructed through different datetypes like unsigned characters, ints, and QVectors.
2. The requests are sent to the \htmlonly API \endhtmlonly thread via emitted QObject signals. 
3. After the first signal is sent, the associated unsigned char variable called a flag will be set to true (raised). 
4. While a flag is raised, the associated signal will continue to be emitted with the contructed request. 
5. The flag will be set to false (lowered) when the \htmlonly API \endhtmlonly thread emits their response signal and trigger the \htmlonly Backend \endhtmlonly QObject response slot. 

### Startup Requests

The first 5 requests are only sent on startup, which would then trigger the home page to be displayed. The responses to these requests will save the values received from the \htmlonly API \endhtmlonly to the <b>State Manager</b>.

The <b>Get Settings Request</b> retrieves all pneumatic settings from the \htmlonly API \endhtmlonly on startup if \htmlonly Humidity \endhtmlonly levels do not equal each other, Separate Humidities Mode will be set. The \htmlonly Humidity \endhtmlonly Percentages will be converted to the following levels:
- 100% to level 4
- 70% to level 3
- 50% to level 2
- 30% to level 1
- 0% to level 0
      
The <b>Enable Notifications Request</b> enables the constant retrieval of notifications from the system on startup. Notification updates will be sent to the state manager and the warning manager.
  
The <b>Get Op Modes Request</b> retrieves the state of all op modes enabled or disabled on the system on startup.
  
The <b>Get Subsystem State Request</b> retrieves the state of all subsystems on the system on startup.
  
The <b>Get System Version Request</b> retrieves the most recent version number of the system controller on startup. Also saves the most recent version of the display controller.

### Backend Requests
  
The <b>Set Settings Request</b> updates the values for pneumatic settings requests updates to the system controller. One pneumatic setting can be changed, such as updating the rate from 30 BPM to 90 BPM. But for implementing a <b>Preset</b>, all pneumatic settings can be changed. When <b>Limited O<sub>2</sub> Oxygen Concentration</b> is less than the current oxygen concentration, oxygen concentration is updated. <b>\htmlonly Humidity\endhtmlonly</b> on the jet line and the auxiliary line is updated at once. All setting updates are logged to the <b>Log Manager</b>. When updating <b>\htmlonly Humidity\endhtmlonly</b>, levels will be converted to the following percentages:
- level 4 to 100%
- level 3 to 70%
- level 2 to 50%
- level 1 to 30%
- level 0 to 0%
      
The <b>Get Measured Request</b> retrieves measurements running on the system, such as for detecting water on the system, O<sub>2</sub> Calibration Voltages, or low and high O<sub>2</sub> Calibration values, and saves the measurements to the <b>State Manager</b>.
    
The <b>Clear \htmlonly Warning \endhtmlonly Request</b> clears warnings running on the system by ID. If the warning ID is 59, the display will clear the Service Due warning in the warning manager. If \htmlonly <b>PIP Disconnection Monitoring</b> \endhtmlonly is active, the \htmlonly PIP \endhtmlonly Disconnection warning is triggered and ventilation stops. Clearing the warning will restart ventilation. If the warning ID is either 4, 5, 6, or 7, (the <b> No Water Detected </b> warnings), the warning will be cleared, but the device will also attempt to pump water into the system if a water tube is connected. The warning that is cleared is logged to the <b> Log Manager </b>. 
  
The <b>Enable Op Mode Request</b> enables or disables an Op Mode available in <b>Operation Modes</b> to the <b>State Manager</b> and the system. All Op Mode activities are logged to the <b>Log Manager</b>. Based on which Op Mode is enabled or disabled, different activities in the \htmlonly Backend \endhtmlonly occur:

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
        - Logs most recent calibration data to Log Manager.
        </td>
        <td>
        - Logs most recent calibration data to Log Manager.
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

The following Op Modes Requested will not proceed if different criterias are met:
- If ventilation is inactive or Manual Mode is enabled, enabling <b>ETCO<sub>2</sub> Mode</b> is prevented.
- If ETCO<sub>2</sub> Mode is enabled, enabling <b>Manual Mode</b> is prevented.

The only Op Modes that will be enabled or disbaled together at the same time are <b>Screen Lock Mode</b> and <b>Screen Lock Touched Mode</b>.
    
The <b>Shutdown Confirm Send Request</b> sends a request to the system to confirm that the device can shutdown completely, and can cancel the shutdown procedure. Flags for shutting are also saved to the State Manager. Also, the shutdown request is logged to the Log Manager.
  
The <b>Set DPR Cal Val Request</b> requests to update the state of calibration for pressure regulators. All state changes are logged to the Log Manager. Depending on which state is active, different activities in the \htmlonly Backend \endhtmlonly will occur:

<table>
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
    <td>Sets Driving Pressure to 48. State change confirmation is logged to the Log Manager.</td>
</tr>
<tr>
    <td>O<sub>2</sub> Regulator</td>
    <td>Sets Driving Pressure to 48. State change confirmation is logged to the Log Manager.</td>
</tr>
<tr>
    <td>Default</td>
    <td></td>
</tr>
</table>

The <b>Enable Pressure Sensor Zero Request</b> sends calibration verification for the following sensors: Inlet Air, Inlet O<sub>2</sub>, \htmlonly PIP\endhtmlonly, and SP. Saves value to Zero Calibration Manager for Sensor values. States of calibrations are logged to the Log Manager.
  
### Other Backend Functions

The backend will continuously receive data from the system. Most importantly, the backend receives <b>Notifications</b> and <b>Service Notifications</b> from the \htmlonly API. \endhtmlonly

The following are data is received from the Notifications and Service Notifications:
- The measurements for Stacking Pressure, Oxygen, Peak Inspiratory Pressure, Auxiliary Flow, TV, and MAP that are saved to the State Manager.
- The states for all 72 warnings are saved to the \htmlonly Warning \endhtmlonly Banner.
- The silence timer countdown time to the State Manager.
- The measurements for the average Stacking Pressure data, the instantaneous Stacking Pressure data, the average Peak Inspiratory Pressure data, the instantaneous Peak Inspiratory Pressure data, and the real-time O<sub>2</sub> Calibration voltage to the State Manager.

The backend will also receive ventilation status updates, which will be utilized for the state manager, the End-Tidal Button, and the part manager; and ids for which the HMI button is pushed, and is especially useful for screen lock mode. Both inputs are saved to the State Manager and will be logged to the Log Manager.

For Modes requested from the system, the states of the Modes will be logged to the Log Manager, and the following will occur:
- When the system enables or disables the O<sub>2</sub> Calibration Op Mode successfully, the measurement for the lowest and highest Calibration values and voltages are requested to the system, then saved to the State Manager and O<sub>2</sub> Calibration Manager. Calibration failures with no new measurements will be logged to the Log Manager.
- When the system enables dehumidification, the \htmlonly Humidity \endhtmlonly on the Jet Line and the Auxiliary Line is set to 0.

For exporting service logs and other files to the USB, the backend detects the dev port for a USB drive, and finds and creates the directories to send files. Once finished, the backend will eject the dev port for the USB drive.

For <b>Service Menu</b> service logs, the backend updates the log manager for when the service menu is opened, see Log Manager.

For <b>Dehumidification</b>, the backend runs a 2 minute countdown timer for when the dehumidification progress page is up.

For when the system begins the <b>Shutdown Procedure</b>, the backend requests measurements for Water Sensors to determine if water is detected on Jet and Auxiliary Lines. All values are saved to the State Manager.

Lastly, the backend sends service calibration data as a QVector back to the system via signal to \htmlonly API \endhtmlonly.

## State Manager

The State Manager stores and controls the following from the backend controller and the Graphical User Interface. States are stored in different data types, and are either constantly updating, or remain static.

<table>
    <tr>
        <th>States</th>
        <th>Description</th>
    </tr>
    <tr>
        <td>Shutdown Flag</td>
        <td>State for when the shutdown procedure is active or inactive.</td>
    </tr>
    <tr>
        <td>Startup Flags</td>
        <td>State for when the startup procedure is still active or complete.</td>
    </tr>
    <tr>
        <td>Display Version</td>
        <td>Text representation for the most recent Display Version Number.</td>
    </tr>
    <tr>
        <td>System Version</td>
        <td>Text representation for the most recent System Version Number.</td>
    </tr>
    <tr>
        <td>Ventilating</td>
        <td>State for when system ventilation is active or inactive.</td>
    </tr>
<tr>
<td>
Op Modes
</td>
<td>
States stored that represent when mode is enabled or disabled. Op Modes include the following:
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
</td>
</tr>
<tr>
<td>
\htmlonly Humidity \endhtmlonly Separation
</td>
<td>
The state for when adjustments for humidity on the Jet Line are Auxiliary Line are separate.
</td>
</tr>
<tr>
<td>
Op Mode Successes
</td>
<td>
The states for when the following Op Mode Procedures succeed or fail:
Dehumidification
O2 Calibration
End-Tidal Mode
</td>
</tr>
<tr>
<td>
Subsystems
</td>
<td>
The states for when each subsystem is active or not:
- Primary Ventilation
- Secondary Ventilation
- Auxiliary Flow
- Oxygen Control
- Primary Humidification
- Secondary Humidification
- Auxiliary Humidification
</td>
</tr>
<tr>
<td>
Pneumatic Settings
</td>
<td>
The states that represent the values set by the user. Settings include the following:
- Driving Pressure
- \htmlonly Rate \endhtmlonly
- Inspiratory Time
- Stacking Pressure
- Oxygen Concentration
- Peak Inspiratory Pressure
- Auxiliary Flow
- \htmlonly Humidity \endhtmlonly on the Jet Line
- \htmlonly Humidity \endhtmlonly on the Auxiliary Line
</td>
</tr>
<tr>
<td>
Double Jet Pneumatic Settings
</td>
<td>
If a double jet is installed on the device, then the following additional pneumatic settings will be set by the user:
- Driving Pressure
- \htmlonly Rate \endhtmlonly
- Inspiratory Time
- Stacking Pressure
- \htmlonly Humidity \endhtmlonly on the Second Jet Line
</td>
</tr>
<tr>
<td>
End-Tidal Settings
</td>
<td>
The states that represent the pneumatic settings set by the user for when End-Tidal Mode is active. Settings include the following:
- ETCO<sub>2</sub> \htmlonly Rate \endhtmlonly 
- ETCO<sub>2</sub> Inspiratory Time
- ETCO<sub>2</sub> Number of Breaths
- ETCO<sub>2</sub> Driving Pressure
</td>
</tr>
<tr>
<td>
Limited O<sub>2</sub> Oxygen Concentration
</td>
<td>
The state set by the user for Oxygen Concentration during Limited O<sub>2</sub> Mode.
</td>
</tr>
<tr>
<td>
\htmlonly Volume \endhtmlonly
</td>
<td>
State set by the user for the volume of the Display Controller Alarm Sound.
</td>
</tr>
<tr>
<td>
Oxygen Saved State - Limited O<sub>2</sub>
</td>
<td>
The state for the originally set Oxygen Concentration while Limited O<sub>2</sub> Mode is active.
</td>
</tr>
<tr>
<td>
States of Limited O<sub>2</sub>
</td>
<td>
The states of Limited O<sub>2</sub> for when the oxygen measurement on the notification vector reaches the minimum oxygen and set oxygen.
</td>
</tr>
<tr>
<td>
Pressure Regulator Calibration
</td>
<td>
The state for when a calibration procedure is active for any of the Pressure Regulators.
</td>
</tr>
<tr>
<td>
Sensor Calibration Values
</td>
<td>
States of the following Sensor Calibration values:
- Inlet Air
- Inlet O<sub>2</sub>
- Peak Inspiratory Pressure
- Stacking Pressure
</td>
</tr>
<tr>
<td>
Driving Pressure Save State - Pressure Regulator Calibration
</td>
<td>
The state for the originally set Driving Pressure while Pressure Regulator Calibration is active.
</td>
</tr>
<tr>
<td>
Notifications
</td>
<td>
Measurements for the following values sent from the System:
- Stacking Pressure
- Stacking Pressure on second Jet Line
- Oxygen Concentration
- Peak Inspiratory Pressure
- Auxiliary Flow
- Tidal \htmlonly Volume \endhtmlonly
- Tidal \htmlonly Volume \endhtmlonly on second Jet Line
- Map
- Alarm Time
</td>
</tr>
<tr>
<td>
Oxygen Adjustment
</td>
<td>
The state for when to display the spinner icon when oxygen is adjusting.
</td>
</tr>
<tr>
<td>
Measurements
</td>
<td>
The states of the most recent measurements on the system:
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
</td>
</tr>
<tr>
<td>
IP Address
</td>
<td>
Text representation for the Display Controller IP Address (retrieves and sets IP Address from local network).
</td>
</tr>
<tr>
<td>
Preset Implementation Progress
</td>
<td>
The state for when preset implementation is active or inactive, which is when the pneumatic settings stored on a preset are being sent to the system controller.

<b>Note:</b> State exists due to the time it takes to implement preset and multiple pneumatic settings at once.
</td>
</tr>
<tr>
<td>
\htmlonly Warning \endhtmlonly Banner Displayed
</td>
<td>
The state for when the warning banner on the GUI is visible or not.
</td>
</tr>
<tr>
<td>
Preset Creation
</td>
<td>
The state for when the user is creating or editing a preset.
</td>
</tr>
<tr>
<td>
Stacking Pressure Line
</td>
<td>
The state visibility for Stacking Pressure line on the home page graph.
</td>
</tr>
<tr>
<td>
End-Tidal Button
</td>
<td>
The state for when the End-Tidal Button on the home page is enabled or disabled.
</td>
</tr>
<tr>
<td>
Service Log Count
</td>
<td>
State for the total number of service logs stored on the display controller.
</td>
</tr>
<tr>
<td>
Service Logs Exported
</td>
<td>
State for the number of service logs that are exported to the connected USB drive.
</td>
</tr>
<tr>
<td>
Service Notifications
</td>
<td>
Measurements for the following values sent from the System while the Service Menu is opened:
- Stacking Pressure Average Data
- Stacking Pressure Instantaneous Data
- Peak Inspiratory Pressure Average Data
- Peak Inspiratory Pressure Instantaneous Data
- O<sub>2</sub> Calibration Voltage Data

<b>Note:</b> More measurements will be added later on.
</td>
</tr>
</table>


## Additional Information

Information for the other components of the \htmlonly Backend \endhtmlonly is available in the following links:

- @ref warningsModule "Warnings and Warning Manager"
- @ref modelsModule "Models"
- @ref loggerModule "Log Manager and other Managers"
- @ref gpioModule "GPIO Module"

@defgroup communicationModule Communication Module (API Controller)
@brief Documentation for how the Display Controller and the System Controller communication between each other.
@details

## API Background

The \htmlonly API \endhtmlonly software works separately from the backend and frontend module, for its single tasked requesting and responding to messages from the system controller. The Communication Module is composed of the main \htmlonly API \endhtmlonly Controller that runs on a looping thread, the Serial Port object, and other components to make commuication more structured.

## API Technologies Used
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

<b>Libusb</b> is a C library that provides generic access to USB devices is utilized for devices object.
Link: <a href="https://libusb.info/">Libusb Documentation</a>

## API Directory Structure
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

The <b>\htmlonly Comm \endhtmlonly Object</b> is the UART Serial Port between the Display Controller and the System Controller. The specified port from the Port Name and Baud Rate opens and reads the file descriptor to read and write bytes. After reading the existing settings and handling errors, it constructs the tty settings structure to raise the following port settings:
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

When the API Cycle reads from the Serial Port, The Comm Objects reads to the file descriptor and stores the available bytes to an array buffer of at most 512 bytes. The API Cycle will then process the array buffer by reading the array by index until bytes are no longer available. A message from the array is structured as followed:
- <b>Start Charactor (255):</b> the beginning byte for all requests and responses.
- <b>Op Code:</b> The Byte to represent the type of request or response.
- <b>Body:</b> the number bytes representing the parameters for message if available. The body will also have different lengths.
- <b>CRC:</b> Byte to represent the ending of the message.

Messages written to the file descriptor's are stored on an array buffer as well and are structured the same way.

## Message Object and Message Queue

A <b>\htmlonly Message \endhtmlonly object</b> for sending requests and responses to the system controller contains the following parameters:
- <b>The Input Buffer Array:</b> The array at the size of 512 bytes that store the bytes representing the request or response to the serial port. All input buffers will always include the following bytes:
  - The <b>Start Character,</b> the first byte of the message to indicate the beginning of the message, which will always be 255.
  - The <b>Op Code</b> that represents the message sent or received.
- <b>The CRC Byte:</b> The character representing the end of the message, and is a unique character used to represent the message.
- <b>TX Size:</b> The size or length of the message within the array buffer. The size will always include the Start Character, the Op Code

The <b>\htmlonly Message \endhtmlonly Queue</b> is built from a QQueue object and stores all Message objects. While the backend and the rest of the application are enqueuing messages to the queue, up to 5 messages will be dequeued from the queue at the end of the \htmlonly API \endhtmlonly cycle. To ensure that no repeated messages are pushed to the queue before being sent to the system controller, the queue also tracks the unique crc bytes to an unordered set and checks if a new message contains an existing CRC byte before being pushed to the queue.

## API Requests and Responses

There are multiple requests and responses that need to be sent between the display controller and system controller. 

### API Message Exchanges

<table>
    <tr>
        <th style="background-color: #202531; border-color: #202531"> Messages </th>
        <th style="background-color: #202531; border-color: #202531"> Description </th>
    </tr>
    <tr>
        <th> Power On </th>
        <td> The System Controller sends a request to confirm with a response that the Display Controller is powered on alongside the System controller. </td>
    </tr>
    <tr>
        <th> Get Settings </th>
        <td> On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all pneumatic settings stored on the system and will receive a response with setting values. </td>
    </tr>
    <tr>
        <th>Enable Notification</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request to receive notifications from the system and will receive a response to confirm it.</td>
    </tr>
    <tr>
        <th>Get Op Modes</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all modes enabled and disabled on the system and will receive a response with mode states.</td>
    </tr>
    <tr>
        <th>Get Subsystem States</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for all subsystems active on the system and will receive a response with subsystem status.</td>
    </tr>
    <tr>
        <th>Get System Version</th>
        <td>On startup, the Display Controller's \htmlonly Backend \endhtmlonly Controller will send a request for the system controller's version number and will receive a response with version number.</td>
    </tr>
    <tr>
        <th>Set Settings</th>
        <td>The Display's \htmlonly Backend \endhtmlonly will send a request to update the pneumatic settings to the system and will receive a response to confirm that the update succeeded.</td>
    </tr>
    <tr>
        <th>Get Measured</th>
        <td>The Display's \htmlonly Backend \endhtmlonly will request a measurement running on the system and will receive a response with the measured value.</td>
    </tr>
    <tr>
        <th>Clear \htmlonly Warning \endhtmlonly </th>
        <td>The Display's \htmlonly Backend \endhtmlonly will send a request to clear a warning running on the system and will receive a response with the warning id to clear the warning from the warning banner.</td>
    </tr>
    <tr>
        <th>Enable Op Mode from Display to System</th>
        <td>The Display's \htmlonly Backend \endhtmlonly will send a request to enable or disable an op mode and will receive a response confirming that mode was enabled or disabled.</td>
    </tr>
    <tr>
        <th>Enable Op Mode from System to Display</th>
        <td>The System will send a message that mode was enabled or disabled and the display will send a response to confirm that message was received.</td>
    </tr>
    <tr>
        <th>Notifications</th>
        <td>The System will send the constant measurments for Stacking Pressure, Oxygen, Peak Inspiratory Pressure, Auxiliary Flow, Tidal \htmlonly Volume\endhtmlonly, Mean Average Pressure, states of all warnings, and Alarm Silence Time. Display will send response message after every 10 updates.</td>
    </tr>
    <tr>
        <th>Subsystem Status</th>
        <td>The System sends changed states for subsystem states, and Display confirms received subsystem state change and saves new subsystem states.</td>
    </tr>
    <tr>
        <th>Ventilation Status</th>
        <td>The System sends the state of ventilation, and the Display confirms and saves the received ventilation state.</td>
    </tr>
    <tr>
        <th>HMI Button Pushed</th>
        <td>The System sends which HMI Button was pressed and the Display confirms which HMI Button was pushed.</td>
    </tr>
    <tr>
        <th>Shutdown</th>
        <td>The System sends request (triggered from user input of power button) to initiate the shutdown procedure, and the display confirms and will begin procedure.</td>
    </tr>
    <tr>
        <th>Shutdown Confirm or Cancel</th>
        <td>The Display sends a request to confirm or cancel the shutdown, and the system responses back.</td>
    </tr>
    <tr>
        <th>Set DPR Calibration Value</th>
        <td>The Display sends a request for the state of pressure regulator calibration, and system sends a response that calibration state is active.</td>
    </tr>
    <tr>
        <th>Enable Pressure Sensor Zero</th>
        <td>The Display sends a request for sensor calibration, and system sends a response that completes the calibration completely.</td>
    </tr>
    <tr>
        <th>Service Notifications</th>
        <td>For when the Service Menu is accessed, the Service Calibration Op Mode will be enabled from the Display, and the System will send the constant measurments for SP Average Data, SP Instant Data, \htmlonly PIP \endhtmlonly Average Data, \htmlonly PIP \endhtmlonly Instant Data, and O<sub>2</sub> Calibration Voltage.</td>
    </tr>
    <tr>
        <th>Service Calibration</th>
        <td>The System sends a request to the display for calibration data for verification purposes. Data includes SP Zero Value, \htmlonly PIP \endhtmlonly Zero Value, lowest O<sub>2</sub> Calibration Voltage, highest O<sub>2</sub> Calibration Voltage, and other values.</td>
    </tr>
</table>

### Display Messages

<table>
    <tr>
        <th style="background-color: #202531; border-color: #202531"> Display \htmlonly Message \endhtmlonly </th>
        <th style="background-color: #202531; border-color: #202531"> Display Op Code </th>
        <th style="background-color: #202531; border-color: #202531"> Display Bytes </th>
        <th style="background-color: #202531; border-color: #202531"> Display Length </th>
    </tr>
    <tr>
        <th> Power On Received </th>
        <td> 0 </td>
        <td></td>
        <td> 3 </td>
    </tr>
    <tr>
        <th>Get Settings Request</th>
        <td>1</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Enable Notification Request</th>
        <td>2</td>
        <td>Enable or Disable State</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Get Op Modes Request</th>
        <td>3</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Get Subsystem States Request</th>
        <td>4</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Get System Version Request</th>
        <td>5</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Set Settings Request</th>
        <td>6</td>
        <td>All 20 Pneumatic Settings, with each setting stored as 4 bytes (4 * 20 = 80).</td>
        <td>83</td>
    </tr>
    <tr>
        <th>Get Measured Request</th>
        <td>7</td>
        <td>Requested Measurement ID</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Clear \htmlonly Warning \endhtmlonly Request</th>
        <td>8</td>
        <td>Requested \htmlonly Warning \endhtmlonly ID</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Enable Op Mode Display Request</th>
        <td>9</td>
        <td>
        - Requested Op Mode ID
        - Enable or Disable State
        - Success State
        </td>
        <td>6</td>
    </tr>
    <tr>
        <th>Enable Op Mode Display Response</th>
        <td>10</td>
        <td>
        - Requested Op Mode ID
        - Enable or Disable State
        </td>
        <td>5</td>
    </tr>
    <tr>
        <th>Notification Received Response</th>
        <td>11</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Subsystem Status Received</th>
        <td>12</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Ventilation Status Received</th>
        <td>13</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>HMI Button Pushed Received</th>
        <td>14</td>
        <td>HMI Button ID</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Shutdown Received</th>
        <td>15</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Shutdown Confirm or Cancel Request</th>
        <td>16</td>
        <td>Confirm or Cancel State</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Set DPR Calibration Value Request</th>
        <td>18</td>
        <td>Pressure Regulator Calibration State</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Enable Pressure Sensor Zero Request</th>
        <td>20</td>
        <td>Sensor Calibration ID </td>
        <td>8</td>
    </tr>
    <tr>
        <th>Service Calibration Response</th>
        <td>22</td>
        <td>All 8 calibration values, with each calibration value stored as 4 bytes (4 * 8 = 32 Bytes).</td>
        <td>35</td>
    </tr>
</table>

### System Messages

<table>
    <tr>
        <th style="background-color: #202531; border-color: #202531"> System \htmlonly Message \endhtmlonly </th>
        <th style="background-color: #202531; border-color: #202531"> System Op Code </th>
        <th style="background-color: #202531; border-color: #202531"> System Bytes </th>
        <th style="background-color: #202531; border-color: #202531"> System Length </th>
    </tr>
    <tr>
        <th> Power On Send </th>
        <td> 100 </td>
        <td></td>
        <td> 3 </td>
    </tr>
    <tr>
        <th>Get Settings Response</th>
        <td>101</td>
        <td>All 20 Pneumatic Settings, with settings stored as 4 bytes (4 * 20 = 80). Bytes representing settings are converted to float values.</td>
        <td>83</td>
    </tr>
    <tr>
        <th>Enable Notification Response</th>
        <td>102</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Get Op Modes Response</th>
        <td>103</td>
        <td>All 15 Op Mode States</td>
        <td>18</td>
    </tr>
    <tr>
        <th>Get Subsystem States Response</th>
        <td>104</td>
        <td>All 7 Subsystem States</td>
        <td>10</td>
    </tr>
    <tr>
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
        <th>Set Settings Response</th>
        <td>106</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Get Measured Response</th>
        <td>107</td>
        <td>
        - Requested Measurement ID
        - Measurement Float Value represented as 4 Bytes
        </td>
        <td>8</td>
    </tr>
    <tr>
        <th>Clear \htmlonly Warning \endhtmlonly Response</th>
        <td>108</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Enable Op Mode System Response</th>
        <td>109</td>
        <td>
        - Requested Op Mode ID
        - Enable or Disable State
        </td>
        <td>5</td>
    </tr>
    <tr>
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
        <th>Subsystem Status Update</th>
        <td>112</td>
        <td>All 7 Subsystem States</td>
        <td>10</td>
    </tr>
    <tr>
        <th>Ventilation Status Update</th>
        <td>113</td>
        <td>Ventilation State</td>
        <td>4</td>
    </tr>
    <tr>
        <th>HMI Button Pushed Update</th>
        <td>114</td>
        <td>HMI Button ID</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Shutdown Request</th>
        <td>115</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Shutdown Confirm Received</th>
        <td>116</td>
        <td>Confirm or Cancel State</td>
        <td>4</td>
    </tr>
    <tr>
        <th>Set DPR Calibration Value Response</th>
        <td>118</td>
        <td></td>
        <td>3</td>
    </tr>
    <tr>
        <th>Enable Pressure Sensor Zero Response</th>
        <td>120</td>
        <td>Success or Failure Value</td>
        <td>5</td>
    </tr>
    <tr>
        <th>Service Notification Received Response</th>
        <td>121</td>
        <td>All 5 measurements, with each measurement stored as 4 bytes (4 * 5 = 20 Bytes).</td>
        <td>23</td>
    </tr>
    <tr>
        <th>Service Calibration Request</th>
        <td>122</td>
        <td></td>
        <td>3</td>
    </tr>
</table>

## Devices Object

The device object tracks the connection between the system controller and display controller by tracking the number of devices mounted to the display controller via USB. On an API Cycle, if the system controller is disconnected, then the display will no longer receive notifications or other requests and responses, and the warning manager will raise "Display and System Disconnected!" itself. It is important to note that if the system controller is disconnected, there should only be 2 USB devices mounted, the Linux Foundation 2.0 root hub and Standard Microsystems Corp. USB 2.0 Hub. It is also important to note that when the system controller does get disconnected, the Portname will flip between "ttyUSB0" and "ttyUSB1". Because of this, and when the System Controller and the Display Controller is reconnected via USB and the devices object to 3 mounted devices, the serial port will be reopened and reconfigured.
