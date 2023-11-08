\mainpage Display Overview
\tableofcontents

This page is the main introduction page that will outline all major design parameters for the display controller. \n\n

This manual is divided in the following sections:
1. \subpage introduction "Introduction" <br>
        &emsp;1.1 \subpage introduction_background "Background" <br>
        &emsp;1.2 \subpage introduction_tech_used "Technologies Used" <br>
        &emsp;1.3 \subpage introduction_directory_structure "Directory Structure" <br>
2. \subpage mainThread   "Threading Architecture" <br>
        &emsp;2.1 \subpage mainThread_definitions "Definitions" <br>
        &emsp;2.2 \subpage mainThread_background "Background" <br>
        &emsp;2.3 \subpage thread_list "List of Threads" <br>
                &emsp;&emsp;2.3.1 \subpage thread1 "API Thread" <br>
                        &emsp;&emsp;&emsp;2.3.1.1 \subpage thread1_background "Background" <br>
                        &emsp;&emsp;&emsp;2.3.1.2 \subpage thread1_sequence "Sequence of Events" <br>
                        &emsp;&emsp;&emsp;2.3.1.3 \subpage thread1_references "Module References" <br>
                &emsp;&emsp;2.3.2 \subpage thread2 "Encoder Knob Thread" <br>
                        &emsp;&emsp;&emsp;2.3.2.1 \subpage thread2_background "Background" <br>
                        &emsp;&emsp;&emsp;2.3.2.2 \subpage thread2_sequence "Sequence of Events" <br>
                        &emsp;&emsp;&emsp;2.3.2.3 \subpage thread2_references "Module References" <br>
3. \subpage modules "Modules" <br>
        &emsp;3.1 \subpage moduleDefinitions "Definitions" <br>
        &emsp;3.2 \subpage main "Main Application" <br>
        &emsp;3.3 \subpage frontendModule "Frontend Module (GUI)" <br>
                &emsp;&emsp;3.3.1 \subpage frontendModule_background "GUI Background" <br>
                &emsp;&emsp;3.3.2 \subpage frontendModule_technologies "GUI Technologies Used" <br>
                &emsp;&emsp;3.3.3 \subpage frontendModule_directory "GUI Directory Structure" <br>
                &emsp;&emsp;3.3.4 \subpage frontendModule_page_description "Page Description" <br>
                &emsp;&emsp;3.3.5 \subpage frontendModule_page_stacks "Page StackViews" <br>
                &emsp;&emsp;3.3.6 \subpage pagesModule "Pages" <br>
                        &emsp;&emsp;&emsp;3.3.6.1 \subpage homePagesModule "Main Window and its Related Pages" <br>
                        &emsp;&emsp;&emsp;3.3.6.2 \subpage pneumaticSettingPagesModule "Pneumatic Settings Adjustment Pages" <br>
                        &emsp;&emsp;&emsp;3.3.6.3 \subpage humidityAdjustmentModule "Humidity Adjustment Page" <br>
                        &emsp;&emsp;&emsp;3.3.6.4 \subpage presetPagesModule "Preset Options" <br>
                        &emsp;&emsp;&emsp;3.3.6.5 \subpage jetActiveModule "Shutdown and Dehumidification Pages" <br>
                        &emsp;&emsp;&emsp;3.3.6.6 \subpage screenlockModule "Screen Lock Mode" <br>
                        &emsp;&emsp;&emsp;3.3.6.7 \subpage helpPagesModule "Help Pages" <br>
                        &emsp;&emsp;&emsp;3.3.6.8 \subpage troubleshootingPagesModule "Troubleshooting Steps" <br>
                        &emsp;&emsp;&emsp;3.3.6.9 \subpage settingsMenuPagesModule "Settings Menu" <br>
                        &emsp;&emsp;&emsp;3.3.6.10 \subpage serviceMenuPagesModule "Service Menu" <br>
                &emsp;&emsp;3.3.7 \subpage customObjectsModule "Custom Objects" <br>
                        &emsp;&emsp;&emsp;3.3.7.1 \subpage customObjectsGraph "Graph" <br>
                        &emsp;&emsp;&emsp;3.3.7.2 \subpage customObjectsNavigation "Navigational Sidebar and Inputs" <br>
                        &emsp;&emsp;&emsp;3.3.7.3 \subpage customObjectsModule "Warning Banner" <br>
                        &emsp;&emsp;&emsp;3.3.7.4 \subpage customObjectsOtherObjects "Other Objects" <br>
                        &emsp;&emsp;&emsp;3.3.7.5 \subpage customObjectsInputs "Buttons and Other Inputs" <br>
                        &emsp;&emsp;&emsp;3.3.7.6 \subpage customObjectsSwitches "Switches" <br>
                        &emsp;&emsp;&emsp;3.3.7.7 \subpage customObjectsKeyboards "Keyboards and Keypads" <br>
                        &emsp;&emsp;&emsp;3.3.7.8 \subpage customObjectsLayouts "Page Layouts" <br>
                &emsp;&emsp;3.3.8 \subpage stylingModule "Styling" <br>
                &emsp;&emsp;3.3.9 \subpage iconographyModule "Iconography" <br>
        &emsp;3.4 \subpage 
                
        
        




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

<b>Thread</b> - A sequence of software code the application must execute.f

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






<!--- Frontend -->

@defgroup frontendModule Frontend Module (GUI)
@brief Documentation for all QML files.
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




<!-- Backend -->

@defgroup backendModule Backend Module (Backend Controller)
@brief Documentation for backend functions and features.
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





<!-- API -->

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
