TARGET = $$qtLibraryTarget(kpico)
TEMPLATE = lib
INCLUDEPATH += include ../Pico80/include
CONFIG += plugin c++11 silent
QT += qml quick gui opengl
LIBS += -lscas -lz80e

SOURCES += \
	src/KPico.cpp \
    src/EmulatorContext.cpp \
    src/gui/Display.cpp \
    src/gui/DisplayFrameBuffer.cpp \
    src/gui/DisplayRenderer.cpp

HEADERS += \
	include/KPico.h \
    include/EmulatorContext.h \
    include/gui/Display.h \
    include/gui/DisplayFrameBuffer.h \
    include/gui/DisplayRenderer.h

DISTFILES += \
    kpico.json \
    textures/test.png

win32: DESTDIR = ../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/plugins
unix: DESTDIR = ../build-Pico80-Desktop-Debug/plugins

RESOURCES += \
    rsrc.qrc
