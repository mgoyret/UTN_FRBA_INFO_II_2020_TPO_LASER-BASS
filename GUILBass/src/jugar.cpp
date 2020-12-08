#include "jugar.h"
#include "ui_jugar.h"

Jugar::Jugar(QWidget *parent, QString nombre) :
    QDialog(parent),
    ui(new Ui::Jugar)
{
    ui->setupUi(this);
    bufferSerie.clear();
    nombreCancion = nombre;
    nombreCancion=nombreCancion.prepend("../media/");
    qDebug()<< "el nombre es:"<<nombreCancion;
      LeerArchivo();
      //cargar archivo
      puntajes.cargarDesdeArchivo();
      int i=0;
      int cuerda,nota,cant=0,duracion=0;
      //lista
      qDebug()<<"size de lista"<<listaNota.size();
      while(i<listaNota.size()-1){
          /*1----7 Cuerda 1
          8----14   Cuerda 2
          15---21   Cuerda 3
          22---28   Cuerda 4*/
          //las cuerdas van d e0 a 3 y las notas de 0 a 6
        cuerda =std::abs((listaNota[i].toInt()/4)-1);
        nota= std::abs((listaNota[i].toInt()-7*cuerda)-1);
        //el array de notas tiene q ser igual al del archivo xq sino es posible perder info
         while(listaNota[i]!=listaNota[i+1]){
            cant++;
            i++;
         }
        if(!cant){
           duracion=0;
        }else{
            duracion=cant;
            i-=cant;
            cant=0;
        }
        ui->graphicsView_2->agregarNota(nota,cuerda,i,duracion);
        i++;
      }
      connect(puerto, SIGNAL(monitoreoSignal()), this, SLOT(monitoreoPuntos()));
      //despues hay q apagarlo
      ui->graphicsView_2->startTiempo();
      ui->graphicsView->setColorNotaApagada(Qt::black);
      ui->graphicsView->setColorNotaPrendida(Qt::darkRed);
      ui->graphicsView->setColorCuerdaPrendida(Qt::darkRed);
      ui->graphicsView->setColorCuerdaApagada(Qt::black);
      ui->Puntos->setPalette(Qt::white);
}


Jugar::~Jugar()
{
    delete ui;
}
void Jugar::iniciarTimer(int nota)
{
    timerNota[nota]=1;
    QTimer::singleShot(TIMER_TIME_, this, SLOT(timer_handler()));
}
void Jugar::timer_handler()
{
    int i;
    for(i=0;i<29;i++){
        if(timerNota[i]== 1)
        {
            i=-i;
            mostrarNota(-i);
            ui->Puntos->setPalette(Qt::white);
        }
    }
}
void Jugar::monitoreoPuntos() {

    //esto es lo que tengo
    //cuerda =(listaNota[i].toInt()/4)-1;
    //nota= (listaNota[i].toInt()-7*cuerda)-1;
    //necesito llevarlo a lo que habia
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
  // 5-> poner amarillo es medio punto -1-> rojo  1-> verde
   if(ui->graphicsView_2->getEstadoMostrar()==-1){
       //ESTO DE PALETTA NI IDEA SI ANDA O HAY Q PONERLE DE OTRA FORMA EL COLOR
       ui->Puntos->setPalette(Qt::red);
   }else if(ui->graphicsView_2->getEstadoMostrar()==1) {
       //ESTO DE PALETTA NI IDEA SI ANDA O HAY Q PONERLE DE OTRA FORMA EL COLOR
       ui->Puntos->setPalette(Qt::green);
       puntos+=PUNTOCSIMPLE;
       ui->Puntos->setText(QString::number(puntos));
       iniciarTimer(nota);
   }else if(ui->graphicsView_2->getEstadoMostrar()==2) {
       pesoPunto+=1;
       ui->Puntos->setText(QString::number(puntos));
       ui->Puntos->setPalette(Qt::blue);
       puntos=puntos+pesoPunto*(int)PUNTOCSIMPLE;
       ui->Puntos->setText(QString::number(puntos));
       iniciarTimer(nota);
   }else if(ui->graphicsView_2->getEstadoMostrar()==5) {
       ui->Puntos->setPalette(Qt::darkYellow);
       //esto lo dejo en dark yellow para poder diferenciar entre estados
       //despues se puede poner red
       pesoPunto=0;
       iniciarTimer(nota);
   }
   mostrarNota(nota);
   //muestro qguitarview y puntos
}
void Jugar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this,  SLOT(on_datosRecibidos() ));
}
void Jugar::mostrarNota(char nota) {

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
    qDebug() << "Cuerda: " << cuerda << "\nNotaConvertida: " << notaConv;
    ret |= notaConv;
    ret |= cuerda << 8;
    return ret;
}
void Jugar::on_datosRecibidos() {
    bufferSerie.append(puerto->readAll());
    validarDatos();
}
void Jugar::validarDatos() {
    int cant = bufferSerie.size();
    QByteArray datoAProcesar;
    datoAProcesar.clear();
    while (cant > 1) {
        if (bufferSerie[0] & 0x50) {
            if (cant == 1) break;
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

void Jugar::procesarNotaATocar(QByteArray dato) {
    char nota = 0;
    if (dato.size() != 2) qDebug() << "array de datos con mas de 2 bytes";
    nota |= (uint8_t)(dato.at(0) << 4) & 0xf0;
    nota |= (uint8_t)(dato.at(1) >> 4) & 0x0f;
    qDebug() << (uint8_t)nota;
    if (nota < 0) {
        qDebug() << puertoMidi->enviarNoteOff(0, 32 + (uint8_t)std::abs(nota) * 2);
        nota=-nota;
        ui->graphicsView_2->soltarNota(nota/7,nota-7*(nota/7)-1);
    } else {
        qDebug() << puertoMidi->enviarNoteOn(0, 32 + (uint8_t)std::abs(nota) * 2, 127);
        ui->graphicsView_2->tocarNota(nota/7,nota-7*(nota/7)-1);
    }
}

/*
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
}*/
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
        qDebug()<<"estalapalabra"<<aux;
         listaNota +=aux.split(',');
         qDebug()<<listaNota.size();
        //listaNota = line.split(QLatin1Char(',')); //guarda lo separado por las comas en posiciones distintas de un array
        //saco el numero de la posicion de la lista
        int tam=(int)listaNota.size();
        listaNota.swapItemsAt(tam-1,tam-2);
        listaNota.removeLast();
        i++;
        qDebug()<<listaNota.size();
        aux = in.readLine();
    }
        /*
        for(i=0;i<listaNota.size();i++){
            qDebug()<< "lista[" << i << "] =" <<listaNota[i];
        }*/
    cancion.close();
    }
}

void Jugar::slotPuntaje()
{
    ui->graphicsView_2->stopTiempo();
    QString nombreCancion = "";
    puntaje estructuraPuntajes;
    DialogPuntajes dPuntajes(this, puntos);
    dPuntajes.exec();
    estructuraPuntajes.iniciales = dPuntajes.getName();
    estructuraPuntajes.puntaje = puntos;
    dPuntajes.close();
    puntajes.agregarPuntaje(nombreCancion, estructuraPuntajes);
    puntajes.guardarPuntajes();
    puntajes.guardarArchivo();
    hide();//cierro ventana jugar
}

