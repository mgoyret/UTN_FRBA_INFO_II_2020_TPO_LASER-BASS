#include "inc/tocar.h"
#include "ui_tocar.h"

Tocar::Tocar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tocar)
{
    ui->setupUi(this);
    bufferSerie.clear();
    qDebug() << puertoMidi.abrirPuerto(1);
    qDebug() << puertoMidi.getNombreSalida(1) << "\n" << puertoMidi.getNombresSalidas();
    qDebug() << puertoMidi.inicializarGS();
    qDebug() << puertoMidi.enviarNoteOn(0, 64, 127);
    ui->graphicsView->setColorNotaApagada(Qt::black);
}

Tocar::~Tocar()
{
    delete ui;
}

/*
void Tocar::on_datosRecibidos(){
    QByteArray datos;
    int cant = int (puerto.bytesAvailable());
    datos.resize(cant);
    puerto->read(datos.data(), cant);
    //Procesar Dato y poner MIDI
    //Funcion que procese el dato y devuelva un string con la nota
    //transforma el dato o la nota en el array para setColor
    //29 xq son 28 lugares que hay que cpnfigurar + 1 por el retun 0
    char status[29]="0011010101010111111111111110";
    //    setColor(status);

}
*/

/*
 * void Tocar :: setColor(const char* estado){
    QColor red(255,0,0);
    QColor white(255,255,255);
    QColor green(0,255,0);
    if(estado[0]==ON){
        ui->Cuerda1->setPalette(red);
    }else{
        ui->Cuerda1->setPalette(white);
    }
    if(estado[7]==ON){
        ui->Punto6A->setPalette(green);
    }else{
        ui->Punto6A->setPalette(white);
    }
    if(estado[8]==ON){
        ui->Cuerda2->setPalette(green);
    }else{
        ui->Cuerda2->setPalette(white);
    }
    //y asi con el resto a mi se me ocurrio hacer esto para no tener 58 if
    //y de esta forma tmb queda separado lo otro que se me ocurrio sino
    //es q en vez del array uno le entrege un numero de noto y despues en esta funcion
    //pase esa nota al array ,seria otra opcion

}
*/


void Tocar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this, SLOT(puertoSerieRcv_handler()));
}


void Tocar::puertoSerieRcv_handler( void )
{
    uint8_t cant = 0;
    QByteArray datos;

    #ifdef DEBUG
    qDebug() << "Datos recibidos ";
    #endif
    cant = (int)puerto->bytesAvailable();


    datos.resize(cant);
    puerto->read(datos.data(), cant);

    //prosesar data recibida y transformarla a un char o uint8_t
    //pros.nota devuelve el numero de nota 1-28 o 29-56
    procesarNota(datos);
    setNotaCorrecta();
}


void Tocar::procesarNota( QByteArray data )
{
    uint8_t nota; // nota == ultimos 4 bits de byte 1 y primeros 4 bits de byte 2

    if( tramaOk(data) )
    {
        #ifdef DEBUG
        qDebug()<<"Trama correcta";
        #endif
        nota = tramaInfo(data); //relleno "nota" con lo alcarado arriba en su declaracion (ver comentario)

        //  notaTocada podra tomar valores del 0 al 56. Entre 1 y 28 corresponde a los note on
        //  y entre el 29 y 56 corresponde a los noteoff
        if( (nota<1) || (nota>NOTA_MAX*2) ) //es porque hubo error, ya que no puede llegar nada <1 o >56
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

uint8_t Tocar::tramaOk( QByteArray data)
{
    uint8_t res = ERROR;

    if( INICIO_TRAMA_OK_ && FIN_TRAMA_OK_ )
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

uint8_t Tocar::tramaInfo( QByteArray data)
{
    uint8_t res=0;

    res = ( (((uint8_t)data[0])&ULTIMA_MITAD_)<<4 ) + ( (((uint8_t)data[1])&PRIMER_MITAD_)>>4 );

    #ifdef DEBUG
    qDebug()<< "info: " << res << " = " << (BIT1_MITAD2_<<4) << " + " << BIT2_MITAD1_;
    #endif

    return res;
}


void Tocar::mostrarNota(char nota) {
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

int Tocar::notaACuerdaYNota(uint8_t nota) {
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

void Tocar::on_datosRecibidos() {
    bufferSerie.append(puerto->readAll());
    validarDatos();
}

void Tocar::validarDatos() {
    int cant = bufferSerie.size();
    QByteArray datoAProcesar;
    datoAProcesar.clear();
    while (cant > 1) {
        if (bufferSerie.at(0) & 0xa0) {
        if (!(bufferSerie[0] & 0x50)) {
            if (cant == 1) break;
            datoAProcesar.append(bufferSerie.at(0));
            datoAProcesar.append(bufferSerie.at(1));
            bufferSerie.remove(0, 2);
            procesarNota(datoAProcesar);
        } else if (bufferSerie.at(0) & 0x05) {
            bufferSerie.remove(0,1);
        } else {
            bufferSerie.remove(0,1);
        }
        cant = bufferSerie.size();
    }
  }
}

void Tocar::procesarNotaATocar(QByteArray dato) {
    char nota = 0;
    if (dato.size() != 2) qDebug() << "array de datos con mas de 2 bytes";
    nota |= (uint8_t)(dato.at(0) << 4) & 0xf0;
    nota |= (uint8_t)(dato.at(1) >> 4) & 0x0f;
    qDebug() << (uint8_t)nota;
    mostrarNota(nota);
    if (nota < 0) {
        qDebug() << puertoMidi.enviarNoteOff(0, 32 + (uint8_t)std::abs(nota) * 2);
    } else {
        qDebug() << puertoMidi.enviarNoteOn(0, 32 + (uint8_t)std::abs(nota) * 2, 127);
    }
}
