#include "jugar.h"
#include "ui_jugar.h"

Jugar::Jugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Jugar)
{
    ui->setupUi(this);
}

Jugar::~Jugar()
{
    delete ui;
}

void Jugar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this, SLOT(puertoSerieRcv_handler()));
}

void Jugar::puertoSerieRcv_handler( void )
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
    LeerArchivo();
}

void Jugar::procesarNota( QByteArray datos )
{
    uint8_t nota; // nota == ultimos 4 bits de byte 1 y primeros 4 bits de byte 2

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

        /*  notaTocada podra tomar valores del 0 al 56. Entre 1 y 28 corresponde a los note on
            y entre el 29 y 56 corresponde a los noteoff */
        if( (nota<1) || (nota>NOTA_MAX*2) ) //es porque hubo error, ya que no puede llegar nada <1 o >56
        {
            notaTocada = SIN_NOTA;
        }
        else
        {
            notaTocada = nota;
            posicion++;
        }
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
uint8_t Jugar::tramaOk(unsigned char* data)
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
uint8_t Jugar::tramaInfo(unsigned char* data)
{
    uint8_t res=0;

    res = ( (((uint8_t)data[0])&ULTIMA_MITAD)<<4 ) + ( (((uint8_t)data[1])&PRIMER_MITAD)>>4 );

    #ifdef DEBUG
    qDebug()<< "info: " << res << " = " << (BIT1_MITAD2<<4) << " + " << BIT2_MITAD1;
    #endif

    return res;
}

void Jugar::setNotaCorrecta(void)
{
    if(notaTocada >= 1 && notaTocada <= 28){
        //prendo la nota en verde

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

void Jugar::setNotaIncorrecta(void)
{
    if(notaTocada >= 1 && notaTocada <= 28){
        //prendo la nota en rojo

        QGuitarView aux;

        if(aux.setNotaPrendida(notaTocada)){

            aux.setColorNotaPrendida(QColor::fromRgb(255,0,0));
            //aux.setColorCuerdaPrendida(QColor::fromRgb(255,0,0));
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

void Jugar::LeerArchivo(void){
    QString line;
    QStringList list;
    int i = 0;

    QFile cancion(SONG_FILE_NAME);


    if(!cancion.open(QIODevice::ReadOnly)){

    QTextStream in(&cancion);

    while (i < posicion && !in.atEnd()) //La funcion !in.atEnd() no me funcionaba bien, asi que quizas haya que reemplazarla por otra
    {
        line = in.readLine(); //posicion,nota
        list = line.split(QLatin1Char(',')); //guarda lo separado por las comas en posiciones distintas de un array

        i++;
    }
    //En el paso anterior se va a leer el archivo linea por lina hasta llegar a la que corresponde a la posicion de la nota recibida,
    //por lo que una vez que se sale del while, list[1] va a tener los datos en esa posicion

    //Comparo list[1] (nota) con el dato recibido
    if(list[1].toInt() == (int) notaTocada){
        setNotaCorrecta(); //la nota se prende en color verde
        //Sumo puntaje
        //ui->Puntos->setText(Puntaje);
    }else{
        setNotaIncorrecta(); //la nota se prende en color rojo
        //Resto puntaje
        //ui->Puntos->setText(Puntaje);
    }
    cancion.close();
    }
   /* Ejemplo uso QStringList
      QStringList str = {"Hola", "todo", "bien"};
      ui->textEdit->setText(str[2]);
    */
}
