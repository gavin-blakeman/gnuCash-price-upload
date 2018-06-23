# Project file for gnuCash application

QT += core
QT -= gui

TARGET = gnuCash
CONFIG += console

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++17 -static -static-libgcc #-save-temps=obj

#DESTDIR = ""
OBJECTS_DIR = "objects"
UI_DIR = "objects/ui"
MOC_DIR = "objects/moc"
RCC_DIR = "objects/rcc"

INCLUDEPATH +=  "../boost 1.62" \
                "../GCL" \
                "../QCL" \

SOURCES += \
    source/main.cpp \
    source/databaseGnuCash.cpp

HEADERS += \
    include/settings.h \
    include/databaseGnuCash.h

