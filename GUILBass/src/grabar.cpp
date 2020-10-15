#include "inc/grabar.h"
#include "ui_grabar.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <QMessageBox>
#include <QTimer>
#include <QDebug>

#define DEBUG

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


/////////////////////////     PUBLIC     //////////////////////////////////////////////////////

/**
*	\fn         void setPuerto( QString )
*	\brief      Setea puerto serie
*	\details    Configura y abre un puerto especificado
*	\author     Marcos Goyret
*/
void Grabar::setPuerto(QString name){
    puerto.setPortName(name);
    puerto.setBaudRate(QSerialPort::Baud9600);
    puerto.setDataBits(QSerialPort::Data8);
    puerto.setParity(QSerialPort::NoParity);
    puerto.setStopBits(QSerialPort::OneStop);
    puerto.setFlowControl(QSerialPort::NoFlowControl);

    /* El puerto lo abrieron en mw asiq lo cierro para conectarme yo */
    if(puerto.isOpen())
        puerto.close();

    if (puerto.open(QIODevice::ReadWrite) == true) //deberia ser ReadOnly...
    {
        #ifdef DEBUG
        qDebug()<< "Grabar::setPuerto(): puerto conectado ["+puerto.portName()+"]";
        #endif

        connect(&puerto, SIGNAL(readyRead()), this, SLOT(puertoSerieRcv_handler()));
    }else{
        QMessageBox::critical(this, "Error", "No se puedo abrir el puerto");
    }
}


/**
*	\fn void inicializarMdE(void)
*	\brief Inicializa variables que haya que inicializar
*	\details Detalles
*	\author Marcos Goyret
*/
void Grabar::inicializar(void)
{
    recBuf.note_st = nullptr;
    recBuf.total_cntr = 0;
    notaTocada = SIN_NOTA;
}

/**
*	\fn         void iniciarTimer_250ms(void)
*	\brief      inicializa un timer de 250ms
*	\details    Inicia un timer que ejecuta el timer handler al terminar
*	\author     Marcos Goyret
*/
void Grabar::iniciarTimer_250ms()
{
    QTimer::singleShot(500, this, SLOT(timer_250ms_handler()));
}


/**
*	\fn         void timer_250ms_handler(void)
*	\brief      handler del timer inicializado de 250ms
*	\details    ejecuta la funcion guardar nota, y restaura el valor de la nota a sin nota
*	\author     Marcos Goyret
*/
void Grabar::timer_250ms_handler( void )
{
    if(grabacion == ON)
    {
        /* aca tendria que limpiar la cola por si toco mas de 1 nota en 250ms, solo quedarme con la primera
            limpiarCola(); o podria hacerlo dentro de la fnc notaRecibida() */
        guardarNota();
        notaTocada = SIN_NOTA;
        iniciarTimer_250ms();
    }
}

/**
*	\fn         void guardarNota(void)
*	\brief      guarda la nota tocada en el archivo
*	\details    Guarda la nota actual almacenada en el array secuencial de estructuras notas y tiempos
*	\author     Marcos Goyret
*/
void Grabar::guardarNota( void )
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

    #ifdef DEBUG
    qDebug()<<"guardando: aux[" << i << "].note = [" << aux[i].note<<"]";
    #endif

    delete[] recBuf.note_st;
    recBuf.note_st = aux;
    recBuf.total_cntr++;
}

uint8_t Grabar::guardarCancion( void )
{
    uint8_t i, res = ERROR;
    #ifdef DEBUG
    qDebug()<<"total notas: " << recBuf.total_cntr;
    for(i=0; i<recBuf.total_cntr; i++)
    {
        qDebug()<<"recBuf.note_st[" << recBuf.note_st[i].cntr << "].note = [" << recBuf.note_st[i].note<<"]";
    }
    #endif

    songFile.setFileName(SONG_FILE_NAME);
    if(songFile.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream out(&songFile);
        for(i=0; i<recBuf.total_cntr; i++)
        {
            out << recBuf.note_st[i].cntr << "," << recBuf.note_st[i].note << "\n";
        }
        songFile.close();
        res = EXITO;
    }
    return (uint8_t)1;
}


uint8_t Grabar::prosesarNota( QByteArray datos)
{
    uint8_t res = SIN_NOTA;

    //Deberia prosesar la nota almacenada y transformarla a un numero entre 1-28, pero para probar hago esto
    srand(time(nullptr));
    res = (rand() % 28) + 1; //random entre 1 y 28

    return res;
}

void Grabar::desconectarPuerto()
{
    puerto.close();
}

/////////////////////////     PRIVATE SLOTS    //////////////////////////////////////////////////////

//boton iniciar grabacion
void Grabar::on_PBrec_clicked()
{
    ui->PBrec->setEnabled(false);
    ui->PBfinRec->setEnabled(true);

    grabacion = ON;
    inicializar();
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
        if(guardarCancion())
            QMessageBox::information(this, "Bien hecho", "Cancion guarada exitosamente");
    }else if ( (opcion == QMessageBox::StandardButton::No) || (opcion == QMessageBox::StandardButton::Escape) )
    {
        //se descarta la grabacion
        QMessageBox::information(this, "Atencion", "Grabacion descartada");
    }else
        QMessageBox::critical(this, "ERROR", "Ocurrio un error inesperado [on_PBfinRed_clicked()]");

    ui->PBrec->setEnabled(true);
}

/**
*	\fn         void puertoSerieRcv_handler()
*	\brief      Slot de la interrupcion cada vez que se emite la senal ReadyRead()
*	\details    Guarda la informacion disponible en el puerto en una variable, y llama a setColor()
*	\author     Marcos Goyret
*/
void Grabar::puertoSerieRcv_handler()
{
    #ifdef DEBUG
    qDebug() << "Datos recibidos ";
    #endif
    QByteArray datos;
    uint8_t cant = (int)puerto.bytesAvailable();
    datos.resize(cant);
    puerto.read(datos.data(), cant);
    /* prosesar data recibida y transformarla a un char o uint8_t
     * pros.nota devuelve el numero de nota 1-28 */
    notaTocada = prosesarNota(datos);
    //setColor(notaTocada);
}
