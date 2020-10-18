#ifndef GRABAR_H
#define GRABAR_H

#include <stdio.h>
#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QSerialPort>

#include <QTimer>


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

#define SONG_FILE_NAME "cancionGrabada.csv" //agregar el nombre que sea con el path deseado

#define TIMER_TIME 500

#define PRIMER_MITAD    240 // 240 = 11110000
#define ULTIMA_MITAD    15  // 15 = 00001111
#define INICIO_TRAMA    10  // 10 == 1010 que es el inicio de trama que esta en el primer byte
#define FIN_TRAMA       5   // 5 == 0101 que es el fin de trama que esta en el segundo byte
#define INICIO_TRAMA_OK ( ( (dataRcv[0])&PRIMER_MITAD ) == INICIO_TRAMA )
#define FIN_TRAMA_OK    ( ( (dataRcv[1])%ULTIMA_MITAD ) ==  FIN_TRAMA )

typedef struct noteBuffer{
    uint32_t cntr;
    uint8_t note;
}noteBuffer;

typedef struct songBuffer{
    uint32_t total_cntr;
    noteBuffer *note_st;
} songBuffer;

namespace Ui {
class Grabar;
}

class Grabar : public QDialog
{
    Q_OBJECT

public:
    explicit Grabar( QWidget *parent = nullptr );

    ~Grabar( void );

    void inicializar( void );
    void guardarNota( void );
    void iniciarTimer( void );
    uint8_t guardarCancion( void );
    uint8_t prosesarNota( QByteArray );
    void desconectarPuerto();
    void set_puerto(QSerialPort*);
    void monitoreo();
    uint8_t tramaOk(QByteArray);
    uint8_t tramaInfo(QByteArray);

private slots:
    void on_PBrec_clicked( void );
    void on_PBfinRec_clicked( void );
    void timer_handler( void );
    void puertoSerieRcv_handler( void );


private:
    Ui::Grabar *ui;
    uint8_t     grabacion; //flag para saber cuando cortar loop de timers en cuyos handlers se realiza el proceso de grabado
    uint8_t     notaTocada;
    uint8_t     status;
    QFile       songFile;
    songBuffer  recBuf;
    QSerialPort *puerto;
    QMetaObject::Connection conection; //almacena el valor retornado por connect() para podes desconectar con disconnect()
};

#endif // GRABAR_H
