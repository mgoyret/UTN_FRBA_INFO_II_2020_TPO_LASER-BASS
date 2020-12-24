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

#define SONG_FILE_NAME      "cancionGrabada.csv" //agregar el nombre que sea con el path deseado
#define SONG_FOLDER_PATH    "../media/"
#define SONG_FILE_TYPE      ".csv"

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
    int puntos=0;
    QString timerNota;
    ParserPuntaje puntajes;
    QString nombreCancion;
    QSerialPort *puerto;
    //lista donde se pone los datos del archivo
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
