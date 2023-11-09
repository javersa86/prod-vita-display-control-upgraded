//Modules for GPIO components.

/**
 * @ingroup  gpioModule
 * @defgroup knobModule Knob Controller
 * @brief Documentation for the \htmlonly Knob \endhtmlonly Controller.
 * @{
 * @details
 *
 * \section knobModule Knob Controller
 *
 * The knob controller is responsible for monitoring the \htmlonly GPIO \endhtmlonly pins for the encoder and sending signals to the QML when the knob is turned or the button is pushed. It is composed of a switch object, and an encoder object. The switch object emits a signal when the button is pushed, and the encoder object emits a signal when the knob is turned. The \htmlonly GPIO \endhtmlonly object monitors pin numbers that they are given. The knob object itself uses poll to watch the file descriptors of the \htmlonly GPIO \endhtmlonly objects watching for changes. When a file descriptor is changed, the knob object updates the knob or encoder appropriately. The knob controller is also running on a QThread at the start of the display controller software. See \ref thread2 "Encoder Knob Thread"
 *
 * \section gpioModule_calc Calculating Pin Numbers
 *
 * From the SECO documentation, pin numbers are calclated using the following formula:
 *
 * (b - 1) * 32 + nn
 *
 * Using this documentation from <a href="https: * wikitech.seco.com/index.php/A62_-_J8_expansion_header_6.0/">SECO</a> is where one can fin the pin number.
 * On finds the b and nn values through the Pinout Configurations Options section of the documentation. The valeus are in the format: GPIOb_nn.
 *
 * @}
 */

/**
 * @ingroup  gpioModule
 * @defgroup switchModule Switch
 * @brief Documentation for the switch on the \htmlonly Knob \endhtmlonly Controller.
 * @{
 * @details
 *
 * \section switchModule Switch
 *
 * The \htmlonly Switch \endhtmlonly component of the knob controller is tasked with setting up the button in the rotary knob. The switch emits a signal for when the button is pushed and when the button is released.
 * @}
 */

/**
 * @ingroup  gpioModule
 * @defgroup encoderModule Encoder
 * @brief Documentation for the encoder on the \htmlonly Knob \endhtmlonly Controller.
 * @{
 * @details
 *
 * \section encoderModule Encoder
 *
 * The \htmlonly Encoder \endhtmlonly component of the knob controller is tasked for listening for changes on pin A and pin B and emits signals when the knob is turned. Both pin A and pin B switch states everytime the knob is turned. If pin A changes, then this means that the signal value emitted is +1 and the knob turned clockwise. If pin B changes, then this means that signal value emitted is -1 and the knob turns counter clockwise.
 *
 * To ensure that the encoder continues to turn one direction, the encoder will read a pattern of sums representing pins as bits. A sum will be read where each bit represents a pin: [Last Pin A State, Last Pin B State, Current Pin A State, Current Pin B State]. If the sum is calculated between 13 (1101) and 2 (0010), then the encoder will continue to emit a signal of -1 for each turn. If the sum is calculated between 14 (1110) and 1 (0001), then the encoder will continue to emit a signal of +1.
 * @}
 */

/**
 * @ingroup  gpioModule
 * @defgroup gpioMainModule GPIO
 * @brief Documentation for the \htmlonly GPIO \endhtmlonly pins on the \htmlonly Knob \endhtmlonly Controller.
 * @{
 * @details
 *
 * \section gpioMainModule GPIO
 *
 * The \htmlonly GPIO \endhtmlonly object for the \htmlonly Knob \endhtmlonly Controller allows the developer to export and set the direction and edge of a pin. If the direction is "in" (the direction is always "in'' for our case), the developer can get the value of the pin in addition to exporting the pin, opening the file descriptor, getting the file descriptor, and setting the direction and edge of the pin. In Linux, the direction, edge, and value of a pin are all saved in files once the pin is exported. To modify the direction, edge, or value, the developer just needs to modify the file. One must never modify the file of a pin with direction "in '' though. To get the direction, edge, or value of a pin, one must simply read the file.
 *
 * There are 3 \htmlonly GPIO \endhtmlonly components to the knob controller, one representing pin A, one representing pin B, and one representing the switch used for the button; all are found in the <b>\htmlonly GPIO \endhtmlonly File Directory.</b>
 *
 * - <b>/sys/class/gpio</b> - root for where the \htmlonly GPIO \endhtmlonly updates any pins available
 * - <b>/sys/class/gpio/gpio9</b> - Pin A.
 * - <b>/sys/class/gpio/gpio57</b> - Pin B.
 * - <b>/sys/class/gpio/gpio55</b> - \htmlonly Switch \endhtmlonly Pin.
 * @}
 */
