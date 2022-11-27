cmake_minimum_required(VERSION 3.10)

project(Minesweeper LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(INCLUDES_DIR ${PROJECT_ROOT}/inc)
set(SOURCES_DIR ${PROJECT_ROOT}/src)
set(UI_FORMS_DIR ${PROJECT_ROOT}/ui_forms)
set(RESOURCE_FILES_DIR ${PROJECT_ROOT}/resource_files)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
        ${INCLUDES_DIR}/common.h
        ${INCLUDES_DIR}/view/game_main_window.h ${SOURCES_DIR}/view/game_main_window.cpp ${UI_FORMS_DIR}/game_main_window.ui
        ${INCLUDES_DIR}/view/game_dimensions_dialog_window.h ${SOURCES_DIR}/view/game_dimensions_dialog_window.cpp ${UI_FORMS_DIR}/game_dimensions_dialog_window.ui
        ${INCLUDES_DIR}/view/end_game_dialog.h ${SOURCES_DIR}/view/end_game_dialog.cpp
        ${INCLUDES_DIR}/view/field_button.h ${SOURCES_DIR}/view/field_button.cpp
        ${INCLUDES_DIR}/model.h ${SOURCES_DIR}/model.cpp
        ${INCLUDES_DIR}/field.h ${SOURCES_DIR}/field.cpp
        ${INCLUDES_DIR}/coordinates.h ${SOURCES_DIR}/coordinates.cpp
        ${INCLUDES_DIR}/minefield.h ${SOURCES_DIR}/minefield.cpp
        ${INCLUDES_DIR}/fields_manager.h ${SOURCES_DIR}/fields_manager.cpp
        ${INCLUDES_DIR}/mines_generator.h ${SOURCES_DIR}/mines_generator.cpp
        ${INCLUDES_DIR}/fields_uncoverer.h ${SOURCES_DIR}/fields_uncoverer.cpp src/minesweeper.cpp inc/minesweeper.h src/controller.cpp inc/controller.h)

add_library(libMinesweeper ${SOURCE_FILES})
target_include_directories(libMinesweeper PUBLIC ${INCLUDES_DIR})
target_link_libraries(libMinesweeper Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(Minesweeper WIN32 ${SOURCES_DIR}/main.cpp ${RESOURCE_FILES_DIR}/images.qrc)
target_link_libraries(Minesweeper libMinesweeper)

if (WIN32)
    set_target_properties(Minesweeper PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_windows)
elseif (UNIX)
    set_target_properties(Minesweeper PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_linux)
endif (WIN32)

add_subdirectory(tests)
