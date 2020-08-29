QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/grabar.cpp \
    src/mainwindow.cpp \
    src/menujugar.cpp \
    src/tocar.cpp \
    lib/RtMidi/RtMidi.cpp

HEADERS += \
    inc/mainwindow.h \
    inc/menujugar.h \
    inc/tocar.h \
    inc/grabar.h
    lib/RtMidi/RtMidi.h \

FORMS += \
    forms/mainwindow.ui \
    forms/menujugar.ui \
    forms/tocar.ui \
    forms/grabar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    GUIResources.qrc

# Reglas para compilacion de librerías
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
  #message("Solo sale en linux")
}

# Includepath para rtmidi
INCLUDEPATH += lib/RtMidi/
