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

/**
 * \fn       unsigned int getSalidasDisponibles()
 * \details  Devuelve la cantidad de salidas midi disponibles
 * \param    void
 * \return   cantidad de puertos
*/

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

/**
 * \fn       QString getNombreSalida(unsigned int n)
 * \details  Devuelve el nombre de la salida midi con cierto indice
 * \param    unsigned int indice
 * \return   nombre de la salida
*/

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

/**
 * \fn       QString getNombreSalida(unsigned int n)
 * \details  Devuelve el nombre de la salida midi con cierto indice
 * \param    unsigned int indice
 * \return   nombre de la salida
*/

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

/**
 * \fn       uint8_t abrirPuerto(unsigned int port)
 * \details  Abre un puerto de salida MIDI con un determinado indice y
 *           y lo asigna como puerto a utilizar por la clase
 * \param    unsigned int port
 * \return   0: el puerto se abrio  1: hubo algun error
*/

uint8_t ClaseMIDI::abrirPuerto(unsigned int port) {
    if (out != nullptr && port < getSalidasDisponibles()) {
        out->openPort(port);
        return 0;
    }
    return 1;
}

/**
 * \fn       uint8_t cerrarPuerto()
 * \details  Cierra el puerto de salida utilizado por la clase
 * \param    void
 * \return   0: se cerro correctamente  1: hubo algun error
*/

uint8_t ClaseMIDI::cerrarPuerto() {
    if (out != nullptr && out->isPortOpen()) {
        out->closePort();
        return 0;
    }
    return 1;
}

/**
 * \fn       uint8_t estaAbuerto()
 * \details  Verifica si el puerto de salida asignado esta abierto
 * \param    void
 * \return   0: no esta abierto     1: esta abierto
*/

uint8_t ClaseMIDI::estaAbierto() {
    if (out != nullptr) {
        return out->isPortOpen();
    }
    return 0;
}

/**
 * \fn       uint8_t inicializarGS()
 * \details  Envia por el puerto una serie de bytes que definen
 *           un mensaje MIDI SysEx (System Exclusive), en este
 *           caso inicializan el sintetizador a utilizar para
 *           manejar los bancos de sonidos de acuerdo a la spec
 *           de Roland GS (el synth a utilizar DEBE SOPORTAR
 *           Roland GS, sino solo pueden utilizarse los 128
 *           instrumentos provistos por la spec GENERAL MIDI v1)
 * \param    void
 * \return   0: se envio el mensaje     1: hubo algun error
*/

uint8_t ClaseMIDI::inicializarGS() {
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

/**
 * \fn       uint8_t enviarNoteOn(uint8_t ch, uint8_t mode, uiunt8_t vel)
 * \details  Envía un mensaje MIDI Note ON para determinado canal, nota,
 *           y con una velocidad especifica
 * \param    uint8_t canal, uint8_t nota, uint8_t velocidad = 127 (usualmente 127)
 * \return   0: enviado correctamente       1: hubo error
*/

uint8_t ClaseMIDI::enviarNoteOn(uint8_t ch, uint8_t note, uint8_t vel = 127) {
    QByteArray arr;
    arr.clear();
    if (ch > 0x0F || note > 0x7F || vel > 0x7F) return 1;
    arr.append(0x90 + ch);
    arr.append(note);
    arr.append(vel);
    return enviarMensaje(arr);
}

/**
 * \fn       uint8_t enviarNoteOff(uint8_t ch, uint8_t note)
 * \details  Envia un mensaje MIDI Note OFF para determinado canal y nota
 * \param    uint8_t canal, uint8_t nota
 * \return   0: enviado correctamente       1: hubo error
*/

uint8_t ClaseMIDI::enviarNoteOff(uint8_t ch, uint8_t note) {
    QByteArray arr;
    arr.clear();
    if (ch > 0x0F || note > 0x7F) return 1;
    arr.append(0x90 + ch);
    arr.append(note);
    arr.append(static_cast<uint8_t>(0x00));
    return enviarMensaje(arr);
}

/**
 * \fn       uint8_t enviarProgramChange(uint8_t ch, uint8_t prgm)
 * \details  Cambia el programa MIDI seleccionado (el banco de sonido principal)
 * \param    uint8_t canal, uint8_t numero de programa
 * \return   0: enviado correctamente       1: error al enviar
*/

uint8_t ClaseMIDI::enviarProgramChange(uint8_t ch, uint8_t prgm) {
    QByteArray arr;
    arr.clear();
    if (ch > 0x0F || prgm > 0x7F) return 1;
    arr.append(0xC0 + ch);
    arr.append(prgm);
    return enviarMensaje(arr);
}

/**
 * \fn       uint8_t enviarControlChange(uint8_t canal, uint8_t byte_1, uint8_t byte_2)
 * \details  Envia un mensaje MIDI Control CHANGE (cambio de control). Sirve para muchas
 *           cosas ya que depende del control que modifiquemos depende del efecto que
 *           presente el sintetizador. Principalmente se usa en la spec GS para el cambio
 *           entre bancos de sonido secundarios que ofrecen mas variaciones de los sonidos
 * \param    uint8_t canal, uint8_t primer byte de info, uint8_t segundo byte de info
 * \return   0: envio correcto      1: envio con error
*/

uint8_t ClaseMIDI::enviarControlChange(uint8_t ch, uint8_t byte_1, uint8_t byte_2) {
    QByteArray arr;
    arr.clear();
    if (ch > 0x0F || byte_1 > 0x7F || byte_2 > 0x7F) return 1;
    arr.append(0xB0 + ch);
    arr.append(byte_1);
    arr.append(byte_2);
    return enviarMensaje(arr);
}

/**
 * \fn       uint8_t enviarMensaje(QByteArray & msg)
 * \details  Envia un determinado numero de bytes por el puerto MIDI de Salida
 * \param    QBytreArray & array de bytes
 * \return   0: envio correcto      1: envio con error
*/

uint8_t ClaseMIDI::enviarMensaje(QByteArray & msg) {
    if (!out->isPortOpen()) {
        out->sendMessage(reinterpret_cast<const uint8_t *>(msg.constData()), msg.length());
        return 0;
    }
    return 1;
}

