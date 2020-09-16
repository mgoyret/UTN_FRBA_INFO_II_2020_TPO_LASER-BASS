#ifndef GRABAR_H
#define GRABAR_H

#include <QDialog>
#include <stdio.h>
#include <QFile>
#include <QTextStream>


namespace Ui {
class Grabar;
}

class Grabar : public QDialog
{
    Q_OBJECT

public:
    explicit Grabar(QWidget *parent = nullptr);
    ~Grabar();

private slots:
    void on_PBrec_clicked();

    void on_PBfinRec_clicked();

private:
    Ui::Grabar *ui;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define	TRUE    1
#define	FALSE   0

#define ON      1
#define OFF     0

#define SIN_NOTA    0
#define SONG_FILE_NAME "cancionGrabada.csv" //agregar el nombre que sea con el path deseado


///////////////////// FUNCIONES

int notaRecibida( void );
void guardarNota( int );


//Prototipos de Inicializacion
void inicializar(void);

//Prototipos de Timers
void iniciarTimer_250ms();
void timer_250ms_handler();




#endif // GRABAR_H
