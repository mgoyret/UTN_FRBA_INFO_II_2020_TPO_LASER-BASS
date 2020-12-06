#ifndef TOCAR_H
#define TOCAR_H

#include <QDialog>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
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



//////////////////////////////////   DEFINES PARA MANEJAR TRAMA MAS COMODAMENTE    //////////////////////////////////////
#define PRIMER_MITAD    240 // 240 = 11110000
#define ULTIMA_MITAD    15  // 15  = 00001111
#define INICIO_TRAMA    10  // 10  = 1010 que es el inicio de trama que esta en el primer byte
#define FIN_TRAMA       13  // 13  = 1101 que es fin de trama 101 mas el bit de paridad 1000
//#define FIN_TRAMA     5   // 5   = 0101 que es el fin de trama que esta en el segundo byte
#define INICIO_TRAMA_OK ( ( ( ((uint8_t)datos[0]) & PRIMER_MITAD ) >>4) == (uint8_t)INICIO_TRAMA )
#define FIN_TRAMA_OK    ( ( ((uint8_t)datos[1]) & ULTIMA_MITAD ) == (uint8_t)FIN_TRAMA )

#define BIT1_MITAD1 ( ( ((uint8_t)datos[0]) & PRIMER_MITAD ) >>4)
#define BIT1_MITAD2 ( ((uint8_t)datos[0]) & ULTIMA_MITAD )
#define BIT2_MITAD1 ( ( ((uint8_t)datos[1]) & PRIMER_MITAD ) >>4)
#define BIT2_MITAD2 ( ((uint8_t)datos[1]) & ULITMA_MITAD )
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
    void procesarNota( QByteArray );
    uint8_t tramaOk( QByteArray );
    uint8_t tramaInfo( QByteArray );
    void setNotaCorrecta(void);


private slots:
  //  void on_datosRecibidos();
    void puertoSerieRcv_handler( void );


private:
    Ui::Tocar *ui;
    uint8_t notaTocada;
    QSerialPort *puerto;
    QMetaObject::Connection conection; //almacena el valor retornado por connect() para podes desconectar con disconnect()
    void setColor(const char * estado);
};

#endif // TOCAR_H
