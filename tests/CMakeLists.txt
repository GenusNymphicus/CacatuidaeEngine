#Cockatoo/Tests/
if(RUN_TESTS)
    ################################
    # Unit Tests
    ################################
    MESSAGE( STATUS "RUNNING TESTS")

    add_subdirectory(Graphic)
    
    set(HEADER_FILES  ${HEADER_FILES} PARENT_SCOPE)

    # Add test cpp file
    include_directories(gtest_main ${TEST_HEADER} ${HEADER_FILES})
    add_executable( runUnitTests ${TEST_SOURCES} )

    # Link test executable against gtest & gtest_main
    target_link_libraries(runUnitTests gtest gtest_main )
    add_test( runUnitTests runUnitTests )

    add_library(TestLib ${SOURCE_FILES})
    TARGET_LINK_LIBRARIES(runUnitTests TestLib ${LIBRARIES} )
    
    add_custom_command(TARGET runUnitTests POST_BUILD COMMAND runUnitTests)
endif(RUN_TESTS)