#ifndef JUGAR_H
#define JUGAR_H

#include <QDialog>
#include <QSerialPort>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QTextStream>
#include "qguitarview.h"
#include "dialogjugar.h"
#include "qnoteview.h"
#include "parserpuntaje.h"
#include <clasemidi.h>
#include <dialogpuntajes.h>

#define DEBUG

#define	TRUE_    1
#define	FALSE_   0

#define EXITO_   1
#define ERROR_   0

#define ON_      1
#define OFF_     0

#define SIN_NOTA_    0
#define NOTA1_       '1'   //aca va el numero que represente a lo que llega por puerto serie al llegar la nota de valor mas chico
#define NOTA28_      '9'  // "" de valor mas grande  (estoy presuponiendo que cada nota tiene valor consecutivo)
#define TOTAL_NOTAS_ 52
#define NOTA_MAX_    28

#define SONG_FILE_NAME_     "cancionGrabada.csv" //agregar el nombre que sea con el path deseado
#define SONG_FOLDER_PATH_   "../media/"
#define SONG_FILE_TYPE_     ".csv"

#define TIME_JUGAR 200
#define PUNTOCSIMPLE 10
#define PUNTOCLARGA 15

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
    void setPuertoMidi(ClaseMIDI* puertoExt);
    void procesarNota( QByteArray );
    uint8_t tramaOk(unsigned char* );
    uint8_t tramaInfo( unsigned char* );
    void LeerArchivo(void);
    void setNotaCorrecta(void);
    void setNotaIncorrecta(void);

private slots:
    void on_datosRecibidos();
    void monitoreoPuntos();
    void timer_handler(void);
    void slotPuntaje();
private:
    Ui::Jugar *ui;
    uint8_t notaTocada;
    int pesoPunto=0;
    int posicion = 0;
    int puntos=0;
    QString timerNota;
    ParserPuntaje puntajes;
    QString nombreCancion;
    QSerialPort *puerto;
    QStringList listaNota;
    void iniciarTimer(int);
    QMetaObject::Connection conection; //almacena el valor retornado por connect() para podes desconectar con disconnect()
    QMetaObject::Connection conection1;
    QMetaObject::Connection conection2;
    //funcion para el line_edit Puntos
    QByteArray bufferSerie;
    ClaseMIDI *puertoMidi;
    QNoteView mostrar;
    void validarDatos();
    void procesarNotaATocar(QByteArray);
    void mostrarNota(char nota);
    int notaACuerdaYNota(uint8_t nota) ;
    int setPuntosMax(void);

};

#endif // JUGAR_H
