cmake_minimum_required(VERSION 3.16)

project(UPPMControlApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appUPPMControlApp
    main.cpp
    eth/ethcore.h eth/ethcore.cpp
    eth/uppm.h eth/uppm.cpp
    eth/frame_defines.h
    eth/uppm_command_frame.h eth/uppm_fdk_frame.h eth/uppm_raw_comm_frame.h
)

target_include_directories(appUPPMControlApp PUBLIC
    eth
    gui
)

qt_add_qml_module(appUPPMControlApp
    URI UPPMControlApp
    VERSION 1.0

    QML_FILES qml/Main.qml
    QML_FILES qml/EthSettings.qml
    QML_FILES qml/ControlScreen.qml

    SOURCES gui/ethgui.h gui/ethgui.cpp
    SOURCES gui/controlgui.h gui/controlgui.cpp
)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appUPPMControlApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appUPPMControlApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appUPPMControlApp PUBLIC
    Qt6::Core
    Qt6::Quick
    Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appUPPMControlApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
