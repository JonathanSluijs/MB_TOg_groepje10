CMAKE_MINIMUM_REQUIRED(VERSION 3.18)
PROJECT(MB_TOg_groepje10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(APPLE)
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(./libs/gtest/include)

link_directories(./libs/gtest/lib) #TODO EVERYONE: GENERATE YOUR OWN LIBGTEST.A AND LIBGTEST_MAIN.A (MAKE SURE IT IS THE SAME VERSION AS THE CURRENT GTEST (LATEST: Release 1.15.2: https://github.com/google/googletest.git)



# Hoofdproject bronnen
SET(SOURCES
        Sources/SingleTapeTransformer.cpp
        Sources/Tape.cpp
        Sources/MultiTapeTuringMachine.cpp
        Sources/TransitionFunction.cpp
        Parsers/EarleyParser.cpp
        Sources/CFG.cpp
        Sources/Logger.cpp
        Parsers/CYKParser.cpp
        Parsers/ParseTree.cpp
        Sources/ExpressionCalculator.cpp
)

SET(SOURCES_GUI
        Interface/MainWindow.cpp
        Interface/TuringSimulationDialog.cpp
        Interface/ArithmeticDialog.cpp
        Interface/OutputViewer.cpp

)

# Hoofdprogramma executable
ADD_EXECUTABLE(TuringTutor main.cpp ${SOURCES} ${SOURCES_GUI})
target_link_libraries(TuringTutor Qt5::Core Qt5::Gui Qt5::Widgets)

# Testbronnen
SET(TEST_SOURCES
        Tests/mainTest.cpp
        Tests/MultiTapeTuringMachineTests.cpp
        Tests/TransitionFunctionTests.cpp
        Tests/TapeTests.cpp
        Tests/ExpressionCalculatorTests.cpp
        Tests/ParserTests.cpp
)

# Test executable maken
ADD_EXECUTABLE(TuringTutorTests ${TEST_SOURCES} ${SOURCES})

# Voeg GoogleTest includes toe aan de test target
target_link_libraries(TuringTutorTests gtest gtest_main)

# Link de test executable met de GoogleTest bibliotheken en Qt


# Windows-specifieke instellingen (indien van toepassing)
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
