#ifndef GRABAR_H
#define GRABAR_H

#include <stdio.h>
#include <QDialog>
#include <QFile>
#include <QTextStream>


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

    void guardarNota( uint8_t );
    uint8_t notaRecibida( void );


    //Prototipos de Inicializacion
    void inicializar(void);

    //Prototipos de Timers
    void iniciarTimer_250ms();
    void timer_250ms_handler();

    uint8_t guardarCancion();

private slots:
    void on_PBrec_clicked();

    void on_PBfinRec_clicked();

private:
    Ui::Grabar *ui;
    int grabacion;          //flag para saber cuando cortar loop de timers en cuyos handlers se realiza el proceso de grabado
    QFile songFile;
    songBuffer recBuf;

};

#endif // GRABAR_H
