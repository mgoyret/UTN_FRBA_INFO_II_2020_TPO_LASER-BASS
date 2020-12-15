#ifndef TOCAR_H
#define TOCAR_H

#include <QDialog>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <clasemidi.h>
//#include "qguitarview.h"

#define DEBUG

#define SONG_FILE_NAME "cancionGrabada.csv" //agregar el nombre que sea con el path deseado

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NOTAS_BASE 40
#define NOTAS_DESP_POR_CUERDA 5
#define NOTAS_DESP_POR_TRASTE 1

namespace Ui {
class Tocar;
}

class Tocar : public QDialog
{
    Q_OBJECT

public:
    explicit Tocar(QWidget *parent = nullptr);
    ~Tocar();
    void setPuerto( QSerialPort* );
    void setPuertoMidi(ClaseMIDI* puertoExt);

    //inline void setPuertoMidi(ClaseMIDI* puertoExt){puertoMidi=puertoExt;}
    void procesarNota( QByteArray );
    uint8_t tramaOk( QByteArray );
    uint8_t tramaInfo( QByteArray );
    void setNotaCorrecta(void);
    void mostrarNota(uint8_t nota);


private slots:
    void on_datosRecibidos();


private:
    Ui::Tocar *ui;
    char notaTocada;
    QSerialPort *puerto;
    ClaseMIDI *puertoMidi;
    QMetaObject::Connection conection; //almacena el valor retornado por connect() para podes desconectar con disconnect()
    //void setColor(const char * estado);
    QByteArray bufferSerie;
    void validarDatos();
    void procesarNotaATocar(QByteArray);
    void mostrarNota(char nota);
    int  notaACuerdaYNota(uint8_t nota);
    uint8_t notaANotaMidi(uint8_t nota);

};

#endif // TOCAR_H
