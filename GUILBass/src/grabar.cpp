#include "inc/grabar.h"
#include "ui_grabar.h"
#include <QMessageBox>
#include <stdio.h>

#include <QTimer>
#include <QDebug>

Grabar::Grabar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabar)
{
    ui->setupUi(this);
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(timer_250ms_handler));

}

Grabar::~Grabar()
{
    delete ui;
}


/////////////////////////     PUBLIC     //////////////////////////////////////////////////////

/**
*	\fn void setPuerto( QString )
*	\brief Setea puerto serie
*	\details Detalles
*	\author Tomada de Alejo Fernandez Bados
*	\date 2020
*/
void Grabar::setPuerto(QString name){
    puerto.portName() = name;
    puerto.setBaudRate(QSerialPort::Baud9600);
    puerto.setDataBits(QSerialPort::Data8);
    puerto.setParity(QSerialPort::NoParity);
    puerto.setStopBits(QSerialPort::OneStop);
    puerto.setFlowControl(QSerialPort::NoFlowControl);
    connect(&puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
}


/**
*	\fn void inicializarMdE(void)
*	\brief Inicializa variables que haya que inicializar
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void Grabar::inicializar(void)
{
    recBuf.note_st = nullptr;
    recBuf.total_cntr = 0;
}

/**
*	\fn void iniciarTimer_250ms(void)
*	\brief inicializa un timer de 250ms
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void Grabar::iniciarTimer_250ms()
{
    /* armar funcion y configurarla con su itmerHandler */
    //timer->start(1000);
    QTimer::singleShot(500, this, SLOT(timer_250ms_handler()));
    qDebug() << "inicie timer";
}


/**
*	\fn void timer_250ms_handler(void)
*	\brief handler del timer inicializado de 250ms
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void Grabar::timer_250ms_handler( void )
{
    /* Seteo variable a SIN_NOTA asi cuando se presione detener y la variable grabacion
        se modifique, esta ultima vuelta no hace nada y no se vuelve a reiniciar el timer */
    uint32_t notaTocada = SIN_NOTA;
    qDebug() << "timer expiro";
    if(grabacion == ON)
    {
        //notaRecibida devuelve la nota que haya encolada en el puerto serie, o SIN_NOTA (0) si no hay nota
        notaTocada = notaRecibida();
        /* aca tendria que limpiar la cola por si toco mas de 1 nota en 250ms, solo quedarme con la primera
            limpiarCola(); o podria hacerlo dentro de la fnc notaRecibida() */
        guardarNota(notaTocada);
        //iniciarTimer_250ms();
        QTimer::singleShot(500, this, SLOT(timer_250ms_handler()));
    }
}


/**
*	\fn int notaRecibida(void)
*	\brief Devuelve false si no hay ninguna nota tocada, y en caso contrario devuelve la nota
*	\details Si hay algo para leer del puerto, va a ser la nota tocada, la asigno a res
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
uint32_t Grabar::notaRecibida( void )
{
    uint32_t res = SIN_NOTA;
    QByteArray datos;
    uint8_t cant = (int)puerto.bytesAvailable();

    qDebug() << "Datos: " << cant;
    datos.resize(cant);
    puerto.read(datos.data(), cant);
    /* No se si esta sentencia esta bien...Quisiera obtener el contenido del QByteArray pero
        el un uint8_t que guarde el numero propio de la info contenida. Si es '00100111' que guarde ese numero */
    res = datos.toUInt();

    if( !(res >= NOTA1) || !(res <= NOTA28) )
        res = SIN_NOTA;

    return res;
}

/**
*	\fn void guardarNota(void)
*	\brief guarda la nota tocada en el archivo
*	\details Detalles
*	\author marcosgoyret
*	\date 15-09-2020 17:00:19
*/
void Grabar::guardarNota( uint32_t notaTocada )
{
    uint32_t i=0;
    noteBuffer *aux = new noteBuffer[recBuf.total_cntr + 1];
    for(i=0; i<recBuf.total_cntr; i++)
    {
        aux[i].note = recBuf.note_st[i].note;
        aux[i].cntr = i;
    }
    aux[i].note = notaTocada;
    aux[i].cntr = i;

    delete [] recBuf.note_st;
    recBuf.note_st = aux;
}


uint8_t Grabar::guardarCancion( void )
{
    uint8_t i;
    songFile.setFileName(SONG_FILE_NAME);
    if(songFile.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream out(&songFile);
        for(i=0; i<recBuf.total_cntr; i++)
        {
            out << recBuf.note_st->cntr << "," << recBuf.note_st->note << "\n";
        }
    }
    return (uint8_t)1;
}

/////////////////////////     PRIVATE SLOTS    //////////////////////////////////////////////////////

//boton iniciar grabacion
void Grabar::on_PBrec_clicked()
{
    ui->PBrec->setEnabled(false);
    ui->PBfinRec->setEnabled(true);

    grabacion = ON;
    inicializar(); // solo hace contador=0  pero quedaba mas prolijo poner la funcion de inic.
    iniciarTimer_250ms();
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
        guardarCancion();
    }else if ( (opcion == QMessageBox::StandardButton::No) || (opcion == QMessageBox::StandardButton::Escape) )
    {
        //se descarta la grabacion
        QMessageBox::information(this, "Atencion", "Grabacion descartada");
    }else
        QMessageBox::critical(this, "ERROR", "Ocurrio un error inesperado [on_PBfinRed_clicked()]");

    ui->PBrec->setEnabled(true);
}

