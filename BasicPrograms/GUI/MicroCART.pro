#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T22:08:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MicroCART
TEMPLATE = app

#QMAKE_CXXFLAGS += -std=c++0x -pthread

SOURCES +=\
        mainwindow.cpp \
    src/CLI.cpp \
    src/CommandInterpreter.cpp \
    src/Locator.cpp \
    src/QuadCommand.cpp \
    src/Transmitter.cpp \
    gui_runner.cpp \
    src/Logger.cpp \
    src/USBController.cpp

HEADERS  += mainwindow.h \
    src/CLI.h \
    src/CommandInterpreter.h \
    src/Locator.h \
    src/QuadCommand.h \
    src/Transmitter.h \
    src/Logger.h \
    src/Q_DebugStream.h \
    src/USBController.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    Images/Images.qrc \
    Images/Images.qrc

# ADD EXTERNAL LIBRARY LINKERS HERE
LIBS += -lpthread \
         -lquat \
         -lvrpnserver
