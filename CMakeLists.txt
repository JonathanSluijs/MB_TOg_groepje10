CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
PROJECT(MB_TOg_groepje10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Works for Linux, not sure for MacOS

if(APPLE)
    # Voeg de locatie toe waar Qt5 via Homebrew is geïnstalleerd
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")
endif()


find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

SET(SOURCES
        main.cpp
        Sources/Tape.cpp
        Sources/MultiTapeTuringMachine.cpp
        Sources/TransitionFunction.cpp
        Sources/EarleyParser.cpp
        Sources/CFG.cpp
        Sources/Logger.cpp
        Sources/CYKParser.cpp)

SET(SOURCES_GUI
        Interface/MainWindow.cpp
        Interface/TuringSimulationDialog.cpp
        Interface/ArithmeticDialog.cpp)

ADD_EXECUTABLE(TuringTutor ${SOURCES} ${SOURCES_GUI})

target_link_libraries(TuringTutor Qt5::Core Qt5::Gui Qt5::Widgets)





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