#include "clasemidi.h"

ClaseMIDI::ClaseMIDI() {
    // La libreria RtMidi especifica que el codigo
    // de instanciamiento y de funciones
    // debe estar dentro de bloques try-catch

    try {
        out = new RtMidiOut();
    } catch (RtMidiError &e) {
        e.printMessage();
        out = nullptr;
    }
}

ClaseMIDI::~ClaseMIDI() {
    delete out;
}

unsigned int ClaseMIDI::getSalidasDisponibles() {
    unsigned int var = 0;
    if (out != nullptr) {
        try {
            var = out->getPortCount();
        } catch (RtMidiError &e) {
            e.printMessage();
        }
    }
    return var;
}

QString ClaseMIDI::getNombreSalida(unsigned int n) {
    QString str = "";
    if (out != nullptr) {
        try {
            str = out->getPortName(n).c_str();
        } catch (RtMidiError &e) {
            e.printMessage();
        }
    }

    return str;
}

QStringList ClaseMIDI::getNombresSalidas() {
    QStringList strl;
    strl.clear();
    if (out != nullptr) {
        for (unsigned int i=0; i<getSalidasDisponibles(); i++) {
            strl.append(getNombreSalida(i));
        }
    }
    return strl;
}

uint8_t ClaseMIDI::abrirPuerto(unsigned int port) {
    if (out != nullptr && port < getSalidasDisponibles()) {
        out->openPort(port);
        return 0;
    }
    return 1;
}

uint8_t ClaseMIDI::inicializarGS(unsigned int port) {
    //Reinicio el synth en modo GS
    //0xF0, 0x41, 0x10, 0x42, 0x12, 0x40, 0x00, 0x7F, 0x00, 0x41, 0xF7
    //Estos bytes vienen del PDF de Roland de la especificacion GS
    QByteArray arr;
    arr.clear();
    arr.push_back(0xF0);
    arr.push_back(0x41);
    arr.push_back(0x10);
    arr.push_back(0x42);
    arr.push_back(0x12);
    arr.push_back(0x40);
    arr.push_back(static_cast<uint8_t>(0x00));
    arr.push_back(0x7f);
    arr.push_back(static_cast<uint8_t>(0x00));
    arr.push_back(0x41);
    arr.push_back(0xF7);
   return enviarMensaje(arr);
}

uint8_t ClaseMIDI::enviarNoteOn(uint8_t ch, uint8_t note, uint8_t vel) {
    QByteArray arr;
    arr.clear();
    if (ch < 0x10 || note < 0x80) return 1;
    arr.append(0x90 + ch);
    arr.append(note);
    arr.append(vel);
    enviarMensaje(arr);
    return 0;
}

uint8_t ClaseMIDI::enviarNoteOff(uint8_t ch, uint8_t note) {
    QByteArray arr;
    arr.clear();
    if (ch < 0x10 || note < 0x80) return 1;
    arr.append(0x90 + ch);
    arr.append(note);
    arr.append(static_cast<uint8_t>(0x00));
    enviarMensaje(arr);
    return 0;
}

uint8_t ClaseMIDI::enviarProgramChange(uint8_t ch, uint8_t prgm) {
    QByteArray arr;
    arr.clear();
    if (ch < 0x10 || prgm < 0x80) return 1;
    arr.append(0xC0 + ch);
    arr.append(prgm);
    enviarMensaje(arr);
    return 0;
}

uint8_t ClaseMIDI::enviarControlChange(uint8_t ch, uint8_t byte_1, uint8_t byte_2) {
    QByteArray arr;
    arr.clear();
    if (ch < 0x10 || byte_1 < 0x80 || byte_2 < 0x80) return 1;
    arr.append(0xB0 + ch);
    arr.append(byte_1);
    arr.append(byte_2);
    enviarMensaje(arr);
    return 0;
}

uint8_t ClaseMIDI::enviarMensaje(QByteArray msg) {
    if (out->isPortOpen()) {
        out->sendMessage(reinterpret_cast<const uint8_t *>(msg.constData()), msg.length());
        return 0;
    }
    return 1;
}

