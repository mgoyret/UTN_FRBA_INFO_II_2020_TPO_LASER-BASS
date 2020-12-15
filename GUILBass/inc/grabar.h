#ifndef GRABAR_H
#define GRABAR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QSerialPort>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QDir>
#include <clasemidi.h>

//#define DEBUG

#define	TRUE    1
#define	FALSE   0

#define ON      1
#define OFF     0

#define SIN_NOTA    (char)0

#define SONG_FILE_NAME "cancionGrabada.csv" //agregar el nombre que sea con el path deseado

#define TIMER_TIME 50

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* Estructura que almacena una nota. Esta compuesta por la posicion cronologica de la nota (ctr) y la nota
    en si, que va desde 0 a 28 para los noteOnn y desde 29 a 52 para los noteOff */
typedef struct noteBuffer{
    uint64_t cntr;
    char note;
}noteBuffer;


/* Estructura que almacena una cancion. Esta compuesta por la suma total de posiciones de la cancion
    y un array de notas del tipo "noteBuffer".  La estructura noteBuffer la declaro arriba para que
    al hacer esta estructura detecte el tipo de dato, sino no funca. */
typedef struct songBuffer{
    uint64_t total_cntr;
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

    void setPuerto( QSerialPort* );
    void setPuertoMidi(ClaseMIDI* puertoExt){puertoMidi=puertoExt;}
    void inicializar( void );
    void iniciarTimer( void );
    void guardarNota( void );
    bool guardarCancion( void );
    bool checkName( void );
    void validarDatos(void);
    void procesarNotaATocar(QByteArray dato);
    void mostrarNota(char nota);
    int notaACuerdaYNota(uint8_t nota);


private slots:
    void on_PBrec_clicked( void );
    void on_PBfinRec_clicked( void );
    void timer_handler( void );
    void on_datosRecibidos( void );
    void on_PBnombre_clicked();
    void on_lineEditNombre_textChanged(const QString &arg1);

private:
    Ui::Grabar  *ui;
    uint8_t     grabacion; //flag para saber cuando cortar loop de timers en cuyos handlers se realiza el proceso de grabado
    uint8_t     status;
    QByteArray  notaTocada;
    QFile       songFile;
    QString     songName, auxName;
    songBuffer  recBuf;
    QSerialPort *puerto;
    ClaseMIDI   *puertoMidi;
    QMetaObject::Connection conection; //almacena el valor retornado por connect() para podes desconectar con disconnect()
    QByteArray  bufferSerie; //para lo de felipe
};

#endif // GRABAR_H
