\mainpage Display Overview
\tableofcontents

This page is the main introduction page that will outline all major design parameters for the display controller. \n\n

This manual is divided in the following sections:
1. \subpage introduction "Introduction" <br>
        &emsp;&emsp;1.1 \subpage introduction_background "Background" <br>
        &emsp;&emsp;1.2 \subpage introduction_tech_used "Technologies Used" <br>
        &emsp;&emsp;1.3 \subpage introduction_directory_structure "Directory Structure" <br>
2. \subpage mainThread   "Threading Architecture" <br>
        &emsp;&emsp;2.1 \subpage mainThread_definitions "Definitions" <br>
        &emsp;&emsp;2.2 \subpage mainThread_background "Background" <br>
        &emsp;&emsp;2.3 \subpage thread_list "List of Threads" <br>
                &emsp;&emsp;&emsp;&emsp;2.3.1 \subpage thread1 "API Thread" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;2.3.1.1 \subpage thread1_background "Background" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;2.3.1.2 \subpage thread1_sequence "Sequence of Events" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;2.3.1.3 \subpage thread1_references "Module References" <br>
                &emsp;&emsp;&emsp;&emsp;2.3.2 \subpage thread2 "Encoder Knob Thread" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;2.3.2.1 \subpage thread2_background "Background" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;2.3.2.2 \subpage thread2_sequence "Sequence of Events" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;2.3.2.3 \subpage thread2_references "Module References" <br>
3. \subpage modules "Modules" <br>
        &emsp;&emsp;3.1 \subpage moduleDefinitions "Definitions" <br>
        &emsp;&emsp;3.2 \subpage main "Main Application" <br>
        &emsp;&emsp;3.3 \subpage frontendModule "Frontend Module (GUI)" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.1 \subpage frontendModule_background "GUI Background" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.2 \subpage frontendModule_technologies "GUI Technologies Used" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.3 \subpage frontendModule_directory "GUI Directory Structure" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.4 \subpage frontendModule_page_description "Page Description" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.5 \subpage frontendModule_page_stacks "Page StackViews" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.6 \subpage pagesModule "Pages" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.1 \subpage homePagesModule "Main Window and its Related Pages" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.2 \subpage pneumaticSettingPagesModule "Pneumatic Settings Adjustment Pages" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.3 \subpage humidityAdjustmentModule "Humidity Adjustment Page" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.4 \subpage presetPagesModule "Preset Options" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.5 \subpage jetActiveModule "Shutdown and Dehumidification Pages" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.6 \subpage screenlockModule "Screen Lock Mode" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.7 \subpage helpPagesModule "Help Pages" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.8 \subpage troubleshootingPagesModule "Troubleshooting Steps" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.9 \subpage settingsMenuPagesModule "Settings Menu" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.6.10 \subpage serviceMenuPagesModule "Service Menu" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.7 \subpage customObjectsModule "Custom Objects" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.1 \subpage customObjectsGraph "Graph" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.2 \subpage customObjectsNavigation "Navigational Sidebar and Inputs" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.3 \subpage customObjectsWarningBanner "Warning Banner" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.4 \subpage customObjectsOtherObjects "Other Objects" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.5 \subpage customObjectsInputs "Buttons and Other Inputs" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.6 \subpage customObjectsSwitches "Switches" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.7 \subpage customObjectsKeyboards "Keyboards and Keypads" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.3.7.8 \subpage customObjectsLayouts "Page Layouts" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.8 \subpage stylingModule "Styling" <br>
                &emsp;&emsp;&emsp;&emsp;3.3.9 \subpage iconographyModule "Iconography" <br>
        &emsp;&emsp;3.4 \subpage backendModule "Backend Module (Backend Controller)" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.1 \subpage backendModule_background "Backend Background" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.2 \subpage backendModule_technologies "Backend Technologies Used" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.3 \subpage backendModule_directory "Backend Directory Structure" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.4 \subpage backendModule_modes "Operational Modes" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.5 \subpage backendController "Backend Controller" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.5.1 \subpage backendController_description "Backend Description" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.5.2 \subpage backendController_request_function "Backend Request Function" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.5.3 \subpage backendController_startup_requests "Backend Startup Requests" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.5.4 \subpage backendController_requests "Backend Requests" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.5.5 \subpage backendController_functions "Other Backend Functions" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.6 \subpage stateManager "State Manager" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.7 \subpage warningsModule "Warnings and Warning Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.7.1 \subpage warningsModule_classes "Warning Classes" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.7.2 \subpage warningsModule_clear_behavior "Warning Clear Behavior" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.7.3 \subpage warningsParent "List of Warnings" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.7.4 \subpage warningsManager "Warning Manager" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.8 \subpage modelsModule "Models" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.8.1 \subpage opModeModels "Op Mode IDs" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.8.2 \subpage hmiModels "HMI Input IDs" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.8.3 \subpage settingsModels "Pneumatic Settings Models" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.8.4 \subpage notificationModels "Notifications" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.8.5 \subpage serviceNotificationModels "Service Notifications" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.9 \subpage loggerModule "Log Manager and other Managers" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.1 \subpage csvManagerModule "CSV Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.2 \subpage logManagerModule "Log Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.3 \subpage brightnessManagerModule "Brightness Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.4 \subpage contactManagerModule "Contact Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.5 \subpage dprManagerModule "DPR Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.6 \subpage maintenanceManagerModule "Maintenance Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.7 \subpage o2CalManagerModule "O2 Calibration Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.8 \subpage partManagerModule "Part Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.9 \subpage passcodeManagerModule "Passcode Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.10 \subpage presetManagerModule "Preset Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.11 \subpage timeManagerModule "Time Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.12 \subpage versionManagerModule "Version Manager" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.9.13 \subpage zeroManagerModule "Zero Manager" <br>
                &emsp;&emsp;&emsp;&emsp;3.4.10 \subpage gpioModule "Knob Controller and other GPIO Components" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.10.1 \subpage knobModule "Knob Controller" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.10.2 \subpage gpioModule_calc "Calculating Pin Numbers" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.10.3 \subpage switchModule "Switch" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.10.4 \subpage encoderModule "Encoder" <br>
                        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;3.4.10.5 \subpage gpioMainModule "GPIO" <br>
        &emsp;&emsp;3.5 \subpage communicationModule "Communication Module (API Controller)" <br>
                &emsp;&emsp;&emsp;&emsp;3.5.1 \subpage communicationModule_background "API Background" <br>
                &emsp;&emsp;&emsp;&emsp;3.5.2 \subpage communicationModule_technologies "API Technologies Used" <br>
                &emsp;&emsp;&emsp;&emsp;3.5.3 \subpage communicationModule_directory "API Directory Structure" <br>
                &emsp;&emsp;&emsp;&emsp;3.5.4 \subpage serialModule "Serial Port Communication (Comm Object)" <br>
                &emsp;&emsp;&emsp;&emsp;3.5.5 \subpage messageModule "Message Object and Message Queue" <br>
                &emsp;&emsp;&emsp;&emsp;3.5.6 \subpage apiModule "API Requests and Responses" <br>
                &emsp;&emsp;&emsp;&emsp;3.5.7 \subpage devicesModule "Devices Object" <br>
                        
        
        




<!-- Introduction -->
        
\page introduction Introduction
\tableofcontents

\section introduction_background Background

The NVENT-VITA Display Controller software is the graphical user interface application that allows the user to interact with NVENT VITA’s system features. The software is designed to manage and track the different pneumatic settings, measurements, modes, data, and other features available on the device. For the display controller software, it consists of frontend components, the backend controller, and the \htmlonly API \endhtmlonly Thread where the display controller communicates with the system controller.

<b>Display Version: 1.2.0</b>

\section introduction_tech_used Technologies Used

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

\section introduction_directory_structure Directory Structure

The project is organized as followed:
* <b>/qml:</b> Contains all UI components built from QML.
* <b>/scripts:</b> Contains CMake and shell scripts required to run the QT Project and utilize all display \htmlonly GPIO \endhtmlonly components of the A62 board.
* <b>/src:</b> Contains all source files for executing the application.




<!--- defines main thread -->

\page mainThread Threading Architecture
\tableofcontents
This page gives detailed information on threading.

\section mainThread_definitions Definitions

<b>Thread</b> - A sequence of software code the application must execute.

\section mainThread_background Background

For the display application to run alongside the system controller, multiple threads need to run continuously with the system and concurrently with each other.

\section thread_list List of Threads

\subsection thread1 API Thread

\subsubsection thread1_background Background

The user will power on the device and startup the display application. On Startup, and after the main functions declare the important variables and initiate the different managers and controllers, the API Controller will start the main thread.

\subsubsection thread1_sequence Sequence of Events

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

\subsubsection thread1_references Module References

- \ref communicationModule "Communication Module"

\subsection thread2 Encoder Knob Thread

\subsubsection thread2_background Background

Activities available on the NVENT-VITA include adjusting pneumatic settings in the system. For when adjustment pages are displayed, the Op Mode "Listening Knob" will be enabled (usually when the backend emits a signal to the knob controller).

\subsubsection thread2_sequence Sequence of Events

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

\subsubsection thread2_references Module References

- \ref gpioModule "Knob Controller and other GPIO Components"
- \ref pneumaticSettingPagesModule "Pneumatic Settings Adjustment Pages"
- \ref humidityAdjustmentModule "HumidityAdjustment Page"
- \ref settingsMenuPagesModule "Settings Menu"
- \ref serviceMenuPagesModule "Service Menu"
- \ref customObjectsModule "Custom Objects"







<!--- defines major modules -->

\page modules Modules
\tableofcontents





<!--- Definitons -->

@defgroup moduleDefinitions Definitions
@brief Definitions available for all modules.
@{
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
@}





<!--- Frontend -->

@defgroup frontendModule Frontend Module (GUI)
@brief Documentation for all QML files.
@{
@details

\section frontendModule Frontend Module (GUI)

\subsection frontendModule_background GUI Background

The frontend software is the Graphical User Interface that the user will interact with to trigger and change events in the backend module. The GUI will be composed of multiple pages, objects, images, and styling tools.

\subsection frontendModule_technologies GUI Technologies Used

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

\subsection frontendModule_directory GUI Directory Structure

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

\subsection frontendModule_page_description Page Description

In context to the graphical user interface, a page refers to a screen within an application that presents a specific set of information or functionality to the user. A page will be composed of different objects, texts, and inputs (referred to as mouse areas). Each page size will match the screen size of the display controller's screen, which is 1280 x 800. For popup windows, the page itself will still be 1280 x 800, but the background will be transparent and the middle section will be composed of a rectangular box.

\subsection frontendModule_page_stacks Page StackViews

A <b>StackView</b> is a component that provides a way to manage multiple views/pages in a stack-like manner for navigation. Stack refers to a data structure that follows the Last-In-First-Out (LIFO) Model. It is a collection of elements in which items can be added or removed only from one end. Note that for Popup windows and pages that are not the Home page, the Preset Creation page, and the Service Menu page will automatically redirect back to the home page if there is no activity or input for at least 1 minute.

The <b>Home Stack</b> is where the user will navigate between main components of the GUI, including the following: the Home Window Page, Adjustment Pages, the Preset Pages, the Settings Menu Page, Passcode Pages, and the Service Menu Page.

The <b>Popup Stack</b> is where the user pushes up Popup Windows and other pages separate from the main components: the Screen Lock Popup and Overlay, Dehumidification Popups and Progress Page, the Jet Active Popup and Shutdown Procedure Popups, the Help and Troubleshooting Boxes, the Preset Name Popup and the Preset Implementation Popup, and the Pneumatic Settings Confirmation Popup.

The <b>Adjustment Page</b> Stacks are utilized for adjustment pages where the user will need to switch between the dial page, and the keypad page.

The <b>Service Popup Stack</b> is specifically for the popup windows available on the Service Menu.

The <b>Settings Stacks</b> are used to contain menu pages for the Settings Menu and the Service Menu.
@}



<!-- Backend -->

@defgroup backendModule Backend Module (Backend Controller)
@brief Documentation for backend functions and features.
@{
@details 

\section backendModule Backend Module (Backend Controller)

\subsection backendModule_background Backend Background

The backend software is responsible for managing all tasks and settings available on the display controller. The backend consists of the backend controller, the state manager, the \htmlonly GPIO \endhtmlonly module, constant models, and multiple loggers and managers for other backend components. This documentation is intended for developers, FDA officials, and medical service technicians who will be working with software.

\subsection backendModule_technologies Backend Technologies Used

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

\subsection backendModule_directory Backend Directory Structure

The backend code is organizaed as followed:
* <b>/src:</b> Header source directory for the backend controller that handles all tasks, and the state manager that manages the state of all settings.
* <b>/src/gpio:</b> Contains the logic for managing the microcontroller connected to the encoder knob.
* <b>/src/logger:</b> Contains the main log manager for writing service logs, the CSV Manager to write all CSV files for service logs, and other managers.
* <b>/src/models:</b> Defines the constant values and models for pneumatic settings, modes, measurements, subsystems, notifications, HMI Buttons, and other settings.
* <b>/src/warnings:</b> Defines the constant values related to warnings, the model structure for all warnings, and contains the management for all warnings running on the system.

\subsection backendModule_modes Operational Modes

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
@}




<!-- API -->

@defgroup communicationModule Communication Module (API Controller)
@brief Documentation for how the Display Controller and the System Controller communication between each other.
@details

\section communicationModule Communication Module (API Controller)

\subsection communicationModule_background API Background

The \htmlonly API \endhtmlonly software works separately from the backend and frontend module, for its single tasked requesting and responding to messages from the system controller. The Communication Module is composed of the main \htmlonly API \endhtmlonly Controller that runs on a looping thread, the Serial Port object, and other components to make commuication more structured.

\subsection communicationModule_technologies API Technologies Used
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

\subsection communicationModule_directory API Directory Structure

The api code is organized as followed:
* <b>/src/communication:</b> Header source directory for the api controller that handles all tasks, the serial port object that send input buffer messages to system, 
queue to send message objects storing input buffers, and the devices object to ensure that there is a usb connection between the display controller and the system controller.
