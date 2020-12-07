#ifndef JUGAR_H
#define JUGAR_H

#include <QDialog>
#include <QSerialPort>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "qguitarview.h"
#include "dialogjugar.h"
#include "inc/qnoteview.h"
#include "parserpuntaje.h"
#include <clasemidi.h>
#define DEBUG

#define	TRUE_    1
#define	FALSE_   0

#define EXITO_   1
#define ERROR_   0

#define ON_      1
#define OFF_     0

#define TIMER1_  1

#define SIN_NOTA_    0
#define NOTA1_       '1'   //aca va el numero que represente a lo que llega por puerto serie al llegar la nota de valor mas chico
#define NOTA28_      '9'  // "" de valor mas grande  (estoy presuponiendo que cada nota tiene valor consecutivo)
#define TOTAL_NOTAS_ 52
#define NOTA_MAX_    28

#define SONG_FILE_NAME_ "cancionGrabada.csv" //agregar el nombre que sea con el path deseado

#define TIMER_TIME_ 100


//////////////////////////////////   DEFINES PARA MANEJAR TRAMA MAS COMODAMENTE    //////////////////////////////////////
#define PRIMER_MITAD_    240 // 240 = 11110000
#define ULTIMA_MITAD_    15  // 15  = 00001111
#define INICIO_TRAMA_    10  // 10  = 1010 que es el inicio de trama que esta en el primer byte
#define FIN_TRAMA_     5   // 5   = 0101 que es el fin de trama que esta en el segundo byte
#define INICIO_TRAMA_OK_ ( ( ( ((uint8_t)data[0]) & PRIMER_MITAD_ ) >>4) == (uint8_t)INICIO_TRAMA_ )
#define FIN_TRAMA_OK_    ( ( ((uint8_t)data[1]) & ULTIMA_MITAD_ ) == (uint8_t)FIN_TRAMA_ )

#define BIT1_MITAD1_ ( ( ((uint8_t)data[0]) & PRIMER_MITAD_ ) >>4)
#define BIT1_MITAD2_ ( ((uint8_t)data[0]) & ULTIMA_MITAD_ )
#define BIT2_MITAD1_ ( ( ((uint8_t)data[1]) & PRIMER_MITAD_ ) >>4)
#define BIT2_MITAD2_ ( ((uint8_t)data[1]) & ULITMA_MITAD_ )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Ui {
class Jugar;
}

class Jugar : public QDialog
{
    Q_OBJECT

public:
    explicit Jugar(QWidget *parent = nullptr, QString nombre = "");
    ~Jugar();
    void setPuerto( QSerialPort* );
    void procesarNota( QByteArray );
    uint8_t tramaOk(unsigned char* );
    uint8_t tramaInfo( unsigned char* );
    void LeerArchivo(void);
    void setNotaCorrecta(void);
    void setNotaIncorrecta(void);

private slots:
    void on_datosRecibidos();
    void monitoreoPuntos();

private:
    Ui::Jugar *ui;
    uint8_t notaTocada;
    int posicion = 0;
    ParserPuntaje puntajes;
    QString nombreCancion;
    QSerialPort *puerto;
    QStringList listaNota;
    QMetaObject::Connection conection; //almacena el valor retornado por connect() para podes desconectar con disconnect()
    //funcion para el line_edit Puntos
    QByteArray bufferSerie;
    ClaseMIDI puertoMidi;

    void validarDatos();
    void procesarNotaATocar(QByteArray);

};

#endif // JUGAR_H
