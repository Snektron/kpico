TARGET = $$qtLibraryTarget(kpico)
TEMPLATE = lib
INCLUDEPATH += include ../Pico80/include
CONFIG += plugin
QT += opengl
win32 {
    DESTDIR = ../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/plugins
}
unix {
    DESTDIR = ../build-Pico80-Desktop-Debug/plugins
}
#LIBS += -lscas -lz80e

SOURCES += \
    src/KPico.cpp

HEADERS += \
    include/KPico.h

DISTFILES += \
    kpico.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
