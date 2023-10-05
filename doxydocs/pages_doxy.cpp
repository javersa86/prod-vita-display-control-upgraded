//Module for pages

/**
 * @ingroup pagesModule
 * @defgroup homePagesModule Home Pages
 * @{
 * @brief The home pages where the all activity takes place.
 * @details
 *
 * ## Home Pages and Main Window
 *
 * The Main Window is the basis for where all the activity from the Graphical User Interface, including the different menus and popups, take place.
 * When user powers on the device, the startup page will be displayed to load the main window. After loading page is cleared,
 * the home page will include the following:
 * - \htmlonly PIP \endhtmlonly and SP Line Graph
 *   - A line graph used to display the measured value for Peak Inspiratory Pressure (Red Line) and Stacking Pressure (Blue Line) as visual indicator
 *     for the amount of oxygen and air is being push into the patient.
 *   - The graph will continue to be updated while system is ventilating or not.
 * - Pneumatic Settings Adjustment Buttons
 *   - The Home Page displays all critical information required by the user for proper operation through the buttons.
 *   - Buttons used to push the pages used to adjust all 8 pneumatic settings.
 *   - The buttons will also display the set values, the value indicator within the settings range, the minimum value, and the maximum value.
 *   - When the system is ventilating, measured values will be displayed on the \htmlonly PIP\endhtmlonly, SP, O<sub>2</sub>, and Aux Flow.
 *   - For the \htmlonly PIP \endhtmlonly Button, lock icon will be displayed to indicate that the \htmlonly PIP \endhtmlonly Disconnection Mode is active.
 *   - For the \htmlonly Humidity \endhtmlonly Button, when humidity split mode is enabled, the two set values for humidity on the Jet and Auxiliary Lines will be displayed.
 *   - For the Oxygen Button, a spinner icon will surround the measured value until the value is adjusted to the set value, and reappear if measured value increases or decreases from set value.
 *   - Different colors will be displayed on buttons based on different criterias:
 *     - For the \htmlonly PIP \endhtmlonly Button, red will be displayed on the set value, measured value, minimum value, maximum value, and value indicator to match the color for the red line on the graph.
 *     - For the SP Button, blue will be displayed on the set value, measured value, minimum value, maximum value, and value indicator to match the color for the blue line on the graph.
 *     - For the Driving Pressure, \htmlonly Rate\endhtmlonly, and Inspiratory Buttons, the borders surronding the buttons will be displayed in orange.
 *     - For the Oxygen Button, the borders, set value, measured value, minimum value, maximum value, and value indicator will be displayed in yellow or green based on which Limited O<sub>2</sub> warning is displayed on the warning banner.
 *   - Statistical Displays for the MAP, TV, and MV values.
 *   - The End-Tidal Button to initiate or stop the End-Tidal Procedure.
 *   - Progress Timer Icon and Text for the counted number of time from start up or from the most recent End-Tidal Sequence.
 *   - Mode Switches for Limited O<sub>2</sub> Mode and Manual Mode.
 *   - Help Buttons with Titles for End-Tidal Mode, Limited O<sub>2</sub> Mode, and Manual Mode.
 * - The following will be display on most of the pages:
 *   - The \htmlonly Warning \endhtmlonly Banner to display all active warnings.
 *   - The Hamburger Menu and Button to open the navigation menu.
 *
 * @file HomeWindow.qml
 * @brief This is the main page where all activity is taking place and where all pages and popup windows are pushed from.
 * @details
 * The following objects will be available to most of the pushed pages from home window:
 * - Home Icon: Icon on the top right corner of the screen where by pressing down, will return the user back to the Single Jet Adjustment Page.
 * - \htmlonly Warning \endhtmlonly Banner: Displays all active alarms on the system at the top of the screen.
 * - Hamburger Menu and Icon - Pressing down on icon at the top left of the screen will show hidden navigational menu for more options.
 * @see main
 *
 * @file StartUpProgressPage.qml
 * @brief The start up page loads up until the start sequence is complete.
 *
 * @file SingleJet.qml
 * @brief This page is pushed after start up and will be the bulk of where medical activity is taken place.
 * @details
 * The medical professional will be able to adust settings and examine the live reading from the system in different boxes and the graph.
 * - Graph: Displays the current readings for Peak Inspiratory Pressure and Stacking Pressure on a line graph.
 * - Pneumatic Icons: Displays the measured and set values for each pneumatic setting and pressing down on one will push up adjustment pages.
 * - Statistical Displays: Displays the measured values for MAP, TV, and MV.
 * - ETCO<sub>2</sub> Button: Pushing down on button will trigger the ETCO<sub>2</sub> Procedure.
 * - ETCO<sub>2</sub> Timer: Displays the elapse time since the last triggered ETCO2<sub>2</sub> Procedure.
 * - Mode Switches: Pushing down will trigger Limited O<sub>2</sub> Mode and Manual Mode.
 * - Help Icons: Pushing down pushes up Help Descriptions for ETCO<sub>2</sub>, Limited O<sub>2</sub>, and Manual.
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup pneumaticSettingPagesModule Pneumatic Settings Adjustment Pages
 * @{
 * @brief The following pages are used to adjust pneumatic settings.
 * @details
 *
 * ## Pneumatic Settings Adjustment Pages
 *
 * The Pneumatic Settings are utilized to create ventilation states based on what is required for the patient, and can be adjusted to different states and values.
 *
 * ## Pneumatic Settings
 *
 * Pneumatic Settings that can be adjusted include the following:
 * - Driving Pressure
 * - \htmlonly Rate \endhtmlonly
 * - Inspiratory Time
 * - Stacking Pressure
 * - Oxygen Concentration
 * - Peak Inspiratory Pressure
 * - Auxiliary Flow
 * - \htmlonly Humidity \endhtmlonly (Consists of 2 Pneumatic Settings to adjust):
 *   - \htmlonly Humidity \endhtmlonly on the Jet Line
 *   - \htmlonly Humidity \endhtmlonly on the Auxiliary line
 *
 * ## Dial and Keypads
 *
 * For the adjustment pages related to the pneumatic settings, the user has the option to switch between two adjustment pages:
 * - <b>Dial Page:</b> When the user opens the dial page, the encoder knob will be enabled, which will be the only tool to increase or decrease the setting.
 * - <b>Keypad Page:</b> Subpage utilized for direct inputs onto the GUI to enter specific values to pneumatic settings. The encoder knob is also enabled on subpage to increase or decrease setting.
 *
 * ## Saving or Cancelling Settings
 *
 * To save the pneumatic settings, the user can press down on the knob or press the save button available on the page. If user doesn't want to set the new pneumatic settings value, the user can exit the page with the cancel button.
 *
 * ## Confirmation Popup Window
 * If a warning threshold exists for a pneumatic setting, then a confirmation popup window will be displayed if set value is greater than or equal to warning threshold. The \htmlonly Warning \endhtmlonly Threshold is uded for the following Pneumatic Settings:
 * - Peak Inspiratory Pressure
 * - Stacking Pressure
 * - Inspiratory Time
 *
 * ## Help Descriptions
 *
 * The following are help descriptions available on the popup windows of the Help Icons from the Adjustment Pages:
 *
 * <table>
 *  <tr>
 *      <th>Pneumatic Settings</th>
 *      <th>Help Descriptions</th>
 *  </tr>
 *  <tr>
 *      <td>Driving Pressure</td>
 *      <td>Driving Pressure indicates the desired pressure to be supplied from the NVENT Vita. This applied pressure increases or decreases respiratory flow causing an effect on TV/MV (i.e. ventilation). The Driving Pressure may be adjusted by the user to achieve better lung recruitment and compensate for lung compliance.</td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly Rate \endhtmlonly</td>
 *      <td>The Respiratory \htmlonly Rate \endhtmlonly setting, measured in Breaths Per Minute (BPM), adjusts the rate at which breaths are supplied to the patient.</td>
 *  </tr>
 *  <tr>
 *      <td>Inspiratory Time</td>
 *      <td>The Inspiratory Time is the percentage of time during the breath cycle in which critical gases are delivered to the patient.</td>
 *  </tr>
 *  <tr>
 *      <td>Stacking Pressure</td>
 *      <td>Stacking Pressure (SP) refers to the residual pressure in the airway as measured through the Blue Jet Line approximately 1 ms prior to each inspiratory phase beginning. This is similar to End Expiratory Pressure (EEP) (i.e. closed system ventilation) in critical care ventilators.<br><br>The VITA  will graphically display the measured Stacking Pressure on the main screen with a blue trace. The Blue graph lines can be hidden for the the Stacking Pressure from within settings. The set limit for SP is represented on the graph with a blue dashed line.<br><br>The operator can set the Stacking Pressure threshold from 1-100 cmH<sub>2</sub>O. The measured value must fall below the set threshold on each breath cycle, indicating that there is adequate egress to the flow of air exiting the patient (i.e. no stacking of breaths). Otherwise, the NVENT Vita immediately alerts the operator and restricts ventilation until the measured Stacking Pressure value drops to 30% of the set Stacking Pressure threshold.</td>
 *  </tr>
 *  <tr>
 *      <td>Oxygen</td>
 *      <td>The NVENT Vita is able to proportionally control the concentration of oxygen being delivered to the patient based on desired operator settings. The NVENT VITA performs an automatic O<sub>2</sub> calibration of the oxygen sensor 3 minutes after powering the device on. An automatic secondary O<sub>2</sub> calibration will be performed 10 mins after the device is powered on to ensure proper operation. Calibration can also be performed by the user manually, or it will occur automatically once every 24 hours the unit is powered on. The oxygen concentration can be set in 1% increments from  21% to 100%. The Oxygen setpoint will be delivered on both the Jet Line and the Auxiliary Line.</td>
 *  </tr>
 *  <tr>
 *      <td>Peak Inspiratory Pressure</td>
 *      <td>The Peak Inspiratory Pressure (\htmlonly PIP \endhtmlonly) measures continuously and is the highest pressure measured during the respiratory cycle and is an indication of both the resistance of the airways and the compliance of the patient. This pressure is measured on the Red \htmlonly PIP \endhtmlonly Line.<br><br>The VITA measures the \htmlonly PIP \endhtmlonly regularly and graphically displays the waveform measured on the main screen with a Red trace. The set limit for \htmlonly PIP \endhtmlonly is represented on the graph with a red dashed line.<br><br>The operator can set the \htmlonly PIP \endhtmlonly threshold from 0-100 cmH<sub>2</sub>O. If the measured \htmlonly PIP \endhtmlonly value meets the set threshold at any point during a breath cycle, the operator is immediately alerted and the Vita restricts ventilation until the measured \htmlonly PIP \endhtmlonly value drops to 30% of the set Peak Inspiratory Pressure threshold.</td>
 *  </tr>
 *  <tr>
 *      <td>Auxiliary Flow</td>
 *      <td>The NVENT Vita includes an auxiliary flow line used for supplemental gas flow where continuous flow is needed. The flow from the AUX port is delivered at the same O<sub>2</sub>% as the Jet 1. This line can also be supplied with humidity.<br>**Note: This line does not have pressure monitoring capabilities.**</td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly Humidity \endhtmlonly</td>
 *      <td>\htmlonly Humidity \endhtmlonly the Jet Line or Auxiliary can be controlled in a unified or separated mode by the operator. \htmlonly Humidity \endhtmlonly should be used whenever jetting time exceeds 30 minutes of continuous use, it is always advantageous to use humidity although not mandatory for shorter procedures. The use of humidity reduces the risk of drying of the tracheal mucosa, it also helps to prevent compliance issues caused by drying of the lungs.  The use of humidity also aids in airway surgery to prevent the tissues from becoming sticky for the surgeon.</td>
 *  </tr>
 * </table>
 *
 * ## Related Topics
 *
 * For some of that adjustment pages, other options will be available:
 * - On the Peak Inspiratory Pressure Adjustment Page, the option to disable \htmlonly PIP \endhtmlonly  Disconnection Mode will be available and will disappear after mode is disabled.
 *
 * ## Addtional Information
 * Information regarding how humidity works differently is available in the following link: @ref humidityAdjustmentModule "Humidity Adjustments"
 *
 *
 *
 * @file InteractiveKnobPage.qml
 * @brief When pushed up, will enable functionality for the encode knob.
 *
 * @file SettingDial.qml
 * @brief Page constructed from Interactive Knob Page. The user adjusts the pneumatic setting with the encoder knob.
 *
 * @file numeric_ui.qml
 * @brief Page constructed from Interactive Knob Page. The user adjust the pneumatic setting with keypad and the encoder knob.
 *
 * @file HighSettingConfirmation.qml
 * @brief Pop Up Window that warns the user for setting adjustment greater than the warning threshold, utilized for SP, PIP, and IT.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * @defgroup humidityAdjustmentModule Humidity Adjustments
 * @{
 * @brief Requires adjustment to the Jet Line and the Auxiliary Line.
 * @details
 *
 * ## Humidity Adjustments
 *
 * There are two Pneumatic Settings for \htmlonly Humidity\endhtmlonly, the \htmlonly Humidity \endhtmlonly on the Jet Line, and the \htmlonly Humidity \endhtmlonly on the Auxiliary Line. There are two modes that the user can switch between to adjust humidity:
 * - Unified Mode: A single dial or keypad will be displayed where the the user adjust \htmlonly Humidity \endhtmlonly on the Jet and Auxiliary lines at the same time and at the same value.
 * - Separated Mode: Two dials or two keypads will be displayed where the user can adjust \htmlonly Humidity \endhtmlonly on the Jet Line and the Auxiliary Line separately. It is important to note that when the user switches to Separated Mode, the default value to adjust from for \htmlonly Humidity \endhtmlonly on the Auxiliary Line is 0.
 *      - Note: when the user pushes down on the encoder knob when adjusting the Auxiliary Line, instead of switching back to adjusting Jet Line, the page will exit back to the home page and save the humidity settings.
 *
 * ## Related Topics
 *
 * The following options will also be available on the page:
 * - The Pump Priming Reset button will be displayed after 3 attempts to prime the jet lines with water.
 * - The Dehumidication Option will allow the user to begin the Dehumidification Procedure.
 *
 * @file HumidityAdjustment.qml
 * @brief Page constructed from Interactive \htmlonly Knob \endhtmlonly Page where the user can switch between unified humidity and seperate humidity.
 *
 * @file HumidityUnifiedDial.qml
 * @brief Page where user adjusts humidity and humidity auxiliary at once with encoder knob.
 *
 * @file HumiditySeparatedDial.qml
 * @brief Page where user adjusts humidity and humidity auxiliary separately with encoder knob.
 *
 * @}
 *
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup presetPagesModule Preset Options
 * @{
 * @brief The following pages allow the user to save pneumatic settings as presets to be implemented later.
 * @details
 * ## Presets
 * Presets are saved pneumatic settings created by medical professional for different purposes and medical procedures. The following will be saved in a preset:
 * - Driving Pressure
 * - \htmlonly Rate \endhtmlonly
 * - Inspiratory Time
 * - Stacking Pressure
 * - Oxygen Concentration
 * - Peak Inspiratory Pressure
 * - Auxiliary Flow
 * - \htmlonly Humidity \endhtmlonly (acting as a unified setting)
 *
 * ## Creating Presets
 * The process of creating presets goes as follows:
 * - The user will select the Create Button to open the Preset Creation Page. The user will be required to enter the user passcode to continue the Preset Creation page.
 * - The default pneumatic settings to adjust from will include:
 *   - Driving Pressure: 20
 *   - \htmlonly Rate \endhtmlonly: 120
 *   - Inspiratory Time: 35
 *   - Stacking Pressure: 24
 *   - Oxygen Concentration: 100
 *   - Peak Inspiratory Pressure: 28
 *   - Auxiliary Flow: 0
 *   - \htmlonly Humidity \endhtmlonly: 0
 * - The Preset Creation page is designed similarly to the Pneumatic Buttons on the Main Window and preset adjustment pages will be pushed from pressing down buttons.
 * - The user will have the option to adjust pneumatic setting with the encoder knob and the keypad.
 * - On the Preset Creation Page, there is an option to press down on the Preset Name, pushing up a keyboard to update and save it.
 * - Pressing the save button will redirect the user back to the Presets Page and a new Preset Icon Button will be displayed.
 *
 * ## Preset Icons
 *
 * After creating presets, Preset Icons will be available with smaller button for the user to implement, edit, or delete presets.
 * The user can save up to 12 presets, where up to 6 Preset Icons will be displayed between the 2 subpages at a time. The values of each pneumatic setting will be displayed on the preset icon.
 *
 * ## Implementing Presets
 *
 * When the user presses down on the main body of the Preset Icon, a confirmation popup window will be displayed. The window will display all
 * pneumatic settings to be implemented and will even indicate what values will change.
 * - If Pneumatic Settings are displayed in orange and include an up arrow icon will indicate that the values are increased.
 * - If Pneumatic Settings are displayed in blue and include a down arrow icon will indicate that the values are decreased.
 * - Pneumatic Settings that remain the same will be displayed in gray.
 *
 * Pressing the confirm button will set all Pneumatic Settings to the system controller. A loading screen will be displayed while the system is implementing Pneumatic Settings.
 *
 * ## Editing Presets
 *
 * The user also has the option to edit previously created presets by pressing down on the Edit Button on the Preset Icon. A page similarly to the
 * Preset Creation Page will be displayed and work the same way. The previously saved Pneumatic Settings and Preset Name will be displayed by default.
 * Accessing page will also require passcode input.
 *
 * ## Deleting Presets
 *
 * The user also has the option to delete presets by pressing down the delete button on the Preset Icon. Passcode input is also required.
 *
 * @file PresetsPage.qml
 * @brief Contains up to 12 presets to be created, edited, deleted, and implemented on the system. Consists two subpages that displays 6 presets a page.
 *
 * @file Pages/PassCode.qml
 * @brief A passcode is required to be inputed before creating, editing, or deleting a preset.
 *
 * @file EditPreset.qml
 * @brief Displays pneumatic icons to push the preset adjustment pages each pneumatic setting. There is also an option to push page to edit preset title.
 *
 * @file PresetNamePopup.qml
 * @brief Keyboard Popup to edit preset title text.
 *
 * @file PresetDial.qml
 * @brief Page constructed from @ref InteractiveKnobPage.qml "Interactive Knob Page". The user adjusts the pneumatic setting with the encoder knob.
 *
 * @file PresetKeypad.qml
 * @brief Page constructed from @ref InteractiveKnobPage.qml "Interactive Knob Page". The user adjusts the pneumatic setting with the keypad and encoder knob.
 *
 * @file ConfirmImplementPreset.qml
 * @brief Pushed from preset icon, popup window that shows updated pneumatic setting before continue with implementation.
 *
 * @file SettingsProgressPage.qml
 * @brief Progress page will be displayed until system confirms that the pneumatic settings were implemented.
 *
 * @file PresetMaxPopup.qml
 * @brief Popup window to be pushed if user tries to create more presets after max 12.
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup jetActiveModule Shutdown Pages
 * @{
 * @brief The following pages relate to a popup window that would be display before the Dehumidifcation Procedure and Shutdown Procedure.
 * @details
 *
 * ## Jet Active Popup Window
 *
 * A Popup window will be displayed based on the different criterias met before Shutting Down or Dehumidifying.
 * - If the Auxiliary Line is Active.
 * - If the Jet and Auxiliary Lines are Active.
 * - If the Manual Mode is Active.
 * - If the Manual Mode and Auxiliary Line is Active.
 *
 * @file JetActiveConfirmation.qml
 * @brief Popup window will be display before the shutdown procedure if system is still ventilating.
 * @}
 */

/**
 * @ingroup jetActiveModule
 * @defgroup dehumidificationModule Dehumidification Pages
 * @{
 * @brief The following pages allow the user to initiate the dehumidification procedure.
 * @details
 *
 * ## Dehumidification
 *
 * Before shutting the system down, it is important for the user to dehumidify the system to ensure the remaining water won't damage or corrode different parts. This is the reason why the option to dehumidify is also available on shutdown and on other pages. Dehumidification should only be required if the \htmlonly Humidity \endhtmlonly percentage is greater than or equal to 30% and water is running through the Jet or Auxiliary Lines.
 * The Dehumdification Procedure will go as followed:
 * - Pressing down on any of the dehumidification options will begin the procedure.
 * - A popup window will be displayed to describe how the procedure will work and how parameter must be met.
 *   - If the system is ventilating, the inputs to continue will be disabled and text will change until ventilation stops.
 * - The next popup will require the user to input a checklist before dehumifiying.
 * - While the system is dehumidifying, the progress page will be displayed where a countdown timer will be displayed for 2 minutes.
 * - After dehumidification is complete, one of two popups will be displayed:
 *   - The "Dehumidication Success Popup"
 *   - The "Dehumidification Failure Popup" where the user as the option to restart dehumidification.
 *
 * @file DehumidificationDisconnection.qml
 * @brief Popup window to begin the dehumidification procedure.
 *
 * @file DehumidificationChecklist.qml
 * @brief Popup window to input checklist to insure that criteria is met before beginning dehumdification.
 *
 * @file DehumidifyingProgressPage.qml
 * @brief A progress page with 2 minute timer will be displayed until dehumidification is complete.
 *
 * @file DehumidificationSuccess.qml
 * @brief Popup window is displayed when dehumidification is completed and was successful.
 *
 * @file DehumidificationFailure.qml
 * @brief Popup window is displayed when dehumidification is completed but failed.
 * @}
 */

/**
 * @ingroup jetActiveModule
 * @defgroup shutdownProcedureModule Shutdown Procedure Pages
 * @{
 * @brief The following pages will be utilized for the Shutdown Procedure.
 * @details
 *
 * ## Shutdown Procedure Popups
 *
 * If the user presses the power button, a popup window will be displayed with options to continue with shutdown or begin dehumidification before shutdown. The system cannot continue to ventilate while shutting down. If the system is still ventilating, all inputs will be disabled. If the user starts ventilating while on the shutdown popup, the options to continue with shutdown or dehumidification will be disabled, and will be enabled once user stops ventilating. After dehumidification (success or failure), the user will have the option to continue with shutdown or not.
 *
 * @file ShutdownConfirmation.qml
 * @brief Popup window to confirm the shutdown of the system from the power button. There is also an option to dehumidify before shutting down.
 *
 * @file ContinueShutdown.qml
 * @brief Popup window will appear after dehumidifying to continue with shutdown.
 *
 * @file ShutdownConfirmation.qml
 * @brief Progress page before system shutdown completely.
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup screenlockModule Screen Lock Mode
 * @{
 * @brief The following pages are utilized for screen lock the display to allow the user to clean screen.
 * @details
 *
 * ## Screen Lock Mode
 *
 * For maintenance purposes, it is important for the screen and buttons to be cleaned, which is why the option to disable the screen and buttons is available to the user. If the system is required to remain running, screen lock mode will be helpful to prevent mis inputs. A Popup Window will be displayed with instructions on how to continue with the cleaning procedure. Continuing will display a transparent overlay over the screen that will prevent the user from pressing any other inputs. If the user presses the screen or the HMI Buttons, the message "Screen lock mode is active. Press the dial to unlock and interact with the screen." will be displayed on screen. Pressing down on the encoder knob will disable Screen Lock Mode and the user will exit from the screen overlay. If touch is detected on the screen or the other HMI Buttons while pressing down on the knob, the message "Moisture detected on panel. Please dry off screen." will be displayed, screen lock will not be disabled.
 *
 * @file ScreenLockConfirmation.qml
 * @brief Popup window to push up the screen lock overlay.
 *
 * @file ScreenLockOverlay.qml
 * @brief Transparent Overlay that fills entire screen to prevent input like pneumatic setting adjustments. Popup window will be displayed if input is triggered. Push down encoder knob to exit out.
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup helpPagesModule Help Pages
 * @{
 * @brief The following pages to contain help info.
 * @details
 *
 * ## Help Boxes
 *
 * If a Help Icon is available, the user will have the option to push up a popup window with a description of how a certain feature works, including the descriptions of Pneumatic Settings, and Op Modes.
 *
 * ## Troubleshooting Boxes
 *
 * For every warning on the warning banner, there is the troubleshooting option to push up the popup window with steps on how to fix the reason for warning.
 *
 * @file HelpBox.qml
 * @brief Popup window to contain information from Help Icon.
 *
 * @file Troubleshoot.qml
 * @brief Popup window to contain information on troubleshooting warning.
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup settingsMenuPagesModule Settings Menu
 * @{
 * @brief The following pages for the Settings Menu.
 * @details
 *
 * ## Settings Menu Options
 *
 * The Setting Menu where the user can access multiple pages where the user can update important aspects of the NVENT-Vita, including the following:
 * - <b>Stacking Pressure:</b> The page where the user can update the visibility for the blue line on the graph.
 * - <b>Limited O<sub>2</sub>:</b> The page where the user can adjust the oxygen concentration for the Limited O<sub>2</sub> Mode.
 * - <b>ETCO<sub>2</sub> Settings:</b> The page where the user can adjust the following Pneumatic Settings for the End-Tidal Procedure:
 *   - ETCO<sub>2</sub> \htmlonly Rate \endhtmlonly
 *   - ETCO<sub>2</sub> Inspiratory Time
 *   - ETCO<sub>2</sub> Number of Breaths
 *   - ETCO<sub>2</sub> Driving Pressure
 * - <b>O<sub>2</sub> Calibration:</b> The page where the user begins the O<sub>2</sub> Calibration Procedure.
 * - <b> \htmlonly PIP \endhtmlonly Disconnection:</b> The page where the user can enable and disable PIP Disconnection Mode.
 * - <b>Brightness and \htmlonly Volume\endhtmlonly:</b> The page where the user can adjust the volume of the alarm and the brightness of the screen.
 * - <b>About:</b> The page that displays important system data.
 *
 * ## Additional Information
 *
 * The following links to the modules that go into detail on the About Page and the Brightness and Volume Page:
 * - @ref volumeAndBrightnessModule "Brightness and Volume Settings"
 * - @ref aboutModule "About Page"
 *
 *
 *
 * @file SettingsPage.qml
 * @brief Page that includes options for Settings Menu.
 *
 * @file StackingPressure.qml
 * @brief Page that allow the user to disable the Stacking Pressure line on the graph.
 *
 * @file LaserO2.qml
 * @brief Page to adjust the Oxygen Concentration for Limited O<sub>2</sub> mode.
 *
 * @file ETCO2Settings.qml
 * @brief Page to adjust the following pneumatic settings for ETCO<sub>2</sub>. Driving pressure, Inspiratory Time, Rate, and Number of Breaths.
 *
 * @file ETCO2Dial.qml
 * @brief Page to adjust individual pneumatic setting with encoder knob enabled dial and keypad.
 *
 * @file Settings/Calibration.qml
 * @brief Page to trigger the O<sub>2</sub> Calibration Procedure.
 *
 * @file Disconnection.qml
 * @brief Page to enable PIP Disconnection Mode.
 *
 *
 *
 *
 * @defgroup volumeAndBrightnessModule Brightness and Volume Settings
 * @{
 * @brief Pages to adjust the brightness and volume.
 * @details
 *
 * ## Brightness and Volume
 *
 * The page includes options that allow the user to switch the dial adjustment page for brightness, and the dial adjustment page for volume.
 *
 * ### Adjusting Brightness
 *
 * Turning the encoder knob will increase or decrease the brightness of the screen and directly communicate with the brightness manager. To save Brightness, user will be required to press down on Save Button or the encoder knob.
 *
 * ### Adjusting Volume
 *
 * Turning the encoder knob will increase or decrease the volume used for the warning alarms. An alarm sound will be made after every turn indicate what the actual volume will sound like. To save \htmlonly Volume\endhtmlonly, user will be required to press down on Save Button or the encoder knob.
 *
 * @file VolumeAndBrightness.qml
 * @brief Page to adjust the brightness of the screen and the volume of the alarm.
 *
 * @file Brightness.qml
 * @brief Sub Page to adjust brightness.
 *
 * @file Volume.qml
 * @brief Sub Page to adjust volume.
 *
 * @}
 *
 *
 *
 * @defgroup aboutModule About Page
 * @{
 *
 * @brief Page contains information about the device.
 * @details
 *
 * ## About Page
 *
 * Page that includes the following information:
 * - Service and Sales Contact Information.
 * - Last and Next Service Dates.
 * - Software Version Numbers for Display, System, and HMI Controller.
 * - Serial Number for the device.
 * - IP Address with option to refresh if device needs to reconnect with ethernet cable.
 * - Option to update preset passcode.
 * - \htmlonly Switch \endhtmlonly digital clock between Daylight Savings Time and Standard Time
 *
 * ## Additional Information
 * Additonal Information for Passcode Pages available in the following link: @ref passcodeModule "Passcode Change"
 *
 * @file About.qml
 * @brief Page where system data is displayed.
 *
 *
 * @defgroup passcodeModule Passcode Change Pages
 * @{
 *
 * @brief Pages to update the passcode used to updating presets.
 * @details
 *
 * ## Passcode Change
 *
 * The passcode store on the system is utilized for adjusting presets. The default passcode will be 0000 and is required to be 4 digits. To change passcodes, the user is required to enter the current passcode first, then the option to change the passcode will become available. Note that the user cannot use the previous passcode for the new one, only the service technician can be able to do that.
 *
 * @file Settings/PassCode.qml
 * @brief Page to enter current passcode before changing it.
 *
 * @file Settings/PassCodeChange.qml
 * @brief Page to enter new passcode.
 *
 * @file Settings/PassCodeConfirm.qml
 * @brief Page to confirm that passcode changed.
 *
 * @}
 *
 * @}
 *
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup serviceMenuPagesModule Service Menu
 * @{
 *
 * @brief The service menu pages will be utilized by service technician.
 * @details
 *
 * ## Service Menu
 *
 * The Service Menu is where only the service technician can access multiple pages where and update important aspects of the NVENT-VITA, including the following:
 * - <b>Demo:</b> The page where the user can enable demo mode on the system, which would disable system warnings for demonstation purposes.
 * - <b>Factory Settings:</b> The page where the user can enable the second jet on the system (if available).
 * - <b>Maintenance:</b> The page that display important system data and where the service technician can update said data.
 * - <b>Components:</b> The page where the service technician can update the part data when replacing parts.
 * - <b>Calibration:</b> The page where the service technician conducts sensor and pressure regulator calibration.
 * - <b>O<sub>2</sub> Calibration:</b> Another page to the service technician begins the O<sub>2</sub> Calibration Procedure. He or she can even adjust oxygen concentration with the encoder knob, see a live feed for the O<sub>2</sub> Calibration Voltage, and see a history of the lowest and highest calibration voltages.
 * - <b>Service Logs:</b> The page where the user can export service logs to a USB Stick.
 * - <b>Passcode:</b> The page where the user can change the user's passcode and the service technician's passcode.
 *
 * @file ServicePage.qml
 * @brief Page that includes options for the Service Menu.
 *
 * @file Demo.qml
 * @brief Page that include option to enable demo mode. Demo Icon will be displayed on home page.
 *
 * @file FactorySettings.qml
 * @brief Page that includes option to switch between single jets and double jets.
 *
 * @defgroup maintenanceModule Maintenance Page
 * @{
 * @brief Page includes information about the device.
 * @details
 *
 * ## Maintenance
 *
 * The page will include the following:
 * - The option to update the contact information for the service company and the sales company. A popup window will be pushed up, which will include a keyboard and text boxes for the following:
 *   - Company Name
 *   - Street
 *   - City/Town
 *   - State
 *   - Postal Code
 *   - Phone Number
 *   - Email / Website
 * - The options to update the date, time, and time zone for the digital clock. A popup window will be pushed up for part of the digital clock to be updated.
 * - The option to update the last and next service dates, popup windows are also constructed from @ref DatePopup.qml "Date Popup Window".
 * - Software Version Numbers for Display, System, and HMI Controller.
 * - Serial Number for the device.
 * - IP Address with option to refresh if device needs to reconnect with ethernet cable.
 *
 * @file Maintenance.qml
 * @brief Page similar to the Settings Menu's About Page, but service technician will be able to update service data.
 *
 * @file ContactPopup.qml
 * @brief Popup window pushed from Maintenance Page to update service and sales contact information.
 *
 * @file DatePopup.qml
 * @brief Popup window to update the month, day and year of the digital clock, as well the last and next service dates.
 *
 * @file UpdateTime.qml
 * @brief Popup window to update hour, month, and time shift of the digital clock.
 *
 * @file UpdateTimeZone.qml
 * @brief Popup window to update the time zone of the digital clock.
 * @}
 *
 * @defgroup componentsModule Components Page
 * @{
 * @brief Pages to manage part information.
 * @details
 *
 * ## Components
 *
 * A table will be displayed with every part that would be replaced on the system. The user can scroll through the every part and columns for each part
 * include the name, serial number, installation date, hours of operation, and hours of ventilation.
 * To begin the replacement procedure, the user must press the "Replace" Option. The borders for the part name entries will be highlighted.
 * Selecting the name for a part will begin the following procedure through popup windows:
 * - The user must confirm that they would like to continue with the replacement process for part selected.
 * - The user must then update the installation date if it is not today.
 * - The user must enter the new serial number (if available) with the pushed up keyboard.
 * - The user must finally confirm replacement, which will reset parts hours of operation and ventilation.
 *
 * @file Components.qml
 * @brief Page to update component information after replacement.
 *
 * @file ComponentsReplaced.qml
 * @brief Popup window pushed from page to begin replacement procedure with the option to update installation date.
 *
 * @file UpdateDateInstalled.qml
 * @brief Popup window to update the installation date of the part.
 *
 * @file ComponentSerialUpdate.qml
 * @brief Popup window pushed from ComponentsReplaced or UpdateDateInstalled to continue with procedure with the option to update serial number.
 *
 * @file SerialNumberPopUp.qml
 * @brief Popup window to update the serial number of the part.
 *
 * @file ComponentsHoursReset.qml
 * @brief Popup window to confirm part replacement, which will reset the parts hours of operation.
 *
 * @}
 *
 * @defgroup calibrationModule Calibration Page
 * @{
 * @brief Pages to manage the multiple calibration procedures.
 * @details
 *
 * ## Service Calibration
 *
 * As the medical professional continues using the device, they need to be ensured that the multiple sensors and
 * pressure regulators are producing the most accurate data for the user.
 *
 * ### Sensors
 *
 * The sensors that need to be calibrated on the page include:
 * - Inlet Air
 * - Inlet O<sub>2</sub>
 * - \htmlonly PIP \endhtmlonly
 * - SP
 *
 * There will also be an option verify sensor calibration.
 *
 * ### Pressure Regulators
 *
 * The pressure regulators that need to be calibrated on the page include:
 * - Driving Pressure Regulator
 *   - Low Calibration: When the DPR valve is closed.
 *   - High Calibration: When the DPR valve is open.
 * - Pressure Regulators
 *   - Air Regulator
 *   - O<sub>2</sub> Regulator
 *
 * ## Inlet Air and Oxygen Zeroing and Verifying
 *
 * Inlet Air and O<sub>2</sub> refers to the pressure produced from the tanks to the system. The system should not see pressure
 * if tanks are not connected or closed. The service technician can conduct calibration by zeroing the measured values for
 * Inlet Air and Inlet O<sub>2</sub>. Through the pop up window for each, the user can zero with the press of the button.
 * A success or failure icon will be displayed based on the results. For the verification,
 * the user will need to manually adjust tanks to ensure that values can produce pressure greater or less than 30.
 * (Separate Calibration tool will be required.)
 *
 * ## PIP and SP Zeroing and Verifying
 *
 * The user should not see values greater than 0 if the system isn’t ventilating. The service technician can conduct calibration
 * by zeroing the measured values for \htmlonly PIP \endhtmlonly and SP. Through the pop up window for each, the user can zero with the press of the
 * button. A success or failure icon will be displayed based on the results. For the verification,
 * the user will need to use a verification tool for manually produce values up to 100.
 *
 * ## Low and High Driving Pressure Regulator Calibration
 *
 * Through the pop up window for low, the user will only need to press a button to calibrate.
 * Previous DPR value will be displayed.
 *
 * Through the same pop up window for high calibration, the user will need to ensure that the live feed for DPR will remain a 45.
 * Precise adjustment for Driving Pressure through the encoder knob may be required. Previous DPR value will be displayed.
 *
 * ## Air and Oxygen Regulator Calibration
 *
 * Through the pop up window for high calibration, the user will need to ensure that the live feed for DPR can hit 48 by
 * pushing down on encoder knob for the Air Regulator or the Oxygen Regulator.
 *
 * @file Service/Calibration.qml
 * @brief Page with multiple options to calibrate sensors and pressure regulators.
 *
 * @file CalibrationSp.qml
 * @brief Page to begin calibration and verification for SP.
 *
 * @file CalibrationPIP.qml
 * @brief Page to begin calibration and verification for \htmlonly PIP \endhtmlonly.
 *
 * @file CalibrationInletAir.qml
 * @brief Page to begin calibration and verification for Inlet Air.
 *
 * @file CalibrationInletO2.qml
 * @brief Page to begin calibration and verification for Inlet O<sub>2</sub>.
 *
 * @file CalibrationDrivingPressure.qml
 * @brief Page to begin calibration procedures for Low Driving Pressure Regulator and High Driving Pressure Regulator.
 *
 * @file CalibrationPreRegulators.qml
 * @brief Page to begin calibration procedures for Air Regulator and Oxygen Regulator.
 * @}
 *
 * @file O2Calibration.qml
 * @brief Page to trigger the O<sub>2</sub> Calibration Procedure
 * @details Includes other features:
 * - Displays the current and previous lowest and hightest O<sub>2</sub> Calibration voltages.
 * - Displays the live feed for the O<sub>2</sub> Calibration value.
 * - Include a mini dial with encoder knob functionality to adjust the Oxygen Concentration, and in turn adjust the O<sub>2</sub> calibration value.
 *
 * @defgroup exportModule Service Logs Page
 * @{
 * @brief The Pages to manage the exporting of service logs.
 * @details
 *
 * ## Service Logs
 *
 * Upon opening the page, the user will be required to check, mount, and create directories for the USB stick attached to the back of the device.
 * If the USB stick is detected, then the user will be able to open the pop up to export all service logs to the following directories:
 * - NVENT_events
 * - NVENT_warnings
 *
 * Option to reconnect USB stick will be available if failed to connect for th first time.
 *
 * The window will display the progress of each file to the USB stick. To ensure, that no data is lost due to inappropriate removal of stick,
 * the disconnection button will unmount the USB stick.
 *
 * @file ServiceLogs.qml
 * @brief Page to export service logs to USB Drive and show the progress of exporting service logs to USB Drive.
 *
 * @}
 *
 * @defgroup servicePasscodeModule Passcode Change Page
 * @{
 * @brief Pages to change the passcodes.
 * @details
 *
 * ## Service Passcodes
 *
 * The service technician will have the ability to change the passcodes for the user and the service technician. The service technician can even forcefully change the user’s passcode.
 *
 * @file ChangePasscode.qml
 * @brief Page to change the preset passcode and the service passcode.
 *
 * @file Service/PassCode.qml
 * @brief Page to enter current passcode before changing it.
 *
 * @file Service/PassCodeChange.qml
 * @brief Page to enter new passcode.
 *
 * @file Service/PassCodeConfirm.qml
 * @brief Page to confirm that passcode changed.
 *
 * @}
 *
 * @}
 */
