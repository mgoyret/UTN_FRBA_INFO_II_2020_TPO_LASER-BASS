#include "inc/tocar.h"
#include "ui_tocar.h"

Tocar::Tocar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tocar)
{
    ui->setupUi(this);
}

Tocar::~Tocar()
{
    delete ui;
}

/*void Tocar :: setPuerto(QString name){
    puerto->portName()=name;
    puerto->setBaudRate(QSerialPort::Baud9600);
    puerto->setDataBits(QSerialPort::Data8);
    puerto->setParity(QSerialPort::NoParity);
    puerto->setStopBits(QSerialPort::OneStop);
    puerto->setFlowControl(QSerialPort::NoFlowControl);
    connect(puerto, SIGNAL(readyRead()), this, SLOT(puertoSerieRcv_handler()));
}
void Tocar::on_datosRecibidos(){

    QByteArray datos;
    int cant = int (puerto->bytesAvailable());
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
/*void Tocar :: setColor(const char* estado){
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

    /* prosesar data recibida y transformarla a un char o uint8_t
     * pros.nota devuelve el numero de nota 1-28 o 29-56*/
    procesarNota(datos);
    setNotaCorrecta();
}

void Tocar::procesarNota( QByteArray datos ) //chequear que hacer con res
{
    uint8_t nota; // nota == ultimos 4 bits de byte 1 y primeros 4 bits de byte 2
    if( tramaOk(datos) )
    {
        #ifdef DEBUG
        qDebug()<<"Trama correcta";
        #endif
        nota = tramaInfo(datos); //relleno "nota" con lo alcarado arriba en su declaracion (ver comentario)

        /*  notaTocada podra tomar valores del 0 al 52. Entre 1 y 28 corresponde a los note on
            y entre el 29 y 56 corresponde a los noteoff */
        if( (nota<1) || (nota>NOTA_MAX/**2*/) )
            //es porque hubo error
            notaTocada = SIN_NOTA;

        else
            notaTocada = nota;

    }
    #ifdef DEBUG
    else
        qDebug()<<"trama incorrecta";
    #endif
    /*
    //Esto es temporal para experimentar
    srand(time(nullptr));
    res = rand() % 53; //random entre 0 y 53
    notaTocada = res;
*/
    return ;
}

/**
*	\fn         void tramaOk(QByteArray datos)
*	\brief      Verifica que lo recibido por puerto serie sea una nota enviada por el microprosesador
*	\details    Verifica especificamente los primeros y ultimos 4 bits de lo recibido por puerto serie
*	\author     Marcos Goyret
*/
uint8_t Tocar::tramaOk(QByteArray datos)
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
uint8_t Tocar::tramaInfo(QByteArray datos)
{
    uint8_t res=0;

    res = ( (((uint8_t)datos[0])&ULTIMA_MITAD)<<4 ) + ( (((uint8_t)datos[1])&PRIMER_MITAD)>>4 );

    #ifdef DEBUG
    qDebug()<< "info: " << res << " = " << (BIT1_MITAD2<<4) << " + " << BIT2_MITAD1;
    #endif

    return res;
}

void Tocar::setNotaCorrecta(void)
{
    if(notaTocada >= 1 && notaTocada <= 28){
        //prendo la nota

        QGuitarView aux;

        if(aux.setNotaPrendida(notaTocada)){

            aux.setColorNotaPrendida(QColor::fromRgb(0,255,0));
            //aux.setColorCuerdaPrendida(QColor::fromRgb(0,255,0));
        }
    }

    if(notaTocada >= 29 && notaTocada <= 56){
        //apago la nota

        QGuitarView aux;

        if(aux.setNotaApagada(notaTocada)){

            aux.setColorNotaApagada(QColor::fromRgb(255));
            //aux.setColorCuerdaApagada(QColor c);
        }
    }
}

