//Module for pages

/**
 * @ingroup pagesModule
 * @defgroup homePagesModule Main Window and its Related Pages
 * @{
 * @brief The home pages where the all activity takes place.
 * @details
 *
 * \section homePagesModule Main Window and its Related Pages
 *
 * The <b>Main Window/Home Page</b> is the basis for where all the activity from the Graphical User Interface, including the different menus and popups, take place. When the user powers on the device, the startup page will be displayed to load the main window. After the loading page is cleared, the home page will include different features.<br>
 *
 * The Home Page displays all critical information required by the user for proper operation through <b>Pneumatic Buttons</b>. These buttons are used to push pages used to adjust all 8 pneumatic settings. They will also display the set values, the value indicator within the settings range, the minimum value, and the maximum value. Further details on how pneumatic settings are adjusted, see @ref pneumaticSettingPagesModule "Pneumatic Settigns Adjustment Pages."<br>
 *
 * When the system is ventilating, measurements received from the <b>Notifications</b> will be displayed on the home page. The set values on the Pneumatic Buttons for \htmlonly <b>PIP</b>, \endhtmlonly <b>SP</b>, <b>O<sub>2</sub></b>, and <b>Auxiliary Flow</b> will be replaced, and the <b>Statistical Displays</b> will show <b>MAP</b> and <b>TV</b>. Another Statical Display will show <b>MV</b>, which is converted from TV. <br>
 *
 * The \htmlonly <b>PIP and SP Line Graph</b> \endhtmlonly is a line graph used to display the measured value for <b>Peak Inspiratory Pressure</b> (Red Line) and <b>Stacking Pressure</b> (Blue Line) as a visual indicator for the amount of oxygen and air being pushed into the patient. The graph will continue to be updated while the system is ventilating or not; see @ref customObjectsModule "Graph." <br>
 *
 * For the <b>Oxygen Button</b>, a spinner icon will surround the measured value until the value is adjusted to the set value, and reappear if the measured value increases or decreases from the set value. <br>
 *
 * For the \htmlonly <b>PIP Button</b>, \endhtmlonly lock icon will be displayed to indicate that the \htmlonly <b>PIP Disconnection Mode</b> \endhtmlonly is active.<br>
 *
 * For the \htmlonly <b>Humidity Button</b>, \endhtmlonly when humidity split mode is enabled, the two set values for humidity on the Jet and Auxiliary Lines will be displayed. for more information on separate humidities, @ref humidityAdjustmentModule "Humidity Adjustment Page." <br>
 *
 * Different colors will be displayed on buttons based on different criterias:
 * - For the \htmlonly PIP \endhtmlonly Button, red will be displayed on the set value, measured value, minimum value, maximum value, and value indicator to match the color for the red line on the graph.
 * - For the SP Button, blue will be displayed on the set value, measured value, minimum value, maximum value, and value indicator to match the color for the blue line on the graph.
 * - For the Driving Pressure, \htmlonly Rate \endhtmlonly, and Inspiratory Buttons, the borders surrounding the buttons will be displayed in orange during <b>End-Tidal Mode</b>.
 * - For the Oxygen Button, the borders, set value, measured value, minimum value, maximum value, and value indicator will be displayed in yellow or green based on which <b>Limited O<sub>2</sub></b> warning is displayed on the warning banner.
 *
 * The <b>End-Tidal Button</b> will initiate or stop the End-Tidal Procedure. <br>
 *
 * The Progress Timer Icon and Text for the counted number of time from startup or from the most recent End-Tidal Sequence. <br>
 *
 * The <b>Mode Switches</b> will be used to enable or disable for Limited O<sub>2</sub> Mode and Manual Mode. <b>Note: a confirmation message will be displayed to confirm the enabling of End-Tidal, Limited O<sub>2</sub>, and Manual.</b><br>
 *
 * The <b>Help Buttons</b> with Titles will push up descriptions for End-Tidal Mode, Limited O<sub>2</sub> Mode, and Manual Mode.<br>
 *
 * The following are objects on the homepage that will also be available on the other pages: the \htmlonly <b>Warning Banner</b> \endhtmlonly will display all active warnings and the <b>Navigational Sidebar Button</b> will open the navigational menu. See @ref  customObjectsModule "Custom Objects."
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
 * \section pneumaticSettingPagesModule Pneumatic Settings Adjustment Pages
 *
 * The <b>Pneumatic Settings</b> are utilized to create ventilation states based on what is required for the patient, and can be adjusted to different states and values.<br>
 *
 * <b>Pneumatic Settings</b> that can be adjusted include the following: Driving Pressure, \htmlonly Rate,\endhtmlonly Inspiratory Time, Stacking Pressure, Oxygen Concentration, Peak Inspiratory Pressure, Auxiliary Flow, and \htmlonly Humidity. \endhtmlonly <br>
 *
 * For the adjustment pages related to the pneumatic settings, the user has the option to switch between two adjustment pages:
 * - <b>Dial Page:</b> When the user opens the dial page, the encoder knob will be enabled, which will be the only tool to increase or decrease the setting.
 * - <b>Keypad Page:</b> Subpage utilized for direct inputs onto the GUI to enter specific values to pneumatic settings. The encoder knob is also enabled on subpage to increase or decrease settings.
 *
 * To save the pneumatic settings, the user can press down on the knob or press the save button available on the page. If the user doesn't want to set the new pneumatic settings value, the user can exit the page with the cancel button. To see how pneumatic settings are exchanged with the system.<br>
 *
 * If a warning threshold exists for a pneumatic setting, then a confirmation popup window will be displayed if the set value is greater than or equal to the warning threshold. The \htmlonly Warning \endhtmlonly Threshold is used for the following Pneumatic Settings: Peak Inspiratory Pressure, Stacking Pressure, and Inspiratory Time.<br>
 *
 * The user will be restricted to adjusting Auxiliary Flow between 1 and 3. <br>
 *
 * Each adjustment will include a description of the related pneumatic setting: see @ref helpPagesModule "Help Pages." For some of those adjustment pages, other options will be available.<br>
 *
 * On the Peak Inspiratory Pressure Adjustment Page, the option to disable \htmlonly PIP \endhtmlonly Disconnection Mode will be available and will disappear after mode is disabled.<br>
 *
 * Information regarding how humidity works differently is available in the following link: @ref humidityAdjustmentModule "Humidity Adjustments"
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
 * @}
 *
 */

/**
 * @ingroup pagesModule
 * @defgroup humidityAdjustmentModule Humidity Adjustment Page
 * @{
 * @brief Requires adjustment to the Jet Line and the Auxiliary Line.
 * @details
 *
 * \section humidityAdjustmentModule Humidity Adjustment Page
 *
 * For \htmlonly Humidity, \endhtmlonly there are two Pneumatic Settings to adjust: \htmlonly Humidity \endhtmlonly on the Jet Line, and the \htmlonly Humidity \endhtmlonly on the Auxiliary Line. There are two modes that the user can switch between to adjust humidity:
 *
 * - <b>Unified Mode:</b> A single dial or keypad will be displayed where the the user adjust \htmlonly Humidity \endhtmlonly on the Jet and Auxiliary lines at the same time and at the same value.
 *
 * - <b>Separated Mode:</b> Two dials or two keypads will be displayed where the user can adjust \htmlonly Humidity \endhtmlonly on the Jet Line and the Auxiliary Line separately. It is important to note that when the user switches to Separated Mode, the default value to adjust from for \htmlonly Humidity \endhtmlonly on the Auxiliary Line is 0.
 *
 *      - Note: when the user pushes down on the encoder knob when adjusting the Auxiliary Line, instead of switching back to adjusting Jet Line, the page will exit back to the home page and save the humidity settings.
 *
 * Also note, if humidity is adjusted to a value greater than 0, and if no water is detected in the system, the <b>No Water Detected</b> warning will be available in the <b>Warning Banner</b> to pump water into the system.
 *
 * The following options will also be available on the \htmlonly Humidity \endhtmlonly Adjustment Page:
 * - The <b>Pump Priming Reset button </b> will be displayed after 3 attempts to prime the jet lines with water.
 * - The <b>Dehumidication Option </b> will allow the user to begin the Dehumidification Procedure.
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
 */

/**
 * @ingroup pagesModule
 * @defgroup presetPagesModule Preset Options
 * @{
 * @brief The following pages allow the user to save pneumatic settings as presets to be implemented later.
 * @details
 *
 * \section presetPagesModule Preset Options
 *
 * <b>Presets</b> are saved pneumatic settings created by medical professionals for different purposes and medical procedures. Presets can be created, edited, deleted, or implemented to the system through the “Presets” option on the <b>Navigational Sidebar</b>.  The following will be saved in a preset: Driving Pressure, \htmlonly Rate \endhtmlonly, Inspiratory Time, Stacking Pressure, Oxygen Concentration, Peak Inspiratory Pressure, Auxiliary Flow, and \htmlonly Humidity \endhtmlonly (acting as a unified setting).<br>
 *
 * The process of creating presets goes as follows:
 * 1. The user will select the Create Button to open the Preset Creation Page. The user will be required to enter the user passcode to continue the Preset Creation page.
 * 2. The default pneumatic settings to adjust from will include:
 *   - Driving Pressure: 20
 *   - \htmlonly Rate \endhtmlonly: 120
 *   - Inspiratory Time: 35
 *   - Stacking Pressure: 24
 *   - Oxygen Concentration: 100
 *   - Peak Inspiratory Pressure: 28
 *   - Auxiliary Flow: 0
 *   - \htmlonly Humidity \endhtmlonly: 0
 * 3. The Preset Creation page is designed similarly to the Pneumatic Buttons on the Main Window and preset adjustment pages will be pushed from pressing down buttons.
 * 4. The user will have the option to adjust pneumatic setting with the encoder knob and the keypad.
 * 5. On the Preset Creation Page, there is an option to press down on the Preset Name, pushing up a keyboard to update and save it.
 * 6. Pressing the save button will redirect the user back to the Presets Page and a new Preset Icon Button will be displayed.
 *
 * After creating presets, <b> Preset Icons </b> will be available with smaller buttons for the user to implement, edit, or delete presets. The user can save up to 12 presets, where up to 6 Preset Icons will be displayed between the 2 subpages at a time. The values of each pneumatic setting will be displayed on the preset icon.<br>
 *
 * When the user presses down on the main body of the Preset Icon, a confirmation popup window will be displayed. The window will display all pneumatic settings to be implemented and will even indicate what values will change.
 * - If Pneumatic Settings are displayed in orange and include an up arrow icon will indicate that the values are increased.
 * - If Pneumatic Settings are displayed in blue and include a down arrow icon will indicate that the values are decreased.
 * - Pneumatic Settings that remain the same will be displayed in gray.
 *
 * Pressing the confirm button will set all Pneumatic Settings to the system controller. A loading screen will be displayed while the system is implementing Pneumatic Settings. If ventilation is active on the Jet or Auxiliary line, confirming the Preset implementation will be disabled with the message: "Stop Ventilating to Implement a Preset". <br>
 *
 * The user also has the option to edit previously created presets by pressing down on the <b>Edit Button</b> on the <b>Preset Icon</b>. A page similarly to the Preset Creation Page will be displayed and work the same way. The previously saved Pneumatic Settings and Preset Name will be displayed by default. Accessing the page will also require passcode input.<br>
 *
 * The user also has the option to delete presets by pressing down the delete button on the <b>Preset Icon</b>. Passcode input is also required.
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
 * @defgroup jetActiveModule Shutdown and Dehumidification Pages
 * @{
 * @brief The following pages relate to a popup window that would be display before the Dehumidifcation Procedure and Shutdown Procedure.
 * @details
 *
 * \section jetActiveModule Shutdown and Dehumidification Pages
 *
 * A Popup window will be displayed based on the different criterias met before Shutting Down or Dehumidifying.
 * - If the Auxiliary Line is Active.
 * - If the Jet and Auxiliary Lines are Active.
 * - If the Manual Mode is Active.
 * - If the Manual Mode and Auxiliary Line is Active.
 *
 * For the <b>Dehumidification Procedure,</b> and before shutting the system down, it is important for the user to dehumidify the system to ensure the remaining water won't damage or corrode different parts. This is the reason why the option to dehumidify is also available on the <b>Shutdown Procedure Popups</b>, the <b>Navigational Sidebar</b>, and the <b>Humidity Adjustment Page</b>. <b>Dehumidification</b> should only be required if the \htmlonly Humidity \endhtmlonly percentage is greater than or equal to 30% and water is running through the Jet or Auxiliary Lines.
 *
 * The Dehumdification Procedure will go as followed:
 * 1. Pressing down on any of the dehumidification options will begin the procedure.
 * 2. A popup window will be displayed to describe how the procedure will work and how parameters must be met.
 *   - If the system is ventilating, the inputs to continue will be disabled and text will change until ventilation stops.
 * 3. The next popup will require the user to input a checklist before dehumifiying.
 * 4. While the system is dehumidifying, the progress page will be displayed where a countdown timer will be displayed for 2 minutes.
 * 5. After dehumidification is complete, one of two popups will be displayed:
 *   - The "Dehumidication Success Popup"
 *   - The "Dehumidification Failure Popup" where the user as the option to restart dehumidification.
 *
 * For the <b>Shutdown Procedure Popups,</b> if the user presses the power button, a popup window will be displayed with options to continue with shutdown or begin dehumidification before shutdown. The system cannot continue to ventilate while shutting down. If the system is still ventilating, all inputs will be disabled. If the user starts ventilating while on the shutdown popup, the options to continue with shutdown or dehumidification will be disabled, and will be enabled once user stops ventilating. After dehumidification (success or failure), the user will have the option to continue with shutdown or not.
 *
 * @file JetActiveConfirmation.qml
 * @brief Popup window will be display before the shutdown procedure if system is still ventilating.
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
 * \section screenlockModule Screen Lock Mode
 *
 * For maintenance purposes, it is important for the screen and buttons to be cleaned, which is why the option to disable the screen and buttons is available to the user on the <b>Navigational Sidebar</b>. If the system is required to remain running, screen lock mode will be helpful to prevent miss inputs. A Popup Window will be displayed with instructions on how to continue with the cleaning procedure. Continuing will display a transparent overlay over the screen that will prevent the user from pressing any other inputs. If the user presses the screen or the HMI Buttons, the message "Screen lock mode is active. Press the dial to unlock and interact with the screen." will be displayed on screen. Pressing down on the encoder knob will disable Screen Lock Mode and the user will exit from the screen overlay. If touch (water residue or other substances) is detected on the screen or the other HMI Buttons while pressing down on the knob, the message "Moisture detected on panel. Please dry off screen." will be displayed, screen lock will not be disabled.
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
 * \section helpPagesModule Help Pages
 *
 * If a <b>Help Icon</b> is available, the user will have the option to push up a popup window <b>(Help Box)</b> with a description of how a certain feature works, including the descriptions of Pneumatic Settings, and Op Modes.
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
 *      <td>The Inspiratory Time is the percentage of time during the breath cycle in which critical gasses are delivered to the patient.</td>
 *  </tr>
 *  <tr>
 *      <td>Stacking Pressure</td>
 *      <td>
 *      Stacking Pressure (SP) refers to the residual pressure in the airway as measured through the Blue Jet Line approximately 1 ms prior to each inspiratory phase beginning. This is similar to End Expiratory Pressure (EEP) (i.e. closed system ventilation) in critical care ventilators.<br><br>
 *      The VITA will graphically display the measured Stacking Pressure on the main screen with a blue trace. The Blue graph lines can be hidden for the Stacking Pressure from within settings. The set limit for SP is represented on the graph with a blue dashed line.<br><br>
 *      The operator can set the Stacking Pressure threshold from 1-100 cmH2O. The measured value must fall below the set threshold on each breath cycle, indicating that there is adequate egress to the flow of air exiting the patient (i.e. no stacking of breaths). Otherwise, the NVENT Vita immediately alerts the operator and restricts ventilation until the measured Stacking Pressure value drops to 30% of the set Stacking Pressure threshold.
 *      </td>
 *  </tr>
 *  <tr>
 *      <td>Oxygen</td>
 *      <td>
 *      The NVENT Vita is able to proportionally control the concentration of oxygen being delivered to the patient based on desired operator settings. The NVENT VITA performs an automatic O<sub>2</sub> calibration of the oxygen sensor 3 minutes after powering the device on. An automatic secondary O<sub>2</sub> calibration will be performed 10 mins after the device is powered on to ensure proper operation. Calibration can also be performed by the user manually, or it will occur automatically once every 24 hours the unit is powered on. The oxygen concentration can be set in 1% increments from 21% to 100%. The Oxygen setpoint will be delivered on both the Jet Line and the Auxiliary Line.
 *      </td>
 *  </tr>
 *  <tr>
 *      <td>Peak Inspiratory Pressure</td>
 *      <td>
 *      The Peak Inspiratory Pressure (\htmlonly PIP \endhtmlonly) measures continuously and is the highest pressure measured during the respiratory cycle and is an indication of both the resistance of the airways and the compliance of the patient. This pressure is measured on the Red \htmlonly PIP \endhtmlonly Line.<br><br>
 *      The VITA measures the \htmlonly PIP \endhtmlonly regularly and graphically displays the waveform measured on the main screen with a Red trace. The set limit for \htmlonly PIP \endhtmlonly is represented on the graph with a red dashed line.<br><br>
 *      The operator can set the \htmlonly PIP \endhtmlonly threshold from 0-100 cmH<sub>2</sub>O. If the measured \htmlonly PIP \endhtmlonly value meets the set threshold at any point during a breath cycle, the operator is immediately alerted and the Vita restricts ventilation until the measured \htmlonly PIP \endhtmlonly value drops to 30% of the set Peak Inspiratory Pressure threshold.
 *      </td>
 *  </tr>
 *  <tr>
 *      <td>Auxiliary Flow</td>
 *      <td>
 *      The NVENT Vita includes an auxiliary flow line used for supplemental gas flow where continuous flow is needed. The flow from the AUX port is delivered at the same O<sub>2</sub>% as the Jet 1. This line can also be supplied with humidity.<br><br>
 *      <b>Note:</b> This line does not have pressure monitoring capabilities.</td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly Humidity \endhtmlonly</td>
 *      <td>
 *      \htmlonly Humidity \endhtmlonly the Jet Line or Auxiliary can be controlled in a unified or separated mode by the operator. \htmlonly Humidity \endhtmlonly should be used whenever jetting time exceeds 30 minutes of continuous use, it is always advantageous to use humidity although not mandatory for shorter procedures. The use of humidity reduces the risk of drying of the tracheal mucosa, it also helps to prevent compliance issues caused by drying of the lungs. The use of humidity also aids in airway surgery to prevent the tissues from becoming sticky for the surgeon.
 *      </td>
 *  </tr>
 * </table>
 *
 * The following are <b>Help Descriptions</b> available on the popup windows for modes:<br>
 *
 * <table>
 *  <tr>
 *      <th>Op Modes</th>
 *      <th>Help Descriptions</th>
 *  </tr>
 *  <tr>
 *      <td>SP Line Hidden</td>
 *      <td>The NVENT VITA allows the user to hide the blue measured line and the blue dash line for Stacking Pressure.</td>
 *  </tr>
 *  <tr>
 *      <td>Limited O<sub>2</sub></td>
 *      <td>Limited O<sub>2</sub> Mode should be activated before any procedure involving a risk of ignition to help prevent airway fires. Limited O<sub>2</sub> Mode restricts the oxygen concentration to a lower user-set limit, to not exceed 40% O<sub>2</sub>.</td>
 *  </tr>
 *  <tr>
 *      <td>Manual</td>
 *      <td>Manual Mode disables automatic ventilation control to the operator. Ventilation only occurs when the rotary knob is being pressed by the operator. The inspiratory time and breath rate are controlled by the user by how fast and how long they press on the rotary knob. The internal driving pressure will still be controlled by the NVENT and is adjustable. The Peak Inspiratory Pressure and Stacking Pressure thresholds are still monitored by the machine. The LED ring surrounding the rotary knob will glow orange to indicate that the knob will allow the user to control ventilation. Additionally, the start/stop button will not be illuminated and is deactivated while manual mode is active.</td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly PIP \endhtmlonly Disconnection</td>
 *      <td>If \htmlonly PIP \endhtmlonly Disconnection is “ON” the user will be notified if no pressure is detected on the \htmlonly PIP \endhtmlonly pressure line for 15 seconds.</td>
 *  </tr>
 *  <tr>
 *      <td>End-Tidal CO<sub>2</sub></td>
 *      <td>End-tidal CO<sub>2</sub> (ETCO<sub>2</sub>) mode is used when users need to perform an ETCO2 measurement using an external ETCO2 monitor. When enabled, the system changes the respiratory rate, inspiratory time, and driving pressure to user-set values which are more representative of natural ventilation. This enables the ability to acquire a more accurate ETCO2 measurement using an external capnography.</td>
 *  </tr>
 *  <tr>
 *      <td>Dehumidification</td>
 *      <td>Prior to shutting down, the VITA should always be dehumidified to clear the machine of moisture. This is recommended to prevent the buildup of any contaminants. It is also recommended that dehumidification be performed when changing out the water supply.</td>
 *  </tr>
 *  <tr>
 *      <td>O<sub>2</sub> Calibration</td>
 *      <td>In the event of a failed automatic O<sub>2</sub> calibration or if an additional O<sub>2</sub> calibration is needed, a manual O<sub>2</sub> calibration should be performed. Prior to a manual O<sub>2</sub> calibration being performed, ensure that the Air and Oxygen supply lines are connected to the machine and the source. Limited O<sub>2</sub> mode cannot be utilized during an O<sub>2</sub> calibration.</td>
 *  </tr>
 *  <tr>
 *      <td>SP Calibration</td>
 *      <td>
 *      If the SP Sensor is reading measurements while ventilation is inactive, the service technician will be required to conduct a thorough calibration procedure.<br><br>
 *      To begin calibration, we need to zero the SP Sensor by ensuring that the actual value, averaged data, is reaching the target value between 0 and 5. Once the value is reached, press the Confirm button on the Zero Section to continue with verification.<br><br>
 *      The thumbs up or down icon will be displayed on the top right of the window to indicate that the average data is zeroed. The actual value will display the saved average data.<br><br>
 *      To complete calibration, the user will need to verify that the actual value, the raw data subtracted from the saved average, is also accurate.<br><br>
 *      <b>Note:</b> Verify that the Jet tube is connected to the front of the NVENT VITA and that it is open to the atmosphere.<br><br>
 *      To verify the Stacking Pressure Measurement is accurate, the following steps need to be conducted:
 *      1. Connect the Jet tube to an external pressure measuring device.
 *      2. Apply 100 cmH2O to the Jet tube.
 *      3. Verify that the onboard sensor and the external pressure measuring device match.
 *      4. Push down on the Verify button on the Verify Section to complete the procedure.
 *      The thumbs up or down icon will be displayed again to indicate that calibration succeeded or failed, and actual values on the Zero and Verify sections are saved.
 *      </td>
 *  </tr>
 *  <tr>
 *      <td>\htmlonly PIP \endhtmlonly Calibration</td>
 *      <td>
 *      If the \htmlonly PIP \endhtmlonly Sensor is reading measurements while ventilation is inactive, the service technician will be required to conduct a thorough calibration procedure.<br><br>
 *      To begin calibration, we need to zero the PIP Sensor by ensuring that the actual value, averaged data, is reaching the target value between 0 and 5. Once the value is reached, press the Confirm button on the Zero Section to continue with verification.<br><br>
 *      The thumbs up or down icon will be displayed on the top right of the window to indicate that the average data is zeroed. The actual value will display the saved average data.<br><br>
 *      To complete calibration, the user will need to verify that the actual value, the raw data subtracted from the saved average, is also accurate.<br><br>
 *      <b>NOTE:</b> Verify that the Proximal tube is connected to the front of the NVENT VITA and that it is open to the atmosphere.<br><br>
 *      To verify the Peak Inspiratory Pressure Measurement is accurate, the following steps need to be conducted:
 *      1. Connect the Proximal tube to an external pressure measuring device.
 *      2. Apply 100 cmH2O to the Proximal tube.
 *      3. Verify that the onboard sensor and the external pressure measuring device match.
 *      4. Push down on the Verify button on the Verify Section to complete the procedure.
 *      The thumbs up or down icon will be displayed again to indicate that calibration succeeded or failed, and actual values on the Zero and Verify sections are saved.
 *      </td>
 *  </tr>
 * </table>
 *
 * @file HelpBox.qml
 * @brief Popup window to contain information from Help Icon.
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup troubleshootingPagesModule Troubleshooting Steps
 * @{
 * @brief The following pages to contain help info.
 *
 * \section troubleshootingPagesModule Troubleshooting Steps
 *
 * For every warning on the warning banner, there is the troubleshooting option <b>(Troubleshooting Box)</b> to push up the popup window with steps on how to fix the reason for warning.
 *
 * The following are the troubleshooting steps available for each warning:<br>
 * <table>
 *  <tr>
 *      <th style="background-color: #202531; border-color: #202531">Warnings</th>
 *      <th style="background-color: #202531; border-color: #202531">Troubleshooting Step</th>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">\htmlonly PIP \endhtmlonly High!</th>
 *      <td>
 *      - The \htmlonly PIP \endhtmlonly of the patient may be higher than the set \htmlonly PIP \endhtmlonly threshold, ensure there is egress.
 *      - Patient compliance may be low, causing rapid rise of \htmlonly PIP\endhtmlonly. Adjust settings to allow ventilation to resume within safe parameters.
 *      - Patient may be gas trapping causing the stacking of breaths and/or an increased baseline.
 *      - The \htmlonly PIP \endhtmlonly line may be occluded and/or pinched.
 *      - Patient may be spontaneously breathing.
 *      - The \htmlonly PIP \endhtmlonly sensor may be defective.
 *      - Contact support @ 888-730-5463.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">Stacking Pressure High!</th>
 *      <td>
 *      - The Stacking Pressure of the patient may be higher than the set SP threshold, ensure there is egress.
 *      - Patient may be gas trapping causing the stacking of breaths and/or an increased baseline.
 *      - The Jet Line may be occluded and/or pinched.
 *      - Patient may be spontaneously breathing.
 *      - The SP sensor may be defective.
 *      - Contact support @ 888-730-5463.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">\htmlonly PIP \endhtmlonly Disconnected!</th>
 *      <td>
 *      - Ensure the \htmlonly PIP \endhtmlonly line is connected to the patient.
 *      - Ensure the \htmlonly PIP \endhtmlonly line is connected to the NVENT Vita.
 *      - The \htmlonly PIP \endhtmlonly line may see no pressure even when the red line is used depending on the point of reference and how open the system is.
 *      - Monitoring of this warning may be disabled through the settings menu \htmlonly PIP \endhtmlonly Disconnection Page, and the \htmlonly PIP \endhtmlonly Adjustment Page.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Jet Line!</th>
 *      <td>
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Press prime in the warning banner to prime the pumps.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Auxiliary Line!</th>
 *      <td>
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Press prime in the warning banner to prime the pumps.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #F24C26; border-color: #202531">No Water Detected in Jet and Auxiliary Lines!</th>
 *      <td>
 *     - Make sure distilled sterile water is connected to the machine.
 *     - Press prime in the warning banner to prime the pumps.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet \htmlonly Switch \endhtmlonly Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Stacking Pressure Sensor Defective!</th>
 *      <td>
 *      - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Stacking Pressure Internally Disconnected!</th>
 *      <td>
 *     - Ensure the jet line is connected to the patient.
 *     - Ensure the jet line is connected to the NVENT Vita.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Inappropriate Oxygen Sensor Detected</th>
 *      <td>
 *     - Oxygen sensor cannot be read.
 *     - Ensure that you are using a "INSERT KIND OF OXYGEN SENSOR HERE".
 *     - Ensure that oxygen sensor is securely inserted.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Air Supply Pressure!</th>
 *      <td>
 *     - The measured inlet air pressure is too low.
 *     - Ensure that the NVENT is securely connected to the air source.
 *     - The delivered oxygen concentration may be higher that expected as a result of this warning.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Air Supply Pressure, Limited O<sub>2</sub> Adjustment In Progress!</th>
 *      <td>
 *     - The delivered oxygen concentration may be higher than expected. Do not use a laser.
 *     - The measured inlet air pressure is too low.
 *     - Ensure that the NVENT is securely connected to the air source.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Low Oxygen Supply Pressure!</th>
 *      <td>
 *     - The measured inlet oxygen pressure is too low.
 *     - Ensure the NVENT is securely connected to the oxygen source.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Proportional Valve Error!</th>
 *      <td>
 *     - Contact support & 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Proportional Valve Error, Limited O<sub>2</sub> Adjustment in Progress!</th>
 *      <td>
 *     - Do not use a laser 100% oxygen is delivered to the patient.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Proportional Valve Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Inlet Pressure Sensor Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Air Inlet Pressure Sensor Error, Limited O<sub>2</sub> Adjustment in Progress!</th>
 *      <td>
 *     - Do not use a laser 100% oxygen is delivered to the patient.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Inlet Pressure Sensor Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Proportional Valve Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Flow Sensor Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Speaker Defect!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Heater Failure!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Internal Temperature Measuring Defect!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Flow Sensor!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet \htmlonly Humidity \endhtmlonly Sensor Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary \htmlonly Humidity \endhtmlonly Sensor Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Real Time Clock Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Exhaust Fan Error</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Driving Pressure Regulator Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">\htmlonly PIP \endhtmlonly Sensor Error!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">FiO<sub>2</sub> Failure!</th>
 *      <td>
 *     - Check that Air and Oxygen supplies are connected correctly.
 *     - Attempt to recalibrate the oxygen sensor in the Settings/Oxygen Calibration Menu.
 *     - The oxygen sensor may need to be replaced.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Display and System Disconnected!</th>
 *      <td>
 *     - Unable to retrieve settings, operating in headless mode.
 *     - Restart when possible.
 *     - Contact service when possible @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Oxygen Calibration Failure!</th>
 *      <td>
 *     - Check that Air and Oxygen supplies are connected correctly.
 *     - The oxygen sensor may need to be replaced.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Water Pump Defect</th>
 *      <td>
 *     - Service is required to change water pump.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Water Pump Defect</th>
 *      <td>
 *     - Service is required to change water pump.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Failed to Restore Memory</th>
 *      <td>
 *     - The system has failed to restore data from memory.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Dehumidification Failed</th>
 *      <td>
 *     - Water may still be connected to the water inlet port.
 *     - The water inlet port may be plugged.
 *     - The output port may be plugged.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Breath Timing Failure!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Jet Water Sensor Failure!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Auxiliary Water Sensor Failure!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Ambient Temperature Sensor Defect!</th>
 *      <td>
 *     - Contact support @ 888-730-5463
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #4A5AE4; border-color: #202531">Internal System Temperature High</th>
 *      <td>
 *     - Check that the exhaust fan (located on the device posterior) is not blocked.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #6FCC68; border-color: #202531">Limited O<sub>2</sub> Safe</th>
 *      <td>
 *     - Limited O<sub>2</sub> mode is active, excess oxygen has been flushed from the system, and the set oxygen concentration is below the set limited oxygen value.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Limited O<sub>2</sub> Prepping</th>
 *      <td>
 *     - Limited O<sub>2</sub> mode is active. The system is prepping for laser use.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Low Static O<sub>2</sub> Pressure</th>
 *      <td>
 *     - The input oxygen pressure is below 35 PSI.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Low Static Air Pressure</th>
 *      <td>
 *     - The input air pressure is below 35 PSI.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Manual Mode Active, \htmlonly PIP \endhtmlonly Monitoring Recommended</th>
 *      <td>
 *     - Manual mode is active. Consider monitoring \htmlonly PIP\endhtmlonly.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">\htmlonly PIP \endhtmlonly Monitoring Recommended</th>
 *      <td>
 *     - The set breath rate is below 80 BPM. Consider monitoring \htmlonly PIP\endhtmlonly.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">End Tidal CO<sub>2</sub> Routine Active</th>
 *      <td>
 *     - End-tidal CO<sub>2</sub> is in progress.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Service Due</th>
 *      <td>
 *     - The system is due for servicing. Schedule an appointment.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Battery Replacement Due</th>
 *      <td>
 *     - The battery is low. Schedule a servicing appointment.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Heater and Humidifier Off</th>
 *      <td>
 *     - The heater is defective. Schedule a servicing appointment.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification System Deactivated</th>
 *      <td>
 *     - The water sensors may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification Deactivated on Jet Line</th>\
 *      <td>
 *     - The water sensor on the jet line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Humidification Deactivated on Auxiliary Line</th>
 *      <td>
 *     - The water sensor on the auxiliary line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Auxiliary Flow Deactivated</th>
 *      <td>
 *     - The water sensor on the auxiliary line may be defective.
 *     - The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Only Use Distilled Water For Humidification</th>
 *      <td>
 *     - Only Use Distilled Sterile Water.
 *     - Using Saline or other composite fluids WILL clog water injectors.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Pump System Priming</th>
 *      <td>
 *     - The system is preparing to humidify the critical gases.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Ventilating without Humidifying for 30+ minutes. Consider adding humidity.</th>
 *      <td>
 *     - The NVENT Vita has been ventilating for 30 minutes without humidification. Consider humidifying the critical gases.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Oxygen Calibration in Progress, Limited O<sub>2</sub> Adjustment in Progress</th>
 *      <td>
 *     - The system is calibrating the oxygen sensor. Do not use a laser.
 *      </td>
 *  </tr>
 *  <tr>
 *      <th style="background-color: #E2C044; border-color: #202531">Oxygen Calibration in Progress</th>
 *      <td>
 *     - The system is calibrating the oxygen sensor.
 *     - You may proceed ventilation.
 *     - The oxygen controller has been temporarily suspended.
 *      </td>
 *  </tr>
 * </table>
 *
 *
 * @file Troubleshoot.qml
 * @brief Popup window to contain information on troubleshooting warning.
 *
 * @}
 */

/**
 * @ingroup pagesModule
 * @defgroup settingsMenuPagesModule Settings Menu
 * @{
 * @brief The following pages for the Settings Menu.
 * @details
 *
 * \section settingsMenuPagesModule Settings Menu
 *
 * The Setting Menu where the user can access multiple pages where the user can update important aspects of the NVENT-Vita.<br>
 *
 * The <b>Stacking Pressure Page</b> is where the user can update the visibility for the blue line on the graph.<br>
 *
 * The <b>Limited O<sub>2</sub> Page</b> is where the user can adjust the oxygen concentration for the Limited O<sub>2</sub> Mode.<br>
 *
 * The <b>ETCO<sub>2</sub> Settings Page</b> is where the user can adjust the following Pneumatic Settings for the End-Tidal Procedure: ETCO<sub>2</sub> \htmlonly Rate \endhtmlonly, ETCO<sub>2</sub> Inspiratory Time, ETCO<sub>2</sub> Number of Breaths, and ETCO<sub>2</sub> Driving Pressure.<br>
 *
 * The <b>O<sub>2</sub> Calibration Page</b> is where the user begins the O<sub>2</sub> Calibration Procedure.<br>
 *
 * The <b>\htmlonly PIP \endhtmlonly Disconnection Page</b> is where the user can enable and disable \htmlonly PIP \endhtmlonly Disconnection Mode.<br>
 *
 * The <b>Brightness and \htmlonly Volume\endhtmlonly Page</b> is where the user can adjust the volume of the alarm and the brightness of the screen. The page includes options that allow the user to switch the dial adjustment page for brightness, and the dial adjustment page for volume.
 * - For adjusting brightness, turning the encoder knob will increase or decrease the brightness of the screen and directly communicate with the brightness manager. To save Brightness, the user will be required to press down on Save Button or the encoder knob.
 * - For adjusting volume, turning the encoder knob will increase or decrease the volume used for the warning alarms. An alarm sound will be made after every turn indicating what the actual volume will sound like. To save \htmlonly Volume\endhtmlonly, the user will be required to press down on Save Button or the encoder knob.
 *   - <b>Note:</b> The \htmlonly <b>Volume</b> \endhtmlonly is classified as a Pneumatic Setting for easier communication with the system.
 *
 * The <b>About Page</b> page displays important system data, including the following:
 * - Service and Sales Contact Information.
 * - Last and Next Service Dates.
 * - Software Version Numbers for Display, System, and HMI Controller.
 * - Serial Number for the device.
 * - IP Address with option to refresh if device needs to reconnect with ethernet cable.
 * - \htmlonly Switch \endhtmlonly digital clock between Daylight Savings Time and Standard Time
 * - Option to update passcode.
 *
 * For passcode changes on the About Page, the passcode store on the system is utilized for adjusting presets. The default passcode will be 0000 and is required to be 4 digits. To change passcodes, the user is required to enter the current passcode first, then the option to change the passcode will become available. Note that the user cannot use the previous passcode for the new one, only the service technician can be able to do that.
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
 * @file VolumeAndBrightness.qml
 * @brief Page to adjust the brightness of the screen and the volume of the alarm.
 *
 * @file Brightness.qml
 * @brief Sub Page to adjust brightness.
 *
 * @file Volume.qml
 * @brief Sub Page to adjust volume.
 *
 * @file About.qml
 * @brief Page where system data is displayed.
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
 */

/**
 * @ingroup pagesModule
 * @defgroup serviceMenuPagesModule Service Menu
 * @{
 *
 * @brief The service menu pages will be utilized by service technician.
 * @details
 *
 * \section serviceMenuPagesModule Service Menu
 *
 * The Service Menu is where only the service technician can access multiple pages and update important aspects of the NVENT-VITA.<br>
 *
 * The <b>Demo Page</b> where the user can enable demo mode on the system, which would disable system warnings for demonstration purposes.<br>
 *
 * The <b>Factory Settings Page</b> where the user can enable the second jet on the system (if available).<br>
 *
 * The <b>Maintenance Page</b> that displays important system data and where the service technician can update said data. The page will include the following:
 * - The option to update the contact information for the service company and the sales company. A popup window will be pushed up, which will include a keyboard and text boxes for the following: Company Name, Street Address, City/Town, State, Postal Code, Phone Number, and Email / Website.
 * - The options to update the date, time, and time zone for the digital clock. A popup window will be pushed up for part of the digital clock to be updated.
 * - The option to update the last and next service dates, popup windows are also constructed from @ref DatePopup.qml "Date Popup Window".
 * - Software Version Numbers for Display, System, and HMI Controller.
 * - Serial Number for the device.
 * - IP Address with option to refresh if device needs to reconnect with ethernet cable.
 *
 * The <b>Components Page</b> where the service technician can update the part data when replacing parts. A table will be displayed with every part that would be replaced on the system. The user can scroll through every part and columns for each part include the name, serial number, installation date, hours of operation, and hours of ventilation. To begin the replacement procedure, the user must press the "Replace" Option. The borders for the part name entries will be highlighted. Selecting the name for a part will begin the following procedure through popup windows:
 * 1. The user must confirm that they would like to continue with the replacement process for the part selected.
 * 2. The user must then update the installation date if it is not today.
 * 3. The user must enter the new serial number (if available) with the pushed up keyboard.
 * 4. The user must finally confirm replacement, which will reset parts hours of operation and ventilation.
 *
 * The <b>Calibration Page</b> where the service technician conducts sensor and pressure regulator calibration. As the medical professional continues using the device, they need to ensure that the multiple sensors and pressure regulators are producing the most accurate data for the user.
 * The sensors that need to be calibrated on the page include the <b>Inlet Air Sensor</b>, the <b>Inlet O<sub>2</sub> Sensor</b>, the <b>\htmlonly PIP \endhtmlonly Sensor</b>, and the <b>SP Sensor</b>.
 * The pressure regulators that need to be calibrated on the page include the <b>Driving Pressure Regulator</b>, the <b>Air Regulator</b>, and the <b>Oxygen Regulator</b>.
 * The procedures for each will go as followed:
 * - <b>\htmlonly PIP \endhtmlonly and SP Zeroing and Verifying:</b> the user should not see values greater than 0 if the system isn’t ventilating. The service technician can conduct calibration by zeroing the measured values for \htmlonly PIP \endhtmlonly and SP. Through the pop up window for each, the user can zero with the press of the button. A success or failure icon will be displayed based on the results. For the verification, the user will need to use a verification tool for manually producing values up to 100.
 * - <b>Inlet Air and Oxygen Zeroing and Verifying:</b> Inlet Air and O<sub>2</sub> refers to the pressure produced from the tanks to the system. The system should not see pressure if tanks are not connected or closed. The service technician can conduct calibration by zeroing the measured values for Inlet Air and Inlet O<sub>2</sub>. Through the pop up window for each, the user can zero with the press of the button. A success or failure icon will be displayed based on the results. For the verification, the user will need to manually adjust tanks to ensure that values can produce pressure greater or less than 30. (Separate Calibration tool will be required.)
 * - <b>Low and High Driving Pressure Regulator Calibration:</b> Through the pop up window for low, the user will only need to press a button to calibrate. Previous DPR value will be displayed. Through the same pop up window for high calibration, the user will need to ensure that the live feed for DPR will remain a 45. Precise adjustment for Driving Pressure through the encoder knob may be required. Previous DPR value will be displayed.
 * - <b>Air and Oxygen Regulator Calibration:</b> Through the pop up window for high calibration, the user will need to ensure that the live feed for DPR can hit 48 by pushing down on the encoder knob for the Air Regulator or the Oxygen Regulator.
 *
 * The <b>O<sub>2</sub> Calibration Page</b> to the service technician begins the O<sub>2</sub> Calibration Procedure. He or she can even adjust oxygen concentration with the encoder knob, see a live feed for the O2 Calibration Voltage from the Service Notification, and see a history of the lowest and highest calibration voltages; see O2 Calibration Manager for how calibration data is saved and how warning banner timer for O2 Calibration is triggered.
 *
 * The <b>Service Logs Page</b> where the user can export service logs to a USB Stick. Upon opening the page, the user will be required to check, mount, and create directories for the USB stick attached to the back of the device. If the USB stick is detected, then the user will be able to open the pop up to export all service logs to directories <b>NVENT_events</b> and <b>NVENT_warnings</b>. The option to reconnect the USB stick will be available if failed to connect for the first time. The window will display the progress of each file to the USB stick. To ensure that no data is lost due to inappropriate removal of the stick, the disconnection button will unmount the USB stick.
 *
 * The <b>Passcode Page</b> where the user can change the user's passcode and the service technician's passcode. The service technician can even forcefully change the user’s passcode.
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
 *
 * @file O2Calibration.qml
 * @brief Page to trigger the O<sub>2</sub> Calibration Procedure
 * @details Includes other features:
 * - Displays the current and previous lowest and hightest O<sub>2</sub> Calibration voltages.
 * - Displays the live feed for the O<sub>2</sub> Calibration value.
 * - Include a mini dial with encoder knob functionality to adjust the Oxygen Concentration, and in turn adjust the O<sub>2</sub> calibration value.
 *
 * @file ServiceLogs.qml
 * @brief Page to export service logs to USB Drive and show the progress of exporting service logs to USB Drive.
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
 */
