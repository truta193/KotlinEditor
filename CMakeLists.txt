cmake_minimum_required(VERSION 3.16)

project(KotlinEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
qt_standard_project_setup()

qt_add_executable(appKotlinEditor
    main.cpp
    resources.qrc
)

qt_add_qml_module(appKotlinEditor
    URI KotlinEditor
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES App.qml
    QML_FILES components/EditorPane.qml
    QML_FILES components/ActionButton.qml
    RESOURCES resources.qrc
    SOURCES
    SOURCES highlighter.h highlighter.cpp
    SOURCES
    SOURCES syntaxHandler.h syntaxHandler.cpp
    SOURCES theme.h theme.cpp
    SOURCES filehandler.h filehandler.cpp
    SOURCES
    SOURCES processhandler.h processhandler.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appKotlinEditor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appKotlinEditor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appKotlinEditor
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appKotlinEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
