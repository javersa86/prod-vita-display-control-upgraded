#Add the different necessary C++ files. If you add a new C++ file, you need to add it here
add_library(vita-core
    backend.cpp
    state_manager.cpp
    logger/part_manager.cpp
    logger/log_manager.cpp
    logger/csv_manager.cpp
    logger/preset_manager.cpp
    logger/brightness_manager.cpp
    logger/o2_cal_manager.cpp
    logger/dpr_manager.cpp
    logger/zero_manager.cpp
    logger/passcode_manager.cpp
    logger/part_manager.cpp
    logger/time_manager.cpp
    logger/maintenance_manager.cpp
    logger/contact_manager.cpp
    logger/version_manager.cpp
    communication/api.cpp
    communication/devices.cpp
    communication/serial.cpp
    communication/message.cpp
    communication/message_queue.cpp
    models/pneumatic_settings.cpp
    models/mode_settings.cpp
    models/QML_IDS.h
    models/QML_notifications.h
    models/QML_settings.h
    models/hmi_buttons.h
    models/sensors.h
    gpio/gpio.cpp
    gpio/switch.cpp
    gpio/encoder.cpp
    gpio/knob.cpp
    warnings/warnings.cpp
    warnings/warning_manager.cpp
    )

#Link the various necessar libraries.
#If you add a library, it needs to be added here
target_link_libraries(vita-core
  PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::Charts usb-1.0)

#Install the vita-core library
install(TARGETS vita-core DESTINATION lib)
#Add .h files here
install(FILES
        backend.h
        communication/api.h
        communication/devices.h
        communication/serial.h
        models/pneumatic_settings.h
        warnings/warnings.h
        warnings/warning_manager.h
    DESTINATION include)

#Add file path and library for libusb
find_path(LIBUSB_INCLUDE_DIR
  NAMES libusb.h
  PATH_SUFFIXES "include" "libusb" "libusb-1.0")
find_library(LIBUSB_LIBRARY
  NAMES usb
  PATH_SUFFIXES "lib" "lib32" "lib64")
