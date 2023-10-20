//Frontend module

/**
 * @ingroup frontendModule
 * @defgroup pagesModule Pages
 * @brief All pages used for the Graphical User Interface.
 * @details
 *
 * ## Pages
 *
 * In context to the graphical user interface, a page refers to a screen within an application that presents a specific set of information or functionality to the user. A page will be composed of different objects, texts, and inputs (referred to as mouse areas). Each page size will match the screen size of the display controller's screen, which is 1280 x 800. For popup windows, the page itself will still be 1280 x 800, but the background will be transparent and the middle section will be composed of a rectangular box.
 *
 * ## Page StackViews
 *
 * A StackView is a component that provides a way to manage multiple views/pages in a stack-like manner for navigation. Stack refers to a data structure that follows the Last-In-First-Out (LIFO) Model. It is a collection of elements in which items can be added or removed only from one end. Note that for Popup windows and pages that are not the Home page, the Preset Creation page, and the Service Menu page will automatically redirect back to the home page if there is no activity or input for at least 1 minute.
 *
 * ### Home Stack
 * Where the user will navigate between main components of the GUI, including the following:
 * - the Home Window Page
 * - Adjustment Pages
 * - the Preset Pages
 * - the Settings Menu Page
 * - Passcode Pages
 * - the Service Menu Page
 *
 * ### Popup Stack
 * Where the user pushes up Popup Windows and other pages separate from the main components:
 * - Screen Lock Popup and Overlay
 * - Dehumidfication Popups and Progress Page
 * - Jet Active Popup and Shutdown Procedure Popups
 * - Help and Troubleshooting Boxes
 * - Preset Name Popup and Preset Implementation Popup
 * - Pneumatic Settings Confirmation Popup
 *
 * ### Adjustment Page StackViews
 * StackViews are also utilized for adjustment pages where the user will need to switch between the dial page, and the keypad page.
 *
 * ### Service Popup StackView
 * StackView specifically for the popup windows available on the Service Menu.
 *
 * ### Settings Stacks for Settings and Service Menus
 * StackViews used to containing menu pages.
 *
 * ## Additional Information
 *
 * Futher Details to pages is available in the following:
 * - @ref homePagesModule "Home Pages"
 * - @ref pneumaticSettingPagesModule "Pneumatic Settings Adjustment Pages"
 * - @ref presetPagesModule "Preset Options"
 * - @ref dehumidificationModule "Dehumidification Pages"
 * - @ref screenlockModule "Screen Lock Mode"
 * - @ref shutdownProcedureModule "Shutdown Procedure Pages"
 * - @ref helpPagesModule "Help Pages"
 * - @ref settingsMenuPagesModule "Settings Menu"
 * - @ref serviceMenuPagesModule "Service Menu"
 */

/**
 * @ingroup frontendModule
 * @defgroup customObjectsModule Custom Objects
 */

/**
 * @ingroup frontendModule
 * @defgroup stylingModule Styling
 * @brief Components responsible for the design of the pages and object.
 * @details
 *
 * ## Styling
 *
 * Styling refers to the overall design for the the Graphical User Interface. Styling include color of centein objects and pages, the font and sizes for text and titles, and the even the positioning and sizes of objects on pages.
 * Styling is significantly important not only to the NVENT-VITA, but to UI Development in general, for it is important to the visual appeal,
 * improving user experience, reinforcing branding and identity, differentiation to other products, and aiding in the communication between user and interface.
 *
 * ## Additional Information
 *
 * Furthor information for styling will be available in the following:
 * - @ref familyModule "Font Family: Roboto"
 * - @ref styleModule "Styles and Fonts"
 * - @ref textModule "Constant Texts"
 */

/**
 * @ingroup frontendModule
 * @defgroup iconographyModule Iconography
 * @brief Iconography graphics utilized for different GUI components.
 * @details
 *
 * ## Iconography
 *
 * Iconography displayed on different objects and pages are built from transparent svg files.
 *
 * Iconography and symbols available on the GUI:
 * - The Projection Screen Symbol for Demo Mode.
 * - Up and Down Symbols for the up or down options.
 * - Plier Symbol used to trigger Calibration Buttons
 * - Delete Symbol for the Delete Button for Presets.
 * - Edit Symbol for the Edit Button for Presets.
 * - Alarm Symbol to display number of warnings and expand all warnings on the warning banner.
 * - Check Mark Symbol used for confirmation buttons (Save/Continue Buttons) on the Display.
 * - Cross Symbol used for all close buttons.
 * - Water Crossed Symbol used for dehumidification options.
 * - Question Mark that makes up all help icons.
 * - Home Symbol that makes up all home icons.
 * - Lock with Water Drop Symbol that is used for the Screen Lock Overlay.
 * - Preset Symbol used for the Navigational Option for Presets.
 * - Stopwatch Symbol used for the timer on home page.
 * - Mechanical Symbol used for the Settings Menu option.
 * - Backspace Symbol used for buttons on all keypads backspace buttons.
 * - Lantern Logo displayed on start up loading screen.
 * - Lock with Finger Touch Symbol used for Screen Lock Mode.
 * - Keypad Symbol used for all keypad push up buttons.
 * - Textbox with Lock Symbol for incorrect passcodes.
 * - Play Symbol used to begin dehumidification.
 * - Plus Symbol used for the Create Button for presets.
 * - Thumbs Up and Down Symbols for O<sub>2</sub> Calibration Results.
 *
 * @file DemoIcon.svg
 * @file Icon_40_down.svg
 * @file Icon_40_up.svg
 * @file calibration.svg
 * @file delete.svg
 * @file edit.svg
 * @file icon_40_alarm.svg
 * @file icon_40_alarm_2.svg
 * @file icon_40_checkmark.svg
 * @file icon_40_close.svg
 * @file icon_40_dehumidify.svg
 * @file icon_40_demo.svg
 * @file icon_40_help.svg
 * @file icon_40_home.svg
 * @file icon_40_lockscreen.svg
 * @file icon_40_presets.svg
 * @file icon_40_progress.svg
 * @file icon_40_settings.svg
 * @file keyboard-delete.svg
 * @file lantern-logo.svg
 * @file lock_element.svg
 * @file numpad_icon.svg
 * @file passcode.svg
 * @file play.svg
 * @file plus.svg
 * @file thumbs-down.svg
 * @file thumbs-up.svg
 */

