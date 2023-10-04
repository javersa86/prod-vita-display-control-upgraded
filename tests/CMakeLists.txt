include_directories( ${nvent-vita-display_SOURCE_DIR} )

set( TEST_LIBRARIES 
    vita-core
    Qt5::Test
    Qt5::Core)

set( tests_SRCS communication_tests.cpp gpio_tests.cpp)
add_executable( tests ${tests_SRCS} )
target_link_libraries( tests ${TEST_LIBRARIES} )
add_test( NAME tests COMMAND tests )

set( warnings_SRCS warnings.cpp)
add_executable( warnings_tests ${warnings_SRCS} )
target_link_libraries( warnings_tests ${TEST_LIBRARIES} )
add_test( NAME warnings_tests COMMAND warnings_tests )

set( logging_SRCS logging_tests.cpp)
add_executable( logging_tests ${logging_SRCS} )
target_link_libraries( logging_tests ${TEST_LIBRARIES} )
add_test( NAME logging_tests COMMAND logging_tests )
