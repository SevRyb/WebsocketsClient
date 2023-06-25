cmake_minimum_required(VERSION 3.17.5)

project(websockets_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 COMPONENTS WebSockets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebSockets REQUIRED)

add_subdirectory(submodules/qlementine)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(websockets_client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(websockets_client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(websockets_client
            ${PROJECT_SOURCES}
	    resources/resources.qrc
	    resources/project.rc
        )
    endif()
endif()

target_link_libraries(websockets_client PRIVATE oclero::qlementine)
target_link_libraries(websockets_client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(websockets_client PRIVATE Qt${QT_VERSION_MAJOR}::WebSockets)

set_target_properties(websockets_client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "WebsocketsClient"
)

install(TARGETS websockets_client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(websockets_client)
endif()

target_deploy_qt(websockets_client)
