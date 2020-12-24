#include "jugar.h"
#include "ui_jugar.h"

/* IMPORTANTE : LOS QDEBUG SON IMPRESIONES DE TEXTO USADAS PARA HACER
 * DISTINTAS PRUEBAS DURANTE EL DESARROLLO DEL CODIGO POR ESO ES Q ESTAN COMENTADOS
 * Y LOS DEJAMOS POR SI ES NECESARIO HACER ALGINA PRUEBA DE NUEVO*/


/**
*   \fn 		Jugar(QWidget *parent, QString nombre)
*   \brief 	    Constructor de la clase
*   \details    Inicializa el midi,lee el archivo  y agrega las notas
*   \details    a la instancia de noteview , ademas se hace los 2 conect(estos comentado mas abajo)
* \param      nombre de la cancion
*/
Jugar::Jugar(QWidget *parent, QString nombre) :
    QDialog(parent),
    ui(new Ui::Jugar)
{
    ui->setupUi(this);

    bufferSerie.clear();
    nombreCancion = nombre;
    nombreCancion=nombreCancion.prepend(SONG_FOLDER_PATH).append(SONG_FILE_TYPE);
    //leo el archivo y lo cargo a lista nota
    LeerArchivo();
    ui->graphicsView_2->tam=listaNota.size();
    int i;
    /*for(i=0;i<listaNota.size();i++){
        qDebug()<<"lista["<<i<<"] ="<<listaNota[i].toInt();
    }*/
     /*qDebug()<<"size de lista"<<listaNota.size();*/
    //arranco desde 1 xq la posicion 0 es imposible menos Tom Cruise
    i=1;
    int cuerda,nota,cant=0,duracion=0;


//Agrego las notas a la instancia de noteview
    while(i<listaNota.size()-1){

        cuerda =(listaNota[i].toInt()-1)/7;
        nota=(std::abs(listaNota[i].toInt())-7*cuerda-1);
       // qDebug()<<i<<"cuerda"<<cuerda<<"notaa"<<nota;
        if(listaNota[i].toInt()>0){
             int notaAux=-(listaNota[i+1+cant].toInt());
             int notaCapa=listaNota[i].toInt();
             while(notaCapa!=(notaAux) && (i+cant+1)<listaNota.size()-1){
                cant++;
                notaAux=-(listaNota[i+1+cant].toInt());
             }

            if(!cant){
               duracion=0;
            }else{
                duracion=cant;
                cant=0;
            }
            ui->graphicsView_2->agregarNota(nota,cuerda,i,duracion);
        }
        i++;
      }
      //hago el conect de las signals
      //esta signal te lleva al slot puntaje cuando se termina la cancion q terminaron de pasar todas
      //las posciones de notas , la signal la manda la instacia de note view
      conection1 = connect(ui->graphicsView_2, SIGNAL(puntajeSignal()), this, SLOT(slotPuntaje()));
      //cuando la nota pasa a uno de los estados con los cuales o cambiamos el color del puntajes y/o
      //aumentamos el puntaje, mandamos una senal desde note view para q cambia el colro o sume puntaje
      conection2 = connect(ui->graphicsView_2, SIGNAL(monitoreoSignal()), this, SLOT(monitoreoPuntos()));
      //despues hay q apagarlo
      ui->graphicsView_2->startTiempo();
      //seteo los colores de las cuerdas
      ui->graphicsView->setColorNotaApagada(Qt::black);
      ui->graphicsView->setColorNotaPrendida(Qt::red);
      ui->graphicsView->setColorCuerdaPrendida(Qt::magenta);
      ui->graphicsView->setColorCuerdaApagada(Qt::black);
      ui->Puntos->setPalette(Qt::white);
      qDebug()<< "contruimos";
}
/**
*   \fn 		~Jugar( QWidget* )
*   \brief 	    Destructor de la clase
*   \details    Hago los disconects y mando note off de todas las notas
*/
Jugar::~Jugar()
{
    disconnect(conection);
    disconnect(conection1);
    disconnect(conection2);
    for(int i=1;i<29;i++)
        puertoMidi->enviarNoteOff(0, 32 + (uint8_t)i* 2);
    delete ui;
}
/**
*	\fn         void iniciarTimer(void)
*	\brief      inicializa un timer periodico
*	\details    Inicia un timer que ejecuta timer_handler() al terminar
*/
void Jugar::iniciarTimer(int nota)
{
    timerNota[nota]=1;
    QTimer::singleShot(TIME_JUGAR, this, SLOT(timer_handler()));
}
/**
*	\fn         void timer_handler(void)
*	\brief      Handler del timer periodico
*	\details    Pone el cartel de puntos en blanco si esta de un color distinto
*/
void Jugar::timer_handler(void)
{
    int i;
    for(i=0;i<29;i++){
        if(timerNota[i]== 1)
        {
            //pongo el blanco el cartel de los puntos
            timerNota[i]=0;
            ui->Puntos->setPalette(Qt::white);
        }
    }
}
/**
*	\fn         monitoreoPuntos(void)
*	\brief      Slot que cambia el color del cartel de los puntos
*	\details    Ademas suma puntos
*/
void Jugar::monitoreoPuntos(void) {

    //calculo el numero de nota para el array donde pongo q se cambio el color
    //del cartel para esa nota
   char nota= (ui->graphicsView_2->getCuerdaMostrar())*7 +(ui->graphicsView_2->getNroMostrar())+1;
  // char estado; //determina el estado de la nota:
                //-1 : Se paso y no se toco
                //0 : Esta en el futuro
                //1 : Ya se toco bien
                //2 : (Solo largas) se esta tocando
                //3 : Esta en un momento donde se puede tocar
                //4 : Se toco
                //5 : (Solo largas) se solto a mitad de camino
   // 0->no me importa 4->no me importa transitorio en el, 3->espero nota asi q no me importa
  // 5-> amarillo  -1-> rojo  1-> verde  2->azul
   //dependiendo el estado seteo los puntos y sumo puntos o no
   if(ui->graphicsView_2->getEstadoMostrar()==-1){
       ui->Puntos->setPalette(Qt::red);
       iniciarTimer(nota);
   }else if(ui->graphicsView_2->getEstadoMostrar()==1) {
       ui->Puntos->setPalette(Qt::green);
       puntos+=PUNTOCSIMPLE;
       ui->Puntos->setText(QString::number(puntos));
       iniciarTimer(nota);
   }else if(ui->graphicsView_2->getEstadoMostrar()==2) {
       ui->Puntos->setText(QString::number(puntos));
       ui->Puntos->setPalette(Qt::blue);
       puntos+=PUNTOCLARGA;
       ui->Puntos->setText(QString::number(puntos));
       iniciarTimer(nota);
   }else if(ui->graphicsView_2->getEstadoMostrar()==5) {
       ui->Puntos->setPalette(Qt::yellow);
       iniciarTimer(nota);
   }
}
/**
*	\fn         void set_puerto( QSerialPort *puertoExt )
*	\brief      Apunta mi puntero de QSerialPort, a la direccion del puerto que tenemos conectado, y conecta el slot
*	\details    La conecion del slot, sera desconectada en el destructor, para dejar la senal readyRead() libre para otras ventanas
*/
void Jugar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this,  SLOT(on_datosRecibidos() ));
}
/**
*	\fn         setPuertoMidi(ClaseMIDI *puertoExt)
*	\brief      Apunta mi puntero de clase midi al que teniamos en la otra vnetana
* \param      la direccione del puerto
* */
void Jugar::setPuertoMidi(ClaseMIDI *puertoExt)
{
    puertoMidi = puertoExt;
}
/**
*	\fn         setPuntosMax(void)
*	\brief      calculo el puntaje maximo de la cancion
*/
int Jugar::setPuntosMax(void)
{
            int res=0;
            //arranco desde 1 xq la posicion 0 es imposible
            int i=1;
            int cant=0,duracion=0;
            //uso lo mismo que uso en el constructor
            while(i<listaNota.size()-1){

                if(listaNota[i].toInt()>0){
                     int notaAux=-(listaNota[i+1+cant].toInt());
                     int notaCapa=listaNota[i].toInt();
                     while(notaCapa!=(notaAux) && (i+cant+1)<listaNota.size()-1){
                        cant++;
                        notaAux=-(listaNota[i+1+cant].toInt());
                     }

                    if(!cant){
                       duracion=0;
                       res+=PUNTOCSIMPLE;
                    }else{
                        duracion=cant+1;
                        qDebug()<<duracion;
                        cant=0;
                        //si es larga va tener un punto al final como la simple
                        //cuando llega a estado 1 y ademas suma por cada momento en el estado 2
                        res+=PUNTOCLARGA*duracion+PUNTOCSIMPLE;
                    }

                }
                i++;
              }
    return res;
}
/**
*	\fn         void mostrarNota( char nota )
*	\brief      Visualiza las notas tocadas
*	\details    Enciende la nota tocada, en el grafico de la guitarra en pantalla
*   \param      nota: char que contiene el numero de nota tocada
*/
void Jugar::mostrarNota(char nota) {

    int cuerdaYNota = notaACuerdaYNota(std::abs(nota));
    if (nota > 0) {
        if ((cuerdaYNota & 0x000000ff) != 0xff) ui->graphicsView->setNotaPrendida(cuerdaYNota & 0x000000ff);
        ui->graphicsView->setCuerdaPrendida(cuerdaYNota >> 8);
    } else {
        if ((cuerdaYNota & 0x000000ff) != 0xff) ui->graphicsView->setNotaApagada(cuerdaYNota & 0x000000ff);
        ui->graphicsView->setCuerdaApagada(cuerdaYNota >> 8);
    }

   // qDebug() << "Valor nota de mostrar (Nota/Cuerda): " << (cuerdaYNota & 0x000000ff) << "/" << (cuerdaYNota >> 8);
}

/**
*	\fn         void notaACuerdaYNota( uint8_t nota )
*	\brief      Descompone el numero de la nota tocada
*	\details    A partir del numero de nota, obtiene el numero de cuerda y el numero de traste
*   \param      nota: char que contiene el numero de nota tocada
*/
int Jugar::notaACuerdaYNota(uint8_t nota) {
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
   // qDebug() << "Cuerda: " << cuerda << "\nNotaConvertida: " << notaConv;
    ret |= notaConv;
    ret |= cuerda << 8;
    return ret;
}
/**
*	\fn         void on_datosRecibidos( void )
*	\brief      Slot de la interrupcion cada vez que se emite la senal ReadyRead()
*	\details    Guarda la informacion disponible en el puerto en una variable, y llama a setColor()
*/
void Jugar::on_datosRecibidos() {
    bufferSerie.append(puerto->readAll());
    validarDatos();
}
/**
*	\fn 		void validarDatos ( void )
*	\brief 	    Chequea los datos recibidos por el puerto serie
*	\details 	Chequea inicio y fin de trama, y envia los dos bytes de la trama a la funcion procesarNotaATocar()
*/
void Jugar::validarDatos() {
    int cant = bufferSerie.size();
    QByteArray datoAProcesar;
    datoAProcesar.clear();
    while (cant > 1) {
        if (!(bufferSerie[0] & 0x50) && !(bufferSerie[1] & 0x0A) ) {
            datoAProcesar.append(bufferSerie.at(0));
            datoAProcesar.append(bufferSerie.at(1));
            bufferSerie.remove(0, 2);
            procesarNotaATocar(datoAProcesar);
            datoAProcesar.clear();
        } else {
            bufferSerie.remove(0, 1);
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
void Jugar::procesarNotaATocar(QByteArray dato) {
    char nota = 0;
    if (dato.size() != 2) qDebug() << "array de datos con mas de 2 bytes";
    nota |= (uint8_t)(dato.at(0) << 4) & 0xf0;
    nota |= (uint8_t)(dato.at(1) >> 4) & 0x0f;
   // qDebug()<<"la nota es:"<<(uint8_t) nota;
    mostrarNota(nota);
    if (nota < 0) {
        puertoMidi->enviarNoteOff(0, 32 + (uint8_t)std::abs(nota) * 2);
        nota=-nota;
        int cuerda=(nota-1)/7;
        qDebug() <<"MANDAR SOLTAR:C"<<cuerda<<"N"<<(nota-7*(cuerda)-1);
        ui->graphicsView_2->soltarNota(nota-7*(cuerda)-1,cuerda);
    } else {
        puertoMidi->enviarNoteOn(0, 32 + (uint8_t)std::abs(nota) * 2, 127);
        int cuerda=(nota-1)/7;
       // qDebug() <<"C"<<cuerda<<"N"<<(nota-7*(cuerda)-1);
        ui->graphicsView_2->tocarNota(nota-7*(cuerda)-1,cuerda);
    }
}


/**
*	\fn 		void LeerArchivo(void)
*	\brief 	    Lee el archivo y lo pongo en una lista
*/
void Jugar::LeerArchivo(void){
    int i = 0;
    QFile cancion(nombreCancion);
    if(cancion.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&cancion);

        QString aux = in.readLine();
        //while (aux.size()>0)
    //while (!in.atEnd()) //La funcion !in.atEnd() no me funcionaba bien, asi que quizas haya que reemplazarla por otra
     while(!aux.isNull())
     {
        //qDebug()<<"estalapalabra"<<aux;
         listaNota +=aux.split(',');
        // qDebug()<<listaNota.size();
        //listaNota = line.split(QLatin1Char(',')); //guarda lo separado por las comas en posiciones distintas de un array
        //saco el numero de la posicion de la lista
        int tam=(int)listaNota.size();
        listaNota.swapItemsAt(tam-1,tam-2);
        listaNota.removeLast();
        i++;
        aux = in.readLine();
    }
        /*
        for(i=0;i<listaNota.size();i++){
            qDebug()<< "lista[" << i << "] =" <<listaNota[i];
        }*/
    cancion.close();
   qDebug()<<"cerramos leer archivo";
    }
}
/**
*	\fn 		void LeerArchivo(void)
*	\brief 	    Hago uan instancia de la clase dPuntajes
*/
void Jugar::slotPuntaje()
{
   /* int i;
    for(i=1;i<29;i++){
    puertoMidi->enviarNoteOff(0, 32 + (uint8_t)i* 2);
    }*/
    //apago el tiempo de noteview
    ui->graphicsView_2->stopTiempo();
    QString nCancion = nombreCancion;
    nCancion.remove(SONG_FOLDER_PATH);
    nCancion.remove(".csv");
    puntaje estructuraPuntajes;
    int puntosMax=setPuntosMax();
    qDebug()<<"puntaje maximo"<<puntosMax;
    DialogPuntajes dPuntajes(this, puntos,puntosMax);
    if( dPuntajes.exec() != QDialog::DialogCode::Rejected) {
        estructuraPuntajes.iniciales = dPuntajes.getName();
        estructuraPuntajes.puntaje = puntos;
        dPuntajes.close();
        puntajes.agregarPuntaje(nCancion, estructuraPuntajes);
        puntajes.guardarPuntajes();
        QMessageBox::information(this, "Atencion", "Puntaje guardado");
    }else{
        QMessageBox::information(this, "Atencion", "Puntaje descartado");
    }

    hide();//cierro ventana jugar
}

