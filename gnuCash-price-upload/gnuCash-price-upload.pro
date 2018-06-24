# Project file for gnuCash application

TARGET = gnuCash-price-upload
CONFIG += console debug
TEMPLATE = app

QT += core sql network
QT -= gui

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

DISTFILES += \
    ../README

win32:CONFIG(release, debug|release) {
  LIBS += -L../../Library/Library/win32/debug -lGCL
  LIBS += -L../../Library/Library/win32/debug -lMCL
  LIBS += -L../../Library/Library/win32/debug -lSCL
  LIBS += -L../../Library/Library/win32/debug -lQCL
  LIBS += -L../../Library/Library/win32/debug -lboost_filesystem
  LIBS += -L../../Library/Library/win32/debug -lboost_system
  LIBS += -L../../Library/Library/win32/debug -lboost_thread
  LIBS += -L../../Library/Library/win32/debug -lboost_chrono
  LIBS += -L../../Library/Library/unix/debug -lboost_program_options
}
else:win32:CONFIG(debug, debug|release) {
  LIBS += -L../../Library/Library/win32/debug -lGCL
  LIBS += -L../../Library/Library/win32/debug -lMCL
  LIBS += -L../../Library/Library/win32/debug -lSCL
  LIBS += -L../../Library/Library/win32/debug -lQCL
  LIBS += -L../../Library/Library/win32/debug -lboost_filesystem
  LIBS += -L../../Library/Library/win32/debug -lboost_system
  LIBS += -L../../Library/Library/win32/debug -lboost_thread
  LIBS += -L../../Library/Library/win32/debug -lboost_chrono
  LIBS += -L../../Library/Library/unix/debug -lboost_program_options
}
else:unix:CONFIG(debug, debug|release) {
  LIBS += -L../GCL -lGCL
  LIBS += -L../MCL -lMCL
  LIBS += -L../QCL -lQCL
  LIBS += -L../SCL -lSCL
  LIBS += -L../../../Library/Library -lboost_filesystem
  LIBS += -L../../../Library/Library/unix/debug -lboost_system
  LIBS += -L../../Library/Library/unix/debug -lboost_thread
  LIBS += -L../../Library/Library/unix/debug -lboost_chrono
  LIBS += -L../../Library/Library/unix/debug -lboost_program_options
}
else:unix:CONFIG(release, debug|release) {
  LIBS += -L../GCL -lGCL
  LIBS += -L../MCL -lMCL
  LIBS += -L../QCL -lQCL
  LIBS += -L../SCL -lSCL
  LIBS += -L../../../Library/Library -lboost_filesystem
  LIBS += -L../../../Library/Library/unix/debug -lboost_system
  LIBS += -L../../Library/Library/unix/debug -lboost_thread
  LIBS += -L../../Library/Library/unix/debug -lboost_chrono
  LIBS += -L../../Library/Library/unix/debug -lboost_program_options
}


