TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT += core

SOURCES += \
        main.cpp \
        src/RtMidi.cpp

HEADERS += \
    src/RtMidi.h

INCLUDEPATH += src/

win32 {
  DEFINES += __WINDOWS_MM__ \
             _WIN32 \
             WIN32
  LIBS += -lwinmm
  QMAKE_LFLAGS += -static -static-libgcc
}

unix {
  DEFINES += __LINUX_ALSA__
  LIBS += -lasound \
          -lpthread
}

RESOURCES += \
    resources.qrc
