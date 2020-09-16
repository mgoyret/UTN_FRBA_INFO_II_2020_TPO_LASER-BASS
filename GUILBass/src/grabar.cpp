#include "inc/grabar.h"
#include "ui_grabar.h"
#include <QMessageBox>

#include <stdio.h>

static int contador;    //ubica linealmente las notas en el orden que se tocan
int grabacion;          //flag para saber cuando cortar loop de timers en cuyos handlers se realiza el proceso de grabado
QFile songFile;

Grabar::Grabar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabar)
{
    ui->setupUi(this);
}

Grabar::~Grabar()
{
    delete ui;
}

//boton iniciar grabacion
void Grabar::on_PBrec_clicked()
{
    ui->PBrec->setEnabled(false);
    ui->PBfinRec->setEnabled(true);


    grabacion = ON;

    songFile.setFileName(SONG_FILE_NAME);
    if(songFile.open(QFile::WriteOnly |QFile::Truncate))
    {
        inicializar(); // solo hace contador=0  pero quedaba mas prolijo poner la funcion de inic.
        iniciarTimer_250ms();
        songFile.close();
    }
}




//boton finalizar grabacion
void Grabar::on_PBfinRec_clicked()
{
    QMessageBox::StandardButton opcion;
    ui->PBfinRec->setEnabled(false);
    grabacion = OFF;

    //Pregunto si descartar grabacion o guardar
    opcion = QMessageBox::question(this, "Fin de la grabacion", "guardar?");

    if( opcion == QMessageBox::StandardButton::Yes )
    {
        //se guarda la grabacion. El mensaje "guardada exitosamente" lo agregaria luego de haber implementado el guardado
        songFile.close();
    }else if ( (opcion == QMessageBox::StandardButton::No) || (opcion == QMessageBox::StandardButton::Escape) )
    {
        //se descarta la grabacion
        songFile.close();
        songFile.remove();
        QMessageBox::information(this, "Atencion", "Grabacion descartada");
    }else
        QMessageBox::critical(this, "ERROR", "Ocurrio un error inesperado [on_PBfinRed_clicked()]");

    ui->PBrec->setEnabled(true);
}



///////////////////////////////////////////////////////////////////////////////


/**
*	\fn void inicializarMdE(void)
*	\brief Inicializa variables que haya que inicializar
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void inicializar(void)
{
    contador = 0;
}


/**
*	\fn void iniciarTimer_250ms(void)
*	\brief inicializa un timer de 250ms
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void iniciarTimer_250ms()
{
    /* armar funcion y configurarla con su itmerHandler */
}

/**
*	\fn void timer_250ms_handler(void)
*	\brief handler del timer inicializado de 250ms
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void timer_250ms_handler()
{
    int notaTocada = SIN_NOTA;
    /* Asi cuando se presione detener y la variable grabacion
        se modifique, esta ultima vuelta no hace nada y no se vuelve a reiniciar el timer */
    if(grabacion == ON)
    {
        //notaRecibida devuelve la nota que haya encolada en el puerto serie, o SIN_NOTA (0) si no hay nota
        notaTocada = notaRecibida();
        /* aca tendria que limpiar la cola por si toco mas de 1 nota en 250ms, solo quedarme con la primera
            limpiarCola(); o podria hacerlo dentro de la fnc notaRecibida() */
        guardarNota(notaTocada);

        iniciarTimer_250ms();
    }
}

/**
*	\fn int notaRecibida(void)
*	\brief Devuelve false si no hay ninguna nota tocada, y en caso contrario devuelve la nota
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
int notaRecibida( void )
{
    int res = FALSE;

    //!< Codigo propio de la funcion
    /* Si hay algo para leer del puerto, va a ser la nota tocada,
        la asigno a res */

    return res;
}


/**
*	\fn void guardarNota(void)
*	\brief guarda la nota tocada en el archivo
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void guardarNota( int notaTocada )
{
    if(songFile.open(QFile::WriteOnly |QFile::Append))
    {
        QTextStream out(&songFile);
        out << contador << "," << notaTocada << "\n";

        contador++;
        songFile.close();
    }
}
