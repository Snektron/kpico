TARGET = $$qtLibraryTarget(kpico)
TEMPLATE = lib
INCLUDEPATH += include ../picore/include
CONFIG += plugin c++11 silent
QT += qml quick gui opengl
LIBS += -lscas -lz80e

SOURCES += \
    src/KPico.cpp \
    src/gui/Display.cpp \
    src/gui/DisplayFrameBuffer.cpp \
    src/gui/DisplayRenderer.cpp \
    src/emu/Asic.cpp

HEADERS += \
    include/KPico.h \
    include/gui/Display.h \
    include/gui/DisplayFrameBuffer.h \
    include/gui/DisplayRenderer.h \
    include/emu/Asic.h \
    include/emu/AsicFactory.h

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
