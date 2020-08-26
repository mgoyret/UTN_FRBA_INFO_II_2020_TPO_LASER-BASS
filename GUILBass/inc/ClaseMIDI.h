#ifndef CLASEMIDI_H
#define CLASEMIDI_H

// Defines para errores al invocar la libreria

#define CM_NOERR 0
#define CM_ECREAT 1
#define CM_ECOUNT 2
#define CM_ENAME 3

#include <RtMidi.h>
#include <QString>
#include <iostream>
#include <QStringList>
#include <QByteArray>

typedef RtMidiOut SalidaMIDI;
typedef unsigned char uint8_t;

class ClaseMIDI {
    private:

    SalidaMIDI *out;


    public:

    ClaseMIDI();

    ~ClaseMIDI();

    //Salida
    unsigned int getSalidasDisponibles();
    QString getNombreSalida(unsigned int);
    QStringList getNombresSalidas();
    uint8_t abrirPuerto(unsigned int);

    //Funciones para mensajes comunes
    uint8_t enviarControlChange(uint8_t, uint8_t, uint8_t);
    uint8_t enviarProgramChange(uint8_t, uint8_t);
    uint8_t enviarNoteOn(uint8_t, uint8_t, uint8_t);
    uint8_t enviarNoteOff(uint8_t, uint8_t);
    uint8_t enviarMensaje(QByteArray);

};

#endif // CLASEMIDI_H
