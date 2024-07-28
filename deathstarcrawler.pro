QT += core gui
QT += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        src/_utilities/levelexporter.cpp \
        src/_utilities/levelimporter.cpp \
        src/_utilities/tilegraph.cpp \
        src/engine/character/attackingnonplayercharacter.cpp \
        src/engine/character/dynamicnonplayercharacter.cpp \
        src/engine/character/maincharacter.cpp \
        src/engine/character/staticnonplayercharacter.cpp \
        src/engine/management/attackcontroller.cpp \
        src/engine/management/controller.cpp \
        src/engine/management/guardcontroller.cpp \
        src/engine/management/stationarycontroller.cpp \
        src/engine/observer/active.cpp \
        src/engine/observer/passive.cpp \
        src/engine/tile/children/door.cpp \
        src/engine/tile/children/levelchanger.cpp \
        src/engine/tile/children/lootchest.cpp \
        src/engine/tile/children/pit.cpp \
        src/engine/tile/children/ramp.cpp \
        src/engine/tile/children/switch.cpp \
        src/main.cpp \
        src/_utilities/rowcolumn.cpp \
        src/engine/character/character.cpp \
        src/engine/management/dungeoncrawler.cpp \
        src/engine/management/level.cpp \
        src/engine/tile/children/floor.cpp \
        src/engine/tile/children/portal.cpp \
        src/engine/tile/children/wall.cpp \
        src/engine/tile/tile.cpp \
        src/ui/abstractui.cpp \
        src/ui/gui/_custompushbuttons/controlpushbutton.cpp \
        src/ui/gui/_customstatusbar/statusbar.cpp \
        src/ui/gui/graphicalui.cpp \
        src/ui/gui/mainwindow/mainwindow.cpp \
        src/ui/gui/_custompushbuttons/hoverpushbutton.cpp \
        src/ui/gui/startscreen/startscreen.cpp \
        src/ui/terminalui.cpp

HEADERS += \
    _config/guisettings.h \
    _config/textures.h \
    _config/settings.h \
    src/_extern/json.hpp \
    src/_utilities/levelexporter.h \
    src/_utilities/levelimporter.h \
    src/_utilities/rowcolumn.h \
    src/_utilities/list.hpp \
    src/_utilities/tilegraph.h \
    src/engine/character/attackingnonplayercharacter.h \
    src/engine/character/character.h \
    src/engine/character/dynamicnonplayercharacter.h \
    src/engine/character/maincharacter.h \
    src/engine/character/staticnonplayercharacter.h \
    src/engine/management/attackcontroller.h \
    src/engine/management/controller.h \
    src/engine/management/dungeoncrawler.h \
    src/engine/management/guardcontroller.h \
    src/engine/management/level.h \
    src/engine/management/stationarycontroller.h \
    src/engine/observer/active.h \
    src/engine/observer/passive.h \
    src/engine/tile/children/door.h \
    src/engine/tile/children/floor.h \
    src/engine/tile/children/levelchanger.h \
    src/engine/tile/children/lootchest.h \
    src/engine/tile/children/pit.h \
    src/engine/tile/children/portal.h \
    src/engine/tile/children/ramp.h \
    src/engine/tile/children/switch.h \
    src/engine/tile/children/wall.h \
    src/engine/tile/tile.h \
    src/ui/abstractui.h \
    src/ui/gui/_custompushbuttons/controlpushbutton.h \
    src/ui/gui/_customstatusbar/statusbar.h \
    src/ui/gui/graphicalui.h \
    src/ui/gui/mainwindow/mainwindow.h \
    src/ui/gui/_custompushbuttons/hoverpushbutton.h \
    src/ui/gui/startscreen/startscreen.h \
    src/ui/terminalui.h

FORMS += \
    src/ui/gui/mainwindow/mainwindow.ui \
    src/ui/gui/startscreen/startscreen.ui

QT += widgets

RESOURCES += \
    assets/assets.qrc \
    assets/assets.qrc
