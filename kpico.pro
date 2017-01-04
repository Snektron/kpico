TARGET = $$qtLibraryTarget(kpico)
TEMPLATE = lib
INCLUDEPATH += include ../picore/include
CONFIG += plugin c++11 silent
QT += qml quick gui opengl

SOURCES += \
    src/KPico.cpp

HEADERS += \
    include/KPico.h

DISTFILES += \
    kpico.json \
    textures/test.png

win32 {
    DESTDIR = ../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/plugins
    LIBS += -L../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ -lpicored
}

unix {
    DESTDIR = ../build-Pico80-Desktop-Debug/plugins
    LIBS += -L../build-Pico80-Desktop-Debug/ -lpicore
}

RESOURCES += \
    rsrc.qrc
