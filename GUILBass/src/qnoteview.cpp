#include "qnoteview.h"

QNoteView::QNoteView(QWidget *parent) : QGraphicsView(parent){
    scene = new QGraphicsScene();
    counter = new QGraphicsTextItem("0");
    updateTimer = new QTimer(parent);
    isShown = false;
    msCounter = 0;

    noteArray.clear();
    connect(updateTimer, &QTimer::timeout, this, &QNoteView::moverNotas);
   // connect(this, SIGNAL(puntejeSignal()), this, SLOT(llamoPuntaje()));
    //modifico el borde de la graphicsview y la hago transparente
    //esto es CSS (lo que se usa en pags web)

    this->setStyleSheet("border:0px; background:transparent");

}

QNoteView::~QNoteView() {
    delete scene;
    delete updateTimer;
}

void QNoteView::hideEvent(QHideEvent *event){
    QGraphicsView::hideEvent(event);
    isShown = false;
    stopTiempo();

}

void QNoteView::showEvent(QShowEvent *event) {
    QGraphicsView::showEvent(event);

    int vw = this->viewport()->width(), vh = this->viewport()->height();
    QPen linePen;

    linePen.setColor(Qt::black);
    linePen.setWidth(ANCHO_LINEAS);

    //limpio la escena
    scene->clear();

    //agrego cosita para dibujar un contador por debug
    counter->setPos(0, 0);
    scene->addItem(counter);

    //dibujo las cuerdas y la barra de presente
    for (int i=0; i<4; i++) {
        scene->addLine(0, (vh / 5) * (i + 1), vw, (vh / 5) * (i + 1), linePen);
    }
    scene->addLine(vw - (vw / DENOM_MARGEN_BARRA_PRESENTE)+DEFASAJE, (vh/5) - ALTO_EXTRA_BARRA_PRESENTE, vw - (vw / DENOM_MARGEN_BARRA_PRESENTE)+DEFASAJE, ((4 * vh)/5) + ALTO_EXTRA_BARRA_PRESENTE, linePen);

    //Seteo la escena
    this->setScene(scene);
    this->setSceneRect(0, 0, vw, vh);
    this->show();

    isShown = true;
    startTiempo();
    qDebug() << vw << "x" << vh;
}

void QNoteView::paintEvent(QPaintEvent *event) {
    //
    QGraphicsView::paintEvent(event);
    if (scene->height() != this->viewport()->height() || scene->width() != this->viewport()->width()) {
        this->setSceneRect(0, 0, this->viewport()->width(), this->viewport()->height());
    }
    //int vw = this->viewport()->width(), vh = this->viewport()->height();
    //this->setSceneRect(0, 0, vw, vh);
    //qDebug() << "paintEvent";
    //

}

void QNoteView::startTiempo() {
    msCounter = 0;
    updateTimer->start(BASE_TIEMPO_MS);
}

void QNoteView::stopTiempo() {
    updateTimer->stop();
    msCounter = 0;
}

void QNoteView::moverNotas() {
    int posMaxAMostrar = 0, posMinAMostrar = 0;
    if (noteArray.size() > 0) {
        //como pienso trabajar con una QList ordenada de acuerdo al tiempo de cada nota
        //hasta que tenga una nota
        //A ver, me voy a organizar. Tengo que calcular un par de cosas complicadas.
        //msCounter, y la de la nota esta en el valor pos de su estructura
        //si esta variable es menor que la posicion maxima que entra en la view, la tengo que mostrar;
        posMaxAMostrar = msCounter + (this->viewport()->width() - (int)((float)this->viewport()->width() / (float)DENOM_MARGEN_BARRA_PRESENTE)) / PX_POR_UPD;
        posMinAMostrar = msCounter - (int)((float)this->viewport()->width() / (float)DENOM_MARGEN_BARRA_PRESENTE) / PX_POR_UPD;
       // qDebug()<<"PMINMOSTRAR"<<posMinAMostrar<<"mscounter"<<msCounter<<"ancho"<<(int)((float)this->viewport()->width());
        for (int i=noteArray.size()-1; i>=0; i--) {
            if (noteArray[i].pos < posMaxAMostrar && !noteArray[i].fueDibujada) {

                //seteo las posiciones
                noteArray[i].textPtr->setPos((posMaxAMostrar - noteArray[i].pos) * PX_POR_UPD - RADIO_NUMEROS, (this->viewport()->height() / 5) * (noteArray[i].cuerda + 1) - RADIO_NUMEROS);
                noteArray[i].circlePtr->setPos((posMaxAMostrar - noteArray[i].pos) * PX_POR_UPD - RADIO_NUMEROS, (this->viewport()->height() / 5) * (noteArray[i].cuerda + 1) - RADIO_NUMEROS);
                //seteo el color
                noteArray[i].circlePtr->setBrush(QBrush(noteArray[i].noteColor));
                noteArray[i].circlePtr->setPen(QPen(QBrush(Qt::black), ANCHO_LINEAS));
                noteArray[i].circlePtr->setZValue(1);
                noteArray[i].textPtr->setZValue(1);
                //Mostrar la nota
                scene->addItem(noteArray[i].circlePtr);
                scene->addItem(noteArray[i].textPtr);
                //lo mismo pero en caso de que sea nota larga
                //Lo tengo que hacer aca arriba asi la nota y el numero me quedan arriba
                if (noteArray[i].linePtr != nullptr) {
                    noteArray[i].linePtr->setPos((posMaxAMostrar - noteArray[i].pos - noteArray[i].duracion) * PX_POR_UPD + RADIO_NUMEROS, (this->viewport()->height() / 5) * (noteArray[i].cuerda + 1));
                    noteArray[i].linePtr->setPen(QPen(QBrush(COLOR_DEFAULT), ANCHO_LINEAS));
                    noteArray[i].linePtr->setZValue(0);
                    scene->addItem(noteArray[i].linePtr);
                }

                noteArray[i].fueDibujada = true;
            } else if (noteArray[i].fueDibujada) {
                //muevo la nota
                moverNota(noteArray[i]);
                //agregar la logica de abajo!!
                if (noteArray[i].duracion == 0) {
                    if (noteArray[i].pos + DELAY_NOTA < msCounter && noteArray[i].estado == 3) {
                        noteArray[i].estado = -1;
                        noteArray[i].noteColor = QColor(Qt::red);
                        //--------Mandar signal--------------------
                        mandarSignal(i);
                         //---------------------------------------------------------------
                         noteArray[i].circlePtr->setBrush(QBrush(noteArray[i].noteColor));
                        scene->update(noteArray[i].circlePtr->boundingRect());
                    }
                    if (noteArray[i].pos + DELAY_NOTA > msCounter && noteArray[i].pos < msCounter && noteArray[i].estado == 4) {
                        noteArray[i].noteColor = QColor(Qt::green);
                        noteArray[i].circlePtr->setBrush(QBrush(noteArray[i].noteColor));
                        noteArray[i].estado = 1;
                        //--------Mandar signal--------------------
                        mandarSignal(i);
                         //---------------------------------------------------------------
                        scene->update(noteArray[i].circlePtr->boundingRect());
                    } else if (noteArray[i].pos + DELAY_NOTA > msCounter && noteArray[i].pos < msCounter && noteArray[i].estado == 0) {
                        noteArray[i].estado = 3;
                    }
                    if (noteArray[i].pos > posMinAMostrar) {
                        scene->update(noteArray[i].circlePtr->boundingRect());
                        //scene->update(noteArray[i].textPtr->boundingRect());
                    } else {
                        //si esta en el pasado la remuevo (fuera del pasado que mostramos);
                        delete noteArray[i].textPtr;
                        delete noteArray[i].circlePtr;
                        noteArray.removeAt(i);
                    }
                } else {
                    if (noteArray[i].pos + DELAY_NOTA < msCounter && noteArray[i].estado == 3) {
                        QPen pen = noteArray[i].linePtr->pen();
                        pen.setColor(Qt::red);
                        noteArray[i].linePtr->setPen(pen);
                        noteArray[i].noteColor = QColor(Qt::red);
                        noteArray[i].circlePtr->setBrush(QBrush(noteArray[i].noteColor));
                        noteArray[i].estado = -1;
                        //--------Mandar signal--------------------
                        mandarSignal(i);
                         //---------------------------------------------------------------
                        delete noteArray[i].linePtr2;
                        noteArray[i].linePtr2 = nullptr;
                        scene->update(noteArray[i].circlePtr->boundingRect());
                        scene->update(noteArray[i].linePtr->boundingRect());
                    }
                    if (noteArray[i].pos + DELAY_NOTA > msCounter && noteArray[i].pos <= msCounter && noteArray[i].estado == 4) {
                        noteArray[i].estado = 2;
                        noteArray[i].delayTocado=msCounter-noteArray[i].pos;
                        //--------Mandar signal--------------------
                        mandarSignal(i);
                         //---------------------------------------------------------------
                        noteArray[i].linePtr2 = new QGraphicsLineItem();
                        noteArray[i].linePtr2->setZValue(0);
                        noteArray[i].noteColor = QColor(Qt::blue);
                        noteArray[i].circlePtr->setBrush(QBrush(noteArray[i].noteColor));
                        scene->addItem(noteArray[i].linePtr2);
                    } else if (noteArray[i].pos + DELAY_NOTA > msCounter && noteArray[i].pos <= msCounter && noteArray[i].estado == 0) {
                        noteArray[i].estado = 3;
                    }
                    if ((noteArray[i].pos + noteArray[i].duracion +noteArray[i].delayTocado) > msCounter && noteArray[i].estado == 2) {
                        QPen pen = noteArray[i].linePtr->pen();
                        pen.setColor(Qt::blue);
                        //--------Mandar signal--------------------
                        mandarSignal(i);
                         //---------------------------------------------------------------
                        noteArray[i].linePtr2->setPen(pen);
                        noteArray[i].linePtr2->setLine(noteArray[i].circlePtr->x() + RADIO_NUMEROS, noteArray[i].linePtr->y(), noteArray[i].linePtr->x() + PX_POR_UPD * noteArray[i].duracion, noteArray[i].linePtr->y());
                        scene->update(noteArray[i].linePtr2->boundingRect());
                    }
                    if ((noteArray[i].pos + noteArray[i].duracion + noteArray[i].delayTocado)<= msCounter && noteArray[i].estado == 2) {
                        QPen pen = noteArray[i].linePtr->pen();
                        pen.setColor(Qt::green);
                        noteArray[i].linePtr->setPen(pen);
                        noteArray[i].noteColor = QColor(Qt::green);
                        noteArray[i].circlePtr->setBrush(QBrush(noteArray[i].noteColor));
                        noteArray[i].estado = 1;
                        //--------Mandar signal--------------------
                        mandarSignal(i);
                         //---------------------------------------------------------------
                        delete noteArray[i].linePtr2;
                        noteArray[i].linePtr2 = nullptr;
                        scene->update(noteArray[i].circlePtr->boundingRect());
                        scene->update(noteArray[i].linePtr->boundingRect());
                    }
                    if (noteArray[i].estado == 5) {
                        QPen pen = noteArray[i].linePtr->pen();
                        pen.setColor(Qt::yellow);
                        noteArray[i].linePtr->setPen(pen);
                        noteArray[i].noteColor = QColor(Qt::yellow);
                        noteArray[i].circlePtr->setBrush(QBrush(noteArray[i].noteColor));
                        //--------Mandar signal--------------------
                        mandarSignal(i);
                         //---------------------------------------------------------------
                        //para mi este note aray de abajo no es necesario
                        noteArray[i].estado = -1;
                        delete noteArray[i].linePtr2;
                        noteArray[i].linePtr2 = nullptr;
                        scene->update(noteArray[i].circlePtr->boundingRect());
                        scene->update(noteArray[i].linePtr->boundingRect());
                    }
                    if (noteArray[i].duracion + noteArray[i].pos > posMinAMostrar) {
                        scene->update(noteArray[i].circlePtr->boundingRect());
                        scene->update(noteArray[i].textPtr->boundingRect());
                        scene->update(noteArray[i].linePtr->boundingRect());
                    } else if (noteArray[i].duracion + noteArray[i].pos < posMinAMostrar){
                        //si esta en el pasado la remuevo (fuera del pasado que mostramos);
                        delete noteArray[i].textPtr;
                        delete noteArray[i].circlePtr;
                        delete noteArray[i].linePtr;
                        noteArray.removeAt(i);
                    }
                }
            }
        }
    }
    counter->setPlainText(QString::number(msCounter * BASE_TIEMPO_MS) + QString(" ms / ") + QString::number(posMinAMostrar * BASE_TIEMPO_MS) + QString(" ms"));
    scene->update(counter->boundingRect());
    msCounter++;
   // qDebug()<<msCounter;
    if(msCounter==(tam+DELAY_NOTA)){
        emit puntajeSignal();
    }

}
void QNoteView:: mandarSignal(int i){
    mostrar.nro=noteArray[i].nro;
    mostrar.cuerda=noteArray[i].cuerda;
    mostrar.estado=noteArray[i].estado;
    emit monitoreoSignal();
}
void QNoteView::moverNota(nota & refNota) {
    if (refNota.duracion > 0) {
        if (refNota.duracion + refNota.pos > msCounter && refNota.pos < msCounter && refNota.estado == 2) {
            refNota.linePtr->moveBy(PX_POR_UPD, 0);
        } else {
            refNota.circlePtr->moveBy(PX_POR_UPD, 0);
            refNota.textPtr->moveBy(PX_POR_UPD, 0);
            refNota.linePtr->moveBy(PX_POR_UPD, 0);
        }
    } else {
        refNota.circlePtr->moveBy(PX_POR_UPD, 0);
        refNota.textPtr->moveBy(PX_POR_UPD, 0);
    }
}

bool QNoteView::tocarNota(int nroNota, int nroCuerda) {
    bool ret = false;
    int p=0;

    for (p=0; p<noteArray.size(); p++) {
        //qDebug()<<"POS"<<noteArray[i].pos<< "ARRAY C:"<<noteArray[i].cuerda<<"N:"<<noteArray[i].nro<<"LLEGA C:"<<nroCuerda<<"N:"<<nroNota;
         if (noteArray[ p].nro == nroNota && noteArray[ p].cuerda == nroCuerda) {
             ret = true;
            break;
        }
    }
        //qDebug()<<"tamano"<<noteArray.size()<<"indice"<<(i-1);
        //sino se va de rango no se xq
   // if(noteArray.size() && i>-1 && i<noteArray.size())
     if(ret){
        if (noteArray[ p].estado == 3) {
            noteArray[ p].estado = 4;
            //qDebug()<<"ESTOY EN ESTADO 4";
        }
    }
    return ret;
}

bool QNoteView::soltarNota(int nroNota, int nroCuerda) {
    bool ret = false;
    int j=0;

    for (j=0; j<noteArray.size(); j++) {
       // qDebug()<<"LLEGA C:"<<nroCuerda<<"N:"<<nroNota<<"POS"<<noteArray[j].pos<< "ARRAY C:"<<noteArray[j].cuerda<<"N:"<<noteArray[j].nro;
         if (noteArray[j].nro == nroNota && noteArray[j].cuerda == nroCuerda) {
             ret = true;
            break;
        }
    }
        //sino se va de rango no se xq
   // if(noteArray.size() && i>-1 && i<noteArray.size())
     if(ret && j<noteArray.size()){
          qDebug()<<"POS"<<noteArray[j].pos<<"estado"<<(int)(noteArray[j].estado);
        if (noteArray[j].estado == 2) {
            noteArray[j].estado = 5;
            qDebug()<<"ESTOY EN ESTADO 5";
        }
    }
    return ret;
}
void QNoteView::agregarNota(int nroNota, int nroCuerda, int posTemporal, int duracion) {
    nota aux;

    if (posTemporal > msCounter) {
        if (nroNota > -1 && nroNota < 7) {
            if (nroCuerda > -1 && nroCuerda < 4) {
                aux.nro = nroNota;
                aux.cuerda = nroCuerda;
                aux.pos = posTemporal;
                aux.duracion = duracion;
                qDebug()<<"duracion"<<aux.duracion;
                aux.textPtr = new QGraphicsTextItem(QString::number(nroNota));
                aux.circlePtr = new QGraphicsEllipseItem(0, 0, RADIO_NUMEROS * 2, RADIO_NUMEROS * 2);
                if (duracion > 0) {
                    aux.linePtr = new QGraphicsLineItem(0, 0, aux.duracion * PX_POR_UPD - RADIO_NUMEROS, 0);
                } else {
                    aux.linePtr = nullptr;
                }
                aux.linePtr2 = nullptr;
                aux.fueDibujada = false;
                aux.estado = 0;
                aux.noteColor = QColor(COLOR_DEFAULT);
                noteArray.append(aux);
            }
        }
    }
    //if(noteArray.size()>0)
      // qDebug()<<"pos"<<noteArray[noteArray.size()-1].pos<<"nota"<<noteArray[noteArray.size()-1].nro<<"cuerda"<<noteArray[noteArray.size()-1].cuerda<<"duracion"<<noteArray[noteArray.size()-1].duracion;
}

