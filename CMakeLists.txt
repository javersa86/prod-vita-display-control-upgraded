cmake_minimum_required(VERSION 3.5.0)


#Update the version of the software here
project(nvent-vita-display LANGUAGES CXX VERSION 1.1.5)



set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(nventConfig.h.in nventConfig.h)

find_package(Qt5 COMPONENTS Core Quick Widgets Charts Test REQUIRED)

#Adds in the src files, used for the actual application
add_subdirectory(src)
#Adds in the tests files, used for testing the application
add_subdirectory(tests)

#adds the executable, nvent-vita-display, used to run the application
add_executable(nvent-vita-display
    main.cpp
    qml.qrc)

#This links the vita-core library to the nvent-vita-display executable
target_link_libraries(nvent-vita-display
    PUBLIC vita-core)

#This links the necessary Qt libraries to the nvent-vita-display.
#If the keybaord library gets added, it needs to be added here
target_link_libraries(nvent-vita-display
  PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::Charts)

#Including the necessary files in
target_include_directories(nvent-vita-display PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/vita-core"
    )
#How to compile the application
target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)


#what to install and where
install(
  TARGETS ${PROJECT_NAME}
  RUNTIME
    DESTINATION bin
)


#Includes the nventConfig file, used for passing the version to the C++ code
install(FILES "${PROJECT_BINARY_DIR}/nventConfig.h"
  DESTINATION include)

enable_testing()
