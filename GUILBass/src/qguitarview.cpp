#include "qguitarview.h"

QGuitarView::QGuitarView(QWidget *parent) : QGraphicsView(parent){
    scene = new QGraphicsScene();

    //modifico el borde de la graphicsview y la hago transparente
    //esto es CSS (lo que se usa en pags web)
    this->setStyleSheet("border:0px; background:transparent");
    noteArr.clear();
    stringArr.clear();

    //Colores por defecto
    noteColorOff.setRgb  (0,  0, 0);
    stringColorOff.setRgb(0,  0, 0);
    noteColorOn.setRgb   (192,0, 0);
    stringColorOn.setRgb (64, 0, 192);

    isShown = false;

}

QGuitarView::~QGuitarView() {
    for (int i=0; i<noteArr.size(); i++) delete noteArr[i];
    for (int i=0; i<stringArr.size(); i++) delete stringArr[i];
    delete scene;

}

/** 
 *  \fn         showEvent(QShowEvent *event)
 *  \details    Override del evento "show" de una GraphicsView para que dibuje
                la guitarra cuando se muestra
 *  \param      QShowEvent *event
 *  \return     void
 */

void QGuitarView::showEvent(QShowEvent *event){
    QGraphicsView::showEvent(event);
    //obtengo las dimensiones de la parte visible de la GraphicsView
    int vw = this->viewport()->width(), vh = this->viewport()->height();
    QPen stringPen;
    QPen outlinePen;
    
    //Seteo los colores de las cuerdas, las notas y las outlines de la guitarra
    stringPen.setColor(stringColorOff);
    stringPen.setWidth(A_CUERDAS);
    outlinePen.setWidth(A_OUTLINE);
    outlinePen.setColor(Qt::black);

    //Cargo las posiciones de los botones y eso
    stringArr.clear();
    noteArr.clear();

    for (int i = 0; i < 4; i++) {
        stringArr.append(new QGraphicsLineItem((vw / 2) - (L_RECT_MANGO - L_CUAD_CAJA) / 2, (vh / 2) - (A_RECT_MANGO / 2) + static_cast<int>(round((A_RECT_MANGO / 5.0))) * (i + 1), (vw / 2) + (L_RECT_MANGO - (L_RECT_MANGO - L_CUAD_CAJA) / 2), (vh / 2) - (A_RECT_MANGO / 2) + static_cast<int>(round((A_RECT_MANGO / 5.0))) * (i + 1)));
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            noteArr.append(new QGraphicsEllipseItem((vw / 2) - (L_RECT_MANGO - L_CUAD_CAJA) / 2 - R_BOTONES + static_cast<int>(round((L_RECT_MANGO / 7.0))) * (j + 1), (vh / 2) - (A_RECT_MANGO / 2) - R_BOTONES + static_cast<int>(round((A_RECT_MANGO / 5.0))) * (i + 1), 2 * R_BOTONES, 2 * R_BOTONES));
        }
    }

    //Limpiamos la escena para redibujar todo
    scene->clear();

    //hacemos la outline de la guitarra
    //caja
    scene->addRect((vw / 2) - (L_CUAD_CAJA + L_RECT_MANGO) / 2, (vh / 2) - (L_CUAD_CAJA / 2), L_CUAD_CAJA, L_CUAD_CAJA, outlinePen, QBrush());
    //mango
    scene->addRect((vw / 2) - ((L_RECT_MANGO - L_CUAD_CAJA) / 2), (vh / 2) - (A_RECT_MANGO / 2), L_RECT_MANGO, A_RECT_MANGO, outlinePen, QBrush());
    //circulo de la caja
    scene->addEllipse((vw / 2) - (L_RECT_MANGO / 2) - R_CIRC_CAJA, (vh / 2) - R_CIRC_CAJA, 2 * R_CIRC_CAJA, 2 * R_CIRC_CAJA, outlinePen, QBrush());
    //cuerdas
    for (int i = 0; i < 4; i++) {
        stringArr[i]->setPen(stringPen);
        scene->addItem(stringArr[i]);
    }
    //botoncitos en los trastes
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            noteArr[j + (i * 6)]->setBrush(QBrush(noteColorOff, Qt::BrushStyle::SolidPattern));
            noteArr[j + (i * 6)]->setPen(QPen(noteColorOff));
            scene->addItem(noteArr[j + (i * 6)]);
        }
    }

    isShown = true;
    this->setScene(scene);
    this->setSceneRect(0, 0, vw, vh);
}


/** 
 *  \fn         hideEvent(QHideEvent *event)
 *  \details    Override del evento "hide" de una GraphicsView para que avise que
                la guitarra no se muestra mas
 *  \param      QHideEvent *event
 *  \return     void
 */

void QGuitarView::hideEvent(QHideEvent *event){
    QGraphicsView::hideEvent(event);
    isShown = false;
}

/** 
 *  \fn         resizeEvent(QResizeEvent *event)
 *  \details    Override del evento "resize" de una GraphicsView, para
 *              acomodar la guitarra al centro del widget
 *  \param      QResizeEvent *event
 *  \return     void
 */

void QGuitarView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);

    int vw = this->viewport()->width(), vh = this->viewport()->height();
    QPen stringPen;
    QPen notePen;
    QPen outlinePen;
    QBrush noteBrush;
    QGraphicsLineItem *stringAux;
    QGraphicsEllipseItem *noteAux;

    outlinePen.setWidth(A_OUTLINE);
    outlinePen.setColor(Qt::black);

    //Cargo las posiciones de los botones y eso
    if (isShown) {
        for (int i = 0; i < 4; i++) {
            stringAux = stringArr[i];
            stringPen = stringAux->pen();
            stringArr[i] = new QGraphicsLineItem((vw / 2) - (L_RECT_MANGO - L_CUAD_CAJA) / 2, (vh / 2) - (A_RECT_MANGO / 2) + static_cast<int>(round((A_RECT_MANGO / 5.0))) * (i + 1), (vw / 2) + (L_RECT_MANGO - (L_RECT_MANGO - L_CUAD_CAJA) / 2), (vh / 2) - (A_RECT_MANGO / 2) + static_cast<int>(round((A_RECT_MANGO / 5.0))) * (i + 1));
            stringArr[i]->setPen(stringPen);
            delete stringAux;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                noteAux = noteArr[j+i*6];
                notePen = noteAux->pen();
                noteBrush = noteAux->brush();
                noteArr[j+i*6] = new QGraphicsEllipseItem((vw / 2) - (L_RECT_MANGO - L_CUAD_CAJA) / 2 - R_BOTONES + static_cast<int>(round((L_RECT_MANGO / 7.0))) * (j + 1), (vh / 2) - (A_RECT_MANGO / 2) - R_BOTONES + static_cast<int>(round((A_RECT_MANGO / 5.0))) * (i + 1), 2 * R_BOTONES, 2 * R_BOTONES);
                noteArr[j+i*6]->setPen(notePen);
                noteArr[j+i*6]->setBrush(noteBrush);
                delete noteAux;
            }
        }

        //Limpiamos la escena para redibujar todo
        scene->clear();

        //hacemos la outline de la guitarra
        //caja
        scene->addRect((vw / 2) - (L_CUAD_CAJA + L_RECT_MANGO) / 2, (vh / 2) - (L_CUAD_CAJA / 2), L_CUAD_CAJA, L_CUAD_CAJA, outlinePen, QBrush());
        //mango
        scene->addRect((vw / 2) - ((L_RECT_MANGO - L_CUAD_CAJA) / 2), (vh / 2) - (A_RECT_MANGO / 2), L_RECT_MANGO, A_RECT_MANGO, outlinePen, QBrush());
        //circulo de la caja
        scene->addEllipse((vw / 2) - (L_RECT_MANGO / 2) - R_CIRC_CAJA, (vh / 2) - R_CIRC_CAJA, 2 * R_CIRC_CAJA, 2 * R_CIRC_CAJA, outlinePen, QBrush());
        //cuerdas
        for (int i = 0; i < 4; i++) {
            scene->addItem(stringArr[i]);
        }
        //botoncitos en los trastes
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                scene->addItem(noteArr[j + (i * 6)]);
            }
        }


        //dibujo la escena y hago que entre en el widgetview de la pantalla

        this->setScene(scene);
        this->setSceneRect(0, 0, vw, vh);
    }

}

/** 
 *  \fn         setNotaPrendida(int nota)
 *  \details    Enciende una nota en la guitarra
 *  \param      int nro de nota
 *  \return     0: todo correcto	-1: hubo algun error 
 */

int QGuitarView::setNotaPrendida(int nota) {
    if (nota < 0 || nota > noteArr.size() - 1) return -1;
    noteArr[nota]->setPen(QPen(noteColorOn));
    noteArr[nota]->setBrush(QBrush(noteColorOn, Qt::BrushStyle::SolidPattern));
    noteArr[nota]->update();
    return 0;
}

/** 
 *  \fn         setNotaApagada(int nota)
 *  \details    Apaga una nota en la guitarra
 *  \param      int nro de nota
 *  \return     0: todo correcto	-1: hubo algun error 
 */

int QGuitarView::setNotaApagada(int nota) {
    if (nota < 0 || nota > noteArr.size() - 1) return -1;
    noteArr[nota]->setPen(QPen(noteColorOff));
    noteArr[nota]->setBrush(QBrush(noteColorOff, Qt::BrushStyle::SolidPattern));
    noteArr[nota]->update();
    return 0;
}

/** 
 *  \fn         setCuerdaPrendida(int cuerda)
 *  \details    Enciende una cuerda en la guitarra
 *  \param      int nro de cuerda
 *  \return     0: todo correcto	-1: hubo algun error 
 */

int QGuitarView::setCuerdaPrendida(int cuerda) {
    if (cuerda < 0 || cuerda > stringArr.length() - 1) return -1;
    QPen stringPen(stringColorOn);
    stringPen.setWidth(A_CUERDAS);
    stringArr[cuerda]->setPen(stringPen);
    stringArr[cuerda]->update();
    return 0;
}

/** 
 *  \fn         setCuerdaApagada(int cuerda)
 *  \details    Apaga una cuerda en la guitarra
 *  \param      int nro de cuerda
 *  \return     0: todo correcto	-1: hubo algun error 
 */

int QGuitarView::setCuerdaApagada(int cuerda) {
    if (cuerda < 0 || cuerda > stringArr.length() - 1) return -1;
    QPen stringPen(stringColorOff);
    stringPen.setWidth(A_CUERDAS);
    stringArr[cuerda]->setPen(stringPen);
    stringArr[cuerda]->update();
    return 0;
}
