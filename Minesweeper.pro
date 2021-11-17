QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = ../../Minesweeper_Game_Qt_Cplusplus/executable_windows/Minesweeper

SOURCES += \
    src/main.cpp \
    src/game_engine.cpp \
    src/game_dimensions_dialog_window.cpp \
    src/game_window.cpp \
    src/coordinates.cpp \
    src/field.cpp \
    src/end_game_dialog.cpp

HEADERS += \
    inc/game_dimensions_dialog_window.h \
    inc/game_engine.h \
    inc/game_window.h \
    inc/coordinates.h \
    inc/end_game_dialog.h \
    inc/field.h \
    inc/common.h

FORMS += \
    ui_forms/game_dimensions_dialog_window.ui \
    ui_forms/game_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource_files/images.qrc
