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

#define ON      1
#define OFF     0

#define TIMER1  1

#define SIN_NOTA    0
#define NOTA1       '1'   //aca va el numero que represente a lo que llega por puerto serie al llegar la nota de valor mas chico
#define NOTA28      '9'  // "" de valor mas grande  (estoy presuponiendo que cada nota tiene valor consecutivo)

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

    void setPuerto(QString name);

    void guardarNota( uint32_t );
    uint32_t notaRecibida( void );


    //Prototipos de Inicializacion
    void inicializar(void);

    //Prototipos de Timers
    void iniciarTimer_250ms();
    //void timer_250ms_handler();

    uint8_t guardarCancion();

private slots:
    void on_PBrec_clicked();

    void on_PBfinRec_clicked();

    void timer_250ms_handler();


private:
    Ui::Grabar *ui;
    int grabacion;          //flag para saber cuando cortar loop de timers en cuyos handlers se realiza el proceso de grabado
    QFile songFile;
    songBuffer recBuf;
    QSerialPort puerto;
    //QTimer *timer;
};

#endif // GRABAR_H
