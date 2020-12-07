#include "inc/grabar.h"
#include "ui_grabar.h"


Grabar::Grabar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabar)
{
    ui->setupUi(this);
}

Grabar::~Grabar()
{
    /* Desconecta el vinculo signal slot del puerto serie que cree en set_puerto()   */
    disconnect(conection);
    puerto->disconnect();
    if(puerto->isOpen())
        puerto->close();
    delete ui;
}


/////////////////////////     PUBLIC     //////////////////////////////////////////////////////

/**
*	\fn         void set_puerto( QSerialPort *puertoExt )
*	\brief      Apunta mi puntero de QSerialPort, a la direccion del puerto que tenemos conectado, y conecta el slot
*	\details    La conecion del slot, sera desconectada en el destructor, para dejar la senal readyRead() libre para otras ventanas
*	\author     Marcos Goyret
*/
void Grabar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this, SLOT(puertoSerieRcv_handler()));
}

/**
*	\fn void inicializarMdE( void )
*	\brief Inicializa variables que haya que inicializar
*	\details Detalles
*	\author Marcos Goyret
*/
void Grabar::inicializar( void )
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
void Grabar::iniciarTimer()
{
    QTimer::singleShot(TIMER_TIME, this, SLOT(timer_handler()));
}


/**
*	\fn         void timer_250ms_handler(void)
*	\brief      handler del timer inicializado de 250ms
*	\details    ejecuta la funcion guardar nota, y restaura el valor de la nota a sin nota
*	\author     Marcos Goyret
*/
void Grabar::timer_handler( void )
{
    monitoreo(); // Ver documentacion de la funcion
    if(grabacion == ON)
    {
        /* aca tendria que limpiar la cola por si toco mas de 1 nota en 250ms, solo quedarme con la primera
            limpiarCola(); o podria hacerlo dentro de la fnc notaRecibida() */
        guardarNota();
        notaTocada = SIN_NOTA;
        iniciarTimer();
    }
}

/**
*	\fn         void monitoreo(void)
*	\brief      Envia senales midi y colores al qGuitarView
*	\details    Para que el usuario al estar grabando tambien escuche y vea lo que esta tocando
*	\author     Marcos Goyret
*/
void Grabar::monitoreo()
{
    //enviar midi signal
    //setColor()
}

/**
*	\fn         void guardarNota(void)
*	\brief      buffer de cancion que se guardara
*	\details    Guarda la nota actual almacenada en el array secuencial de estructuras notas y tiempos
*	\author     Marcos Goyret
*/
void Grabar::guardarNota( void )
{
    uint64_t i=0;
    noteBuffer *aux = new noteBuffer[recBuf.total_cntr + 1]; //creo array con una posicion mas, para almacenar ueva posicion
    for(i=0; i<recBuf.total_cntr; i++)
    {
        aux[i].note = recBuf.note_st[i].note;
        aux[i].cntr = i;
    }
    aux[i].note = notaTocada;
    aux[i].cntr = i;

    #ifdef DEBUG
    if(notaTocada != SIN_NOTA)
        qDebug()<<"guardando: aux[" << i << "].note = [" << aux[i].note<<"]\n";
    #endif

    delete[] recBuf.note_st;
    recBuf.note_st = aux;
    recBuf.total_cntr++;
}

/**
*	\fn         void guardarCancion(void)
*	\brief      Guarda la cancion grabada, en un archivo
*	\details    Imprime la informacion contenida en la estructura del tipo songBuffer, en un archivo
*	\author     Marcos Goyret
*/
uint8_t Grabar::guardarCancion( void )
{
    uint64_t i;
    uint8_t res = ERROR;

    #ifdef DEBUG
    qDebug()<<"total notas: " << recBuf.total_cntr;
    for(i=0; i<recBuf.total_cntr; i++)
    {
        qDebug()<<"recBuf.note_st[" << recBuf.note_st[i].cntr << "].note = [" << recBuf.note_st[i].note<<"]\n";
    }
    #endif

    //Estas tres lineas son porque tengo que poner el nombre con el directorio
    QString nombre;
    nombre.append("../media/");
    nombre.append(songName);
    nombre.append(".csv");

    songFile.setFileName(nombre);
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
    return res;
}


/**
*	\fn         void procesarNota( QByteArray datos )
*	\brief      Transforma informacion del puerto serie en una representacion util
*	\details    La trama que recibo por puerto serie, la decodifico y la represento con una letra o numero, segun la nota que sea
*	\author     Marcos Goyret
*/
void Grabar::procesarNota( QByteArray datos )
{
    char nota; // nota == ultimos 4 bits de byte 1 y primeros 4 bits de byte 2
    unsigned char data[2];

    /////// ESTO NO SE SI VA, ES PORQ RECIBO UNSIGNED PERO QT LEE SIGNED

    data[0] = (datos[0] < (char)0)?(datos[0] + 256):datos[0];
    data[1] = (datos[1] < (char)0)?(datos[1] + 256):datos[1];

    ///////////////////////////////////////////////////////////////
    if( tramaOk(data) )
    {
        #ifdef DEBUG
        qDebug()<<"Trama correcta";
        #endif
        nota = tramaInfo(data); //relleno "nota" con lo alcarado arriba en su declaracion (ver comentario)

        /* notaTocada podra tomar valores del 0 al 56. Entre -28 y 28 */
        if( (nota < -NOTA_MAX) || (nota > NOTA_MAX) ) //es porque hubo error, ya que no puede llegar nada <1 o >56
            notaTocada = SIN_NOTA;
        else
            notaTocada = nota;
    }
    #ifdef DEBUG
    else
        qDebug()<<"trama incorrecta";
    #endif
}

/**
*	\fn         void tramaOk(QByteArray datos)
*	\brief      Verifica que lo recibido por puerto serie sea una nota enviada por el microprosesador
*	\details    Verifica especificamente los primeros y ultimos 4 bits de lo recibido por puerto serie
*	\author     Marcos Goyret
*/
uint8_t Grabar::tramaOk( unsigned char* data)
{
    uint8_t res = ERROR;

    if( INICIO_TRAMA_OK && FIN_TRAMA_OK )
        res = EXITO;

    return res;
}

/**
*	\fn         void tramaInfo(QByteArray datos)
*	\brief      Obtiene la informacion de la nota tocada
*	\details    En el mensaje recibido por puerto serie, la info. de la nota esta en los ultimos 4 bits del primer
*               byte, y en los primeros 4 bits del segundo byte
*	\author     Marcos Goyret
*/
uint8_t Grabar::tramaInfo( unsigned char* data)
{
    uint8_t res=0;

    res = ( (((uint8_t)data[0])&ULTIMA_MITAD)<<4 ) + ( (((uint8_t)data[1])&PRIMER_MITAD)>>4 );

    #ifdef DEBUG
    qDebug()<< "info: " << res << " = " << (BIT1_MITAD2<<4) << " + " << BIT2_MITAD1;
    #endif

    return res;
}

/////////////////////////     PRIVATE SLOTS      //////////////////////////////////////////////////////

//boton iniciar grabacion
void Grabar::on_PBrec_clicked()
{
    ui->PBrec->setEnabled(false);
    ui->PBfinRec->setEnabled(true);

    grabacion = ON;
    inicializar();
    iniciarTimer();
}

//boton finalizar grabacion
void Grabar::on_PBfinRec_clicked()
{
    QMessageBox::StandardButton opcion;
    ui->PBfinRec->setEnabled(false);
    grabacion = OFF;

    //Pregunto si descartar grabacion o guardar
    opcion = QMessageBox::question(this, "Fin de la grabacion", "guardar?");
    //si no se quiere guardar liberar memoria

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

    ui->lineEditNombre->setEnabled(true);
    ui->PBnombre->setEnabled(true);
}

/**
*	\fn         void puertoSerieRcv_handler( void )
*	\brief      Slot de la interrupcion cada vez que se emite la senal ReadyRead()
*	\details    Guarda la informacion disponible en el puerto en una variable, y llama a setColor()
*	\author     Marcos Goyret
*/
void Grabar::puertoSerieRcv_handler()
{
    bufferSerie.append(puerto->readAll());
    validarDatos();
}

void Grabar::validarDatos()
{
    int cant = bufferSerie.size();
    QByteArray datoAProcesar;
    datoAProcesar.clear();
    while (cant > 1) {
        if (bufferSerie[0] & 0xa0) {
            if (cant == 1) break;
            datoAProcesar.append(bufferSerie[0]);
            datoAProcesar.append(bufferSerie[1]);
            bufferSerie.remove(0, 2);
            procesarNotaATocar(datoAProcesar);
            datoAProcesar.clear();
        } else {
            bufferSerie.remove(0, 1);
        }
        cant = bufferSerie.size();
    }
}

void Grabar::procesarNotaATocar(QByteArray dato)
{
    char nota = 0;
    if (dato.size() != 2) qDebug() << "array de datos con mas de 2 bytes";
    nota |= (uint8_t)(dato.at(0) << 4) & 0xf0;
    nota |= (uint8_t)(dato.at(1) >> 4) & 0x0f;
    notaTocada = nota;
    qDebug() << (uint8_t)nota;
    if (nota < 0) {
        qDebug() << puertoMidi.enviarNoteOff(0, 32 + (uint8_t)std::abs(nota) * 2);
    } else {
        qDebug() << puertoMidi.enviarNoteOn(0, 32 + (uint8_t)std::abs(nota) * 2, 127);
    }
}

void Grabar::on_PBnombre_clicked()
{
    if( ui->lineEditNombre->text() != "" )
    {
        if ( checkName() )
        {
            songName = auxName;
            ui->lineEditNombre->setDisabled(true);
            ui->PBnombre->setDisabled(true);
            ui->PBrec->setEnabled(true);
        }else
        {
            QMessageBox::critical(this, "Atencion", "Nombre en uso");
            ui->lineEditNombre->setText("Ingrese Nombre");
        }
    }
}

uint8_t Grabar::checkName( void )
{
    uint8_t res = TRUE;
    QStringList lista = QDir("../media").entryList();
    for(uint8_t i=0; i<lista.size(); i++)
    {
        if( lista.at(i) == auxName )
            res = FALSE;
        qDebug() << lista.at(i);
    }
    return res;
}

void Grabar::on_lineEditNombre_textChanged(const QString &arg1)
{
    auxName = arg1;
}


