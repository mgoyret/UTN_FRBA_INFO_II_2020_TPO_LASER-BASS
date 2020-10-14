#ifndef GRABAR_H
#define GRABAR_H

#include <stdio.h>
#include <QDialog>
#include <QFile>
#include <QTextStream>

#include "bibliotecaInfo2/bibliotecaInfoII.h"


#define	TRUE    1
#define	FALSE   0

#define ON      1
#define OFF     0

#define TIMER1  1

#define SIN_NOTA    0
#define SONG_FILE_NAME "cancionGrabada.csv" //agregar el nombre que sea con el path deseado



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
    explicit Grabar(QWidget *parent = nullptr);
    ~Grabar();

    static void guardarNota( uint8_t );
    static uint8_t notaRecibida( void );


    //Prototipos de Inicializacion
    static void inicializar(void);

    //Prototipos de Timers
    static void iniciarTimer_250ms();
    static void timer_250ms_handler();

    static uint8_t guardarCancion();

private slots:
    void on_PBrec_clicked();

    void on_PBfinRec_clicked();

private:
    Ui::Grabar *ui;
    static int grabacion;          //flag para saber cuando cortar loop de timers en cuyos handlers se realiza el proceso de grabado
    static QFile songFile;
    static songBuffer recBuf;

};

#endif // GRABAR_H
