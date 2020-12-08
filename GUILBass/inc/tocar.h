#ifndef TOCAR_H
#define TOCAR_H

#include <QDialog>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <clasemidi.h>
//#include "qguitarview.h"

#define DEBUG

#define	TRUE    1
#define	FALSE   0

#define EXITO   1
#define ERROR   0

#define ON      1
#define OFF     0

#define TIMER1  1

#define SIN_NOTA    0
#define NOTA1       '1'   //aca va el numero que represente a lo que llega por puerto serie al llegar la nota de valor mas chico
#define NOTA28      '9'  // "" de valor mas grande  (estoy presuponiendo que cada nota tiene valor consecutivo)
#define TOTAL_NOTAS 52
#define NOTA_MAX    28

#define SONG_FILE_NAME "cancionGrabada.csv" //agregar el nombre que sea con el path deseado

#define TIMER_TIME_ 100


//////////////////////////////////   DEFINES PARA MANEJAR TRAMA MAS COMODAMENTE    //////////////////////////////////////
#define PRIMER_MITAD_    240 // 240 = 11110000
#define ULTIMA_MITAD_    15  // 15  = 00001111
#define INICIO_TRAMA_    10  // 10  = 1010 que es el inicio de trama que esta en el primer byte
//#define FIN_TRAMA_       13  // 13  = 1101 que es fin de trama 101 mas el bit de paridad 1000
#define FIN_TRAMA_     5   // 5   = 0101 que es el fin de trama que esta en el segundo byte
#define INICIO_TRAMA_OK_ ( ( ( ((uint8_t)data[0]) & PRIMER_MITAD_ ) >>4) == (uint8_t)INICIO_TRAMA_ )
#define FIN_TRAMA_OK_    ( ( ((uint8_t)data[1]) & ULTIMA_MITAD_ ) == (uint8_t)FIN_TRAMA_ )

#define BIT1_MITAD1_ ( ( ((uint8_t)data[0]) & PRIMER_MITAD_ ) >>4)
#define BIT1_MITAD2_ ( ((uint8_t)data[0]) & ULTIMA_MITAD_ )
#define BIT2_MITAD1_ ( ( ((uint8_t)data[1]) & PRIMER_MITAD_ ) >>4)
#define BIT2_MITAD2_ ( ((uint8_t)data[1]) & ULITMA_MITAD_ )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

};

#endif // TOCAR_H
