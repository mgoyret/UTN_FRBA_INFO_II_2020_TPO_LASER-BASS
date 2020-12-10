#include "inc/grabar.h"
#include "ui_grabar.h"

/**
*   \fn 		Grabar( QWidget* )
*   \brief 	    Constructor de la clase
*   \details    Inicializa el midi
*/
Grabar::Grabar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabar)
{
    ui->setupUi(this);
}

/**
*   \fn 		~Grabar( QWidget* )
*   \brief 	    Destructor de la clase
*/
Grabar::~Grabar()
{
    disconnect(conection); //Desconecta el vinculo signal slot del puerto serie que cree en set_puerto()
    delete ui;
}

/**
*	\fn         void set_puerto( QSerialPort *puertoExt )
*	\brief      Apunta mi puntero de QSerialPort, a la direccion del puerto que tenemos conectado, y conecta el slot
*	\details    La conecion del slot, sera desconectada en el destructor, para dejar la senal readyRead() libre para otras ventanas
*/
void Grabar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
}

/**
*	\fn void inicializar void )
*	\brief Inicializa la grabacion
*	\details Se inicializa la primera nota en 0, para salvar el caso en el que se toca en la primera posicion
* lo cual dificultaria a la hora de jugar con esa cancion, ya que no habria tiempo de ver la nota que haya que tocar
*/
void Grabar::inicializar( void )
{
    noteBuffer *offset = new noteBuffer;
    offset->cntr=0;
    offset->note=SIN_NOTA;
    recBuf.note_st = offset;
    recBuf.total_cntr = 1;
    notaTocada = SIN_NOTA;
}

/**
*	\fn         void iniciarTimer_250ms(void)
*	\brief      inicializa un timer periodico
*	\details    Inicia un timer que ejecuta timer_handler() al terminar
*/
void Grabar::iniciarTimer()
{
    QTimer::singleShot(TIMER_TIME, this, SLOT(timer_handler()));
}

/**
*	\fn         void guardarNota(void)
*	\brief      buffer de cancion que se guardara
*	\details    Guarda la nota actual almacenada en el array secuencial de estructuras notas y tiempos
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
*	\fn 		uint8_t guardarCancion ( void )
*	\brief 	    Guarda la cancion grabada, en un archivo
*	\details 	Imprime la informacion contenida en la estructura del tipo songBuffer, en un archivo
*	\return 	chequeo de errores
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

/**
*	\fn 		void validarDatos ( void )
*	\brief 	    Chequea los datos recibidos por el puerto serie
*	\details 	Chequea inicio y fin de trama, y envia los dos bytes de la trama a la funcion procesarNotaATocar()
*/
void Grabar::validarDatos() {
    int cant = bufferSerie.size();
    QByteArray datoAProcesar;
    datoAProcesar.clear();
    while (cant > 1) {          //chequeos de inicio y fin de trama
        if ( !(bufferSerie[0] & 0x50)  && !(bufferSerie[1] & 0x0A) ) {
            if (cant == 1) break;
            datoAProcesar.append(bufferSerie.at(0));
            datoAProcesar.append(bufferSerie.at(1));
            bufferSerie.remove(0, 2);
            procesarNotaATocar(datoAProcesar);
        } else if (bufferSerie.at(0) & 0x0a) {
            bufferSerie.remove(0,1);
        } else {
            bufferSerie.remove(0,1);
        }
        cant = bufferSerie.size();
    }
}

/**
*	\fn 		void procesarNotaATocar ( ByteArray dato )
*	\brief 	    Procesa la trama recibida puerto serie
*	\details    obtiene la nota tocada (noteOff o noteOn) y lo envia al puerto midi y a la funcion mostrarNota()
*   \param      dato: QByteArray de dos posiciones, con la trama verificada que se recibio por puerto serie
*/
void Grabar::procesarNotaATocar(QByteArray dato) {
    char nota = 0;
    if (dato.size() != 2) qDebug() << "array de datos con mas de 2 bytes";
    nota |= (uint8_t)(dato.at(0) << 4) & 0xf0;
    nota |= (uint8_t)(dato.at(1) >> 4) & 0x0f;
    notaTocada = nota;
    qDebug() << (uint8_t)nota;
    mostrarNota(nota);
    if (nota < 0) {
        qDebug() << puertoMidi->enviarNoteOff(0, 32 + (uint8_t)std::abs(nota) * 2);
    } else {
        qDebug() << puertoMidi->enviarNoteOn(0, 32 + (uint8_t)std::abs(nota) * 2, 127);
    }
}

void Grabar::mostrarNota(char nota) {
    int cuerdaYNota = notaACuerdaYNota(std::abs(nota));
    if (nota > 0) {
        if ((cuerdaYNota & 0x000000ff) != 0xff) ui->graphicsView->setNotaPrendida(cuerdaYNota & 0x000000ff);
        ui->graphicsView->setCuerdaPrendida(cuerdaYNota >> 8);
    } else {
        if ((cuerdaYNota & 0x000000ff) != 0xff) ui->graphicsView->setNotaApagada(cuerdaYNota & 0x000000ff);
        ui->graphicsView->setCuerdaApagada(cuerdaYNota >> 8);
    }

    qDebug() << "Valor nota de mostrar (Nota/Cuerda): " << (cuerdaYNota & 0x000000ff) << "/" << (cuerdaYNota >> 8);
}

int Grabar::notaACuerdaYNota(uint8_t nota) {
    int ret = 0, cuerda = 0, notaConv = 0;
    nota--;
    notaConv = nota % 7;
    if (notaConv) {
        cuerda = nota / 7;
        notaConv = (6 - notaConv) + (6 * cuerda);
    } else {
        cuerda = nota / 7;
        notaConv = 0xff;
    }
    qDebug() << "Cuerda: " << cuerda << "\nNotaConvertida: " << notaConv;
    ret |= notaConv;
    ret |= cuerda << 8;
    return ret;
}

uint8_t Grabar::checkName( void )
{
    uint8_t res = TRUE;
    QString aux2Name = auxName;
    aux2Name.append(".csv"); // los archivos guardados tienen esta terminacion, asique debo compararla tambien
    QStringList lista = QDir("../media").entryList();
    for(uint8_t i=0; i<lista.size(); i++)
    {
        if( lista.at(i) == aux2Name )
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
*	\brief      handler del timer periodico
*	\details    ejecuta la funcion guardar nota, y restaura el valor de la nota a sin nota
*/
void Grabar::timer_handler( void )
{
    if(grabacion == ON)
    {
        guardarNota();
        notaTocada = SIN_NOTA;
        iniciarTimer(); //timer periodico
    }
}

/**
*	\fn         void on_datosRecibidos( void )
*	\brief      Slot de la interrupcion cada vez que se emite la senal ReadyRead()
*	\details    Guarda la informacion disponible en el puerto en una variable, y llama a setColor()
*/
void Grabar::on_datosRecibidos() {
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


