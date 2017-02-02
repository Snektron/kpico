TARGET = $$qtLibraryTarget(kpico)
TEMPLATE = lib
INCLUDEPATH += include ../Pico80/include
CONFIG += plugin c++11 silent
QT += qml quick gui opengl

SOURCES += \
    src/KPico.cpp \
    src/EmulatorContext.cpp \
    src/emu/Emulator.cpp \
    src/emu/EmulatorThread.cpp \
    src/emu/Asic.cpp \
    src/emu/Log.cpp \
    src/gui/Lcd.cpp \
    src/gui/LcdRenderer.cpp \
    src/gui/LcdFrameBuffer.cpp \
    src/emu/debug/CommandHandler.cpp \
    src/emu/debug/InstructionModel.cpp \
    src/KPicoQml.cpp \
    src/emu/debug/DebuggerQml.cpp \
    src/emu/debug/Debugger.cpp \
    src/emu/debug/Disassembler.cpp

HEADERS += \
    include/KPico.h \
    include/EmulatorContext.h \
    include/emu/Emulator.h \
    include/emu/EmulatorThread.h \
    include/emu/Asic.h \
    include/emu/Log.h \
    include/gui/LcdFrameBuffer.h \
    include/gui/Lcd.h \
    include/gui/LcdRenderer.h \
    include/emu/debug/CommandHandler.h \
    include/emu/debug/InstructionModel.h \
    include/KPicoQml.h \
    include/emu/debug/DebuggerQml.h \
    include/emu/debug/Debugger.h \
    include/emu/debug/Instruction.h \
    include/emu/debug/Disassembler.h

DISTFILES += \
    kpico.json \
    textures/test.png

RESOURCES += \
	rsrc.qrc

win32: {
	DESTDIR = ../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/plugins
	INCLUDEPATH += 3rdparty/scas/include
	INCLUDEPATH += 3rdparty/z80e/include
	DEFINES += NOLINK
	LIBS += -L"$$PWD/3rdparty/scas/bin" -lscas
	LIBS += -L"$$PWD/3rdparty/z80e/bin" -lz80e
}
unix: {
	DESTDIR = ../build-Pico80-Desktop-Debug/plugins
	LIBS += -lscas -lz80e
}
