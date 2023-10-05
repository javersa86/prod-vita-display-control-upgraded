//Module for objects

/**
 * @addtogroup customObjectsModule
 * @brief Objects that are utilized for different pages.
 * @{
 * @details
 *
 * # Custom Objects
 *
 * The QML Custom Objects are utilized on multiple pages across the Graphical User Interface. Custom Objects include buttons, switches, keyboards, keypads, icons, page layouts, and even major components to the software.
 *
 * ## Graph
 *
 * The graph is argueble the most important object on the NVENT-Vita, for it displays the measured output for Peak Inspiratory Pressure (RED) and Stacking Pressure (BLUE) in a visual style.
 * The graph will be update every 30 milliseconds with new PIP and SP measured values retrieved from the notifications. There will be two dashed lines that will be displayed. Two dash lines will display
 * the set values for each pneumatic settings. There will also be the solid lines that displays the measured values.
 *
 * ## Navigational Sidebar (Hamburger Menu) and Inputs
 *
 * The navigational sidebar will allow the user to navigate between pages and menus, and push popups for different procedures, including the following:
 * - Home Option to redirect back to Home Page.
 * - Presets Option to open the Presets Page.
 * - Dehumidifying Option to push up the dehumidication popup windows.
 * - Settings Menu Option to push up the Settings Menu.
 * - Screen Lock Procedure Option to push up the popup windows to begin screen lock procedure.
 * - Service Menu to push up passcode input page for Service Menu.
 *
 * Button will push up Sidebar will be available on top left corner.
 *
 * ## Warning Banner
 *
 * The banner that will always be displayed at the top of the screen that will will display all the warnings on the system.
 *
 * Inputs on the warning banner include the following:
 * - <b>\htmlonly Warning \endhtmlonly Flag Icon:</b> Input used to show or hide more than one warning on the warning banner.
 * - <b>\htmlonly Warning \endhtmlonly Silence Button:</b> Button used to silence the alarm for warning on the warning banner.
 * - <b>\htmlonly Warning \endhtmlonly Troubleshoot Button:</b> Button used to push up the popup windows for troubleshooting steps for warnings on the warning banner.
 * - <b>\htmlonly Warning \endhtmlonly Clear Button:</b> Button used to clear warning on warning banner.
 *
 * ## Other Objects
 *
 * Other are also significant to the Graphical User interface:
 * - <b>Checklist Alarm Icon:</b> Changes red to green based on the pressure for verifying values for Inlet Air and Inlet O<sub>2</sub>.
 * - <b>Dial Display:</b> Displays the pneumatic setting value on the adjustment pages.
 * - <b>Dial Display Mini:</b> Mini version of the Dial Display.
 * - <b>Incorrect Passcode Text:</b> Shaky Text animation that flashes when user inputs wrong passcode on passcode pages.
 * - <b>Progress Display:</b> Spinning Icon for the loading screen on startup.
 * - <b>Preset Value Columns:</b> Displays the preset values that will be updated on the Preset Implementation Popup Window.
 * - <b>Preset Progress Display:</b> Spinning Icon for the loading screen on implementing presets.
 * - <b>Measured Value Progress Display:</b> Spinning Icon that surrounds the measured value displayed on the Oxygen Pneumatic Button.
 * - <b>Mini Progress Display:</b> Smaller version of the Spinner Icon
 * - <b>Statistic Display:</b> Displays the calculated values from the notifications.
 * - <b>Time Zone Text:</b> QML Array of Text utilized as options for updating the Time Zone on the digital clock.
 * - <b>Vertical Indicator:</b> Icon that displays the minimum, maximum, and set value between the two for a pneumatic setting.
 *
 * ## Buttons and Other Inputs
 *
 * Mutliple Buttons will trigger different actions from multiple pages. All buttons and inputs will have a press and hold signal where the user will require to push down on screen for at least 50 milliseconds.
 *
 * The following will be available to the user:
 * - <b>Calibrate Button:</b> A green button that will only be used to trigger the following procedures: O<sub>2</sub> Calibration, Sensor Calibration, and Pressure Regulator Calibration.
 * - <b>Calibration Option Button:</b> Button to being calibration procedures from Service Menu.
 * - <b>Cancel Button:</b> Button used cancel certain actions and exit popup windows and pages.
 * - <b>Checklist Item Input:</b> Inputs required to continue to next page or popup window.
 * - <b>Continue Button:</b> Button used proceed with certain actions.
 * - <b>Dial Display Input:</b> For the adjustment pages, pressing down on the dial display icon will switch between the dial and keypad subpages.
 * - <b>End Tidal Button:</b> Button built to trigger or cancel the End Tidal Procedure.
 * - <b>Navigational Sidebar Icon:</b> Icon used to push up navigational sidebar with more option inputs. Icon will always be displayed from the top left of the screen regardless of page.
 * - <b>Help Icons (Labeled and Unlabeled):</b> Icons used to push up the help descriptons for pneumatic settings and OP Modes.
 * - <b>Dial / Keypad Button:</b> Button on adjustment page to switch between dial subpage and keypad subpage.
 * - <b>Menu Buttons:</b> Buttons only used to push up pages and popup windows from the navigation sidebar.
 * - <b>Number and Keyboard Buttons:</b> Buttons used only for keyboards and keypads.
 * - <b>Pneumatic Button:</b> The buttons pushes up the adjustment pages and displays the measured and set values for pneumatic settings.
 * - <b>\htmlonly Humidity \endhtmlonly Button:</b> Functions similarly to the Pneumatic Button, except that it displays the two humidities on the same button when separate humidities mode is enabled.
 * - <b>Preset Button:</b> Composed of multiple inputs to push up popup window to implement preset, and the pages to edit or delete presets.
 * - <b>Save Button:</b> Button used to confirm the update to the pnenumatic settings on adjustment pages.
 * - <b>Start Button:</b> Button used to start Air and O2 Calibration Procedures.
 * - <b>Selectable Dial Input:</b> Utilized on the humdity adjustment pages to track the different set values for the separated humidities and the united humidity.
 * - <b>Setting Options Button:</b> Button used to switch between pages and popup windows on the settings and service menus.
 * - <b>Verify Button:</b> Button used to verify the accuracy measured values for sensor calibration. Confirm State is available.
 *
 * ## Switches
 *
 * Switches work differently from buttons and inputs, in that it does not reset or disappear after input.
 * Mostly utilized for different modes on the display and the system.
 *
 * Switches on the display include the following:
 * - <b>Daylight Saving Time \htmlonly Switch\endhtmlonly:</b> \htmlonly Switch \endhtmlonly used to switch between daylight savings time to standard time.
 * - <b>Line \htmlonly Switch\endhtmlonly:</b> \htmlonly Switch \endhtmlonly used to show and hide the blue lines on the graph.
 * - <b>Mode \htmlonly Switch\endhtmlonly:</b> Switches used to enable or disable different op modes, include Limited O<sub>2</sub>, Manual, and PIP Disconnection.
 *
 * ## Keyboards and Keypads
 *
 * There are multiple virtual keyboards and keypads on the GUI to input text and digits.
 * For clarification, keypads are only used for inputing numbers or digits, while used to input text with multiple character,
 * including numbers.
 *
 * The following keyboards and keypads will be available for different features and in different formats:
 * - <b>Base Keypad (filename keyboard):</b> Built-in keypad used for all keypad adjustment pages on the GUI.
 * - <b>Contact Information:</b>
 *   - Keyboard Buttons and Layouts: QML Objects connected to the contact manager that can be
 *     used to generate and style the rows of buttons used for inputting contact information.
 *   - Contact Information Keyboard: Keyboards generated with different shift states (Uppercase, Lowercase, All Caps, numbers,
 *     and symbols) and can be used to input Company Names,
 *     Street Address, Towns/Cities, States, and email/website.
 *   - Contact Information Keypad: Built in keypad used to input phone and postal code for contact information.
 * - <b>Preset Name Keyboard Buttons and Layouts:</b> QML Objects connected to the preset manager used to generate a keyboard with
 *   different shift states to input the preset's name.
 * - <b>Serial Number Keyboard Buttons and Layouts:</b> QML Objects connected to the part manager used to generate a keyboard to input
 *   a part's serial number.
 * - <b>Date and Time:</b>
 *   - Date Keypad: Built-in keypad used to input date.
 *   - PassCode Keypad: Built-in Keypads used for the PassCode pages.
 *
 * ## Page Layouts
 *
 * Page layouts include:
 * - <b>Adjustment Keypad:</b> The virtual representation for the keypad on the adjustment pages that will include the following
 *   objects and will have encoder knob functionality:
 *   - Base Keypad
 *   - Outside Range Indicator: Displayed when user inputs incorrect value.
 *   - Vertical indicator
 * - <b>Generic Dial:</b> The virtual representation for the dial on the adjustment pages that include the following objects and will
 *   have encoder knob functionality to all layouts:
 *   - Dial Display: Input that displays the Pneumatic Settings set value.
 *   - Help Icon
 *   - Vertical Indicator
 *   - Cancel Button
 *   - Save Button
 *   - Keypad Button: Switches to keypad layout page.
 *   - \htmlonly PIP \endhtmlonly Disconnection Button: Only available on the \htmlonly PIP \endhtmlonly Adjustment Page, and allows the user to disable \htmlonly PIP \endhtmlonly Disconnection Mode.
 * - <b>Generic Dial Mini:</b> Smaller version of the Generic Dial with no cancel, save, keypad, or help icon buttons. Only available on Service Menu O<sub>2</sub> Calibration page.
 * - <b>Mode Setting Dial:</b> Used similarly to Generic Dial, but used for Pneumatic Settings related to Op Modes and include the following:
 *   - Dial Display
 *   - Vertical Indicator
 * - <b>Mode Setting Keypad:</b> Used similary to Adjustment Keypad and is even built around it.
 * - <b>Sliding Box Popup Window:</b> A popup window where it slides down from the top of the screen to the center.
 *   The following popup windows are built from the layout:
 *   - Preset Implementation Confirm Popup Window
 *   - Dehumidification Popup Window
 *   - Helpbox Popup Window
 *   - High Setting Confirmation Windows
 *   - Sensor Calibration Windows
 *   - Service Exporting Windows
 * - <b>Reverse Sliding Box Popup Window:</b> A popup window where it slides up from the bottom of the screen to the center. The popup windows are built from keyboard and keypad layouts.
 * - <b>Mode \htmlonly Switch \endhtmlonly Confirmation Popup Window:</b> Popup Window displayed to continue the process of enabling the following Op Modes:
 *   - ETCO<sub>2</sub> Mode
 *   - Limited O<sub>2</sub> Mode
 *   - Manual Mode
 *
 * @file ContactKeyboard/ContactKeyboardButton.qml
 * @brief Button used for keyboard to enter contact information.
 *
 * @file ContactKeyboard/ContactKeyboardLayout.qml
 * @brief Layout used for different state of keyboard used to enter contact information.
 *
 * @file ContactKeyboard/GeneralContactKeyboard.qml
 * @brief Keyboard used to enter contact information.
 *
 * @file ContactKeyboard/GeneralContactKeypad.qml
 * @brief Keypad used to enter contact information.
 *
 * @file Keyboard/KeyboardButton.qml
 * @brief Button used for keyboard.
 *
 * @file Keyboard/KeyboardLayout.qml
 * @brief Layout for keyboard.
 *
 * @file Keyboard/SerialNumberKeyboardButton.qml
 * @brief Button used for keyboard to enter component's serial number.
 *
 * @file Keyboard/SerialNumberKeyboardLayout.qml
 * @brief Layout used for keyboard to enter component's serial number.
 *
 * @file AdjustmentKeypad.qml
 * @brief Keypad used to adjust pneumatic settings.
 *
 * @file CalibrateButton.qml
 * @brief Button used to initiate calibration, including Sensors, Pressure Regulators, and O2 Calibration.
 *
 * @file CalibrationOptionsButton.qml
 * @brief Button used to begin calibration procedures.
 *
 * @file CancelButton.qml
 * @brief Button used to exit back to previous page.
 *
 * @file CheckListAlarm.qml
 * @brief Icon displayed green or red if criteria is met for calibration procedure.
 *
 * @file CheckListItem.qml
 * @brief Icon used for checklist items on calibration pages.
 *
 * @file ContinueButton.qml
 * @brief Button used to for complete activity on page.
 *
 * @file DateDayPad.qml
 * @brief Keypad used to input the day for date.
 *
 * @file DateFebruaryDayPad.qml
 * @brief Keypad used to input the day for date during February.
 *
 * @file DateFebruaryLeapDayPad.qml
 * @brief Keypad used to input the day for date during February while during a Leap Year.
 *
 * @file DateMonthPad.qml
 * @brief Keypad used to input the month for date.
 *
 * @file DateOtherDayPad.qml
 * @brief Keypad used to input the day for date. The month would only have 30 days.
 *
 * @file DateYearPad.qml
 * @brief Keypad used to input the year for date.
 *
 * @file DialButton.qml
 * @brief Button used to switch between unified and seperate humidity on humidity adjustment page, or used to switch from keypad to dial on ETCO<sub>2</sub> adjustment page.
 *
 * @file DialDisplay.qml
 * @brief Icon large used to display the setting value and unit on the adjustment page. Contains input signal as well.
 *
 * @file EndTidalButton.qml
 * @brief Button used to initiate the ETCO<sub>2</sub> procedure.
 *
 * @file GenericDial.qml
 * @brief Layout used for adjustment pages to display the following: the title, the help icon, the dial display, Vertical Indicator, Cancel Button, Save Button, and Keypad Button. A PIP Disconnection Button will be available on PIP Adjustment Page.
 *
 * @file GenericDialMini.qml
 * @brief A smaller version of the Generic Dial used for the O<sub>2</sub> Calibration Page.
 *
 * @file Graph.qml
 * @brief Graph used on the home page to display the PIP and SP.
 *
 * @file HamburgerButton.qml
 * @brief Button used to push up the navigational menu.
 *
 * @file HamburgerMenu.qml
 * @brief Menu used to navigate to the follow pages and popups, Home, Presets, Dehumidification, Settings Menu, Screen Lock, and Service Menu.
 *
 * @file HelpIcon.qml
 * @brief Icon used to display the help description.
 *
 * @file HelpIconLabeled.qml
 * @brief Icon used to display the help description and title. Used to for mode buttons on home page.
 *
 * @file HumidityIcon.qml
 * @brief A Pneumatic Icon that will display the humdity on the jet line and the auxiliary line in seperate mode. Constructed from pneumatic icon object.
 *
 * @file IncorrectPassCode.qml
 * @brief Text used for incorrect passcode input with shaking effect.
 *
 * @file Keyboard.qml
 * @brief Keypad with buttons used for the Adjustment Keypad on adjustment pages.
 *
 * @file KeypadButton.qml
 * @brief Button used to switch dial to keypad on ETCO<sub>2</sub> Adjustment pages.
 *
 * @file LineButton.qml
 * @brief Switch used to show or hide the blue line on the graph.
 *
 * @file MenuButton.qml
 * @brief Button used as an option for the navigational menu.
 *
 * @file ModeSettingDial.qml
 * @brief Dial Adjustment Page for adjusting the settings related to modes, such as ETCO<sub>2</sub> settings and Laser-Safe.
 *
 * @file ModeSettingKeypad.qml
 * @brief Dial Adjustment Page for adjusting the settings related to modes.
 *
 * @file ModeSwitch.qml
 * @brief Switch used to enable and diable modes.
 *
 * @file NumberButton.qml
 * @brief Button used for keypads.
 *
 * @file PassCodeKeypad.qml
 * @brief Keypad used for passcode pages.
 *
 * @file PneumaticButton.qml
 * @brief Button used to push up adjustment pages and to display the set and measured values for the pneumatic settings.
 *
 * @file PresetIcon.qml
 * @brief Icon used used to display preset values, and push up pages to edit, delete, and implement presets.
 *
 * @file PresetProgressDisplay.qml
 * @brief Spinner Icon used on the Preset Implementation Progress page.
 *
 * @file ProgressDisplay.qml
 * @brief Spinner Icon used for the start up and shutdown progress pages.
 *
 * @file ProgressDisplayMeasureValue.qml
 * @brief Spinner Icon that surround measured value for oxygen concentration on pneumatic button.
 *
 * @file SaveButton.qml
 * @brief Button used to save and confirm pneumatic setting from adjustment pages.
 *
 * @file SelectableDial.qml
 * @brief Dial Icon used for the humidity adjustment pages.
 *
 * @file SettingOptionsButton.qml
 * @brief Button used for menu options and for multiple purposes for different modes.
 *
 * @file SlidingBox.qml
 * @brief Popup window that appears from top of the screen.
 *
 * @file SlidingBoxReversed.qml
 * @brief Popup window that appears from bottom of the screen.
 *
 * @file StatisticDisplay.qml
 * @brief Displays the measured values for MAP, TV, and MV.
 *
 * @file TimeZoneText.qml
 * @brief Text array storing existing time zone to update the digital clock.
 *
 * @file VerifyButton.qml
 * @brief Button used to confirm that caribration values are accurate on verification pages.
 *
 * @file VerticalIndicator.qml
 * @brief Bar icon to display the set value between the minimum and maximum values.
 *
 * @file WarningBanner.qml
 * @brief Large banner icon at the top of the screen to display all warnings and alarms triggered in the system.
 *
 * @file WarningBannerAlarmIcon.qml
 * @brief Icon that displays one alarm. Pushing down shows and hides up to 3 warnings at once.
 *
 * @file WarningBannerAlarmIcons.qml
 * @brief Icon that displays the number of different alarms. Pushing down shows and hides up to 3 warnings at once.
 *
 * @file WarningBannerModel.qml
 * @brief Layout for each warning on the warning banner, which includes title, color, and built-in troubleshoot and silence buttons.
 * @}
 */
