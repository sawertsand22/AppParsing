    cmake_minimum_required(VERSION 3.5)

    project(AppParsing VERSION 0.2.5 LANGUAGES CXX)

    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
    find_package(Boost 1.40 COMPONENTS program_options REQUIRED)
    find_package(CURL REQUIRED)
    find_package(Qt5 COMPONENTS WebKitWidgets REQUIRED)
    find_package(LibXml2 REQUIRED)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/pat ${LIBXML2_INCLUDE_DIR})
    set(WEB_ENGINE_WIDGETS_LIBRARIES "/home/sawert/Downloads/qtwebengine-5.15.15/src/webenginewidgets")
    include_directories(${WEB_ENGINE_WIDGETS_LIBRARIES})

    set(MYSQL_CONNECTOR_CPP_LIBRARIES "/usr/lib/x86_64-linux-gnu/libmysqlcppconn.so")
    include_directories(${MYSQL_CONNECTOR_CPP_INCLUDE_DIRS})
    set(PROJECT_SOURCES
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            database.cpp
            database.h
            database.ui
            br.html
            index.html
    )

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(AppParsing
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET AppParsing APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    else()
        if(ANDROID)
            add_library(AppParsing SHARED
                ${PROJECT_SOURCES}
            )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        else()
            add_executable(AppParsing
                ${PROJECT_SOURCES}
            )
        endif()
    endif()

    target_link_libraries(AppParsing  Qt${QT_VERSION_MAJOR}::Widgets)

    set_target_properties(AppParsing PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    target_link_libraries(AppParsing Qt5::Core)
    target_link_libraries(AppParsing CURL::libcurl)
    target_link_libraries(AppParsing Boost::program_options)
      target_link_libraries(AppParsing ${MYSQL_CONNECTOR_CPP_LIBRARIES})
    target_link_libraries(AppParsing Qt5::WebKitWidgets)
    target_link_libraries(AppParsing ${WEB_ENGINE_WIDGETS_LIBRARIES})
    target_link_libraries(AppParsing ${LIBXML2_LIBRARIES})
    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(AppParsing)
    endif()
