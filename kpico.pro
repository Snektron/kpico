TARGET = $$qtLibraryTarget(kpico)
TEMPLATE = lib
INCLUDEPATH += include ../Pico80/include
CONFIG += plugin
QT += opengl
DESTDIR = ../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/plugins

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
