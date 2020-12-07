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
        qDebug()<<"holarecBuf.note_st[" << recBuf.note_st[i].cntr << "].note = [" << recBuf.note_st[i].note<<"]\n";
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
            out << recBuf.note_st[i].cntr << "," << (int)(recBuf.note_st[i].note) << "\n";
        }
        songFile.close();
        res = EXITO;
    }
    return res;
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

uint8_t Grabar::checkName( void )
{
    uint8_t res = TRUE;
    QStringList lista = QDir("../media").entryList();
    for(uint8_t i=0; i<lista.size(); i++)
    {
        if( lista.at(i) == auxName )
            res = FALSE;
        //qDebug() << lista.at(i);
    }
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
*	\fn         void timer_250ms_handler(void)
*	\brief      handler del timer inicializado de 250ms
*	\details    ejecuta la funcion guardar nota, y restaura el valor de la nota a sin nota
*	\author     Marcos Goyret
*/
void Grabar::timer_handler( void )
{
    if(grabacion == ON)
    {
        guardarNota();
        notaTocada = SIN_NOTA;
        iniciarTimer();
    }
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


void Grabar::on_lineEditNombre_textChanged(const QString &arg1)
{
    auxName = arg1;
}


