QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = ../../Minesweeper_Game_Qt_Cplusplus/executable/Minesweeper

SOURCES += \
    game_engine.cpp \
    main.cpp \
    game_dimensions_dialog_window.cpp \
    game_window.cpp \
    coordinates.cpp \
    field.cpp \
    end_game_dialog.cpp

HEADERS += \
    game_dimensions_dialog_window.h \
    game_engine.h \
    game_window.h \
    coordinates.h \
    end_game_dialog.h \
    field.h \
    common.h

FORMS += \
    game_dimensions_dialog_window.ui \
    game_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
