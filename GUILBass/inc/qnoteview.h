#ifndef QNOTEVIEW_H
#define QNOTEVIEW_H

#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QList>
#include <QColor>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include "qguitarview.h"
#define ALTO_EXTRA_BARRA_PRESENTE 9
#define DENOM_MARGEN_BARRA_PRESENTE 5
#define ANCHO_LINEAS 1
#define RADIO_NUMEROS 9
#define BASE_TIEMPO_MS 50
#define DELAY_NOTA 16
//las notas futuras no suenan pero con este define se puede mover la linea
//para q la linea de presente este mas adelante y por lo tanto el usuario
//pueda toque un toqeucin antes de esta linea sea correcto
#define DEFASAJE 10
//cant de piclies q se corre mientras mas chico mas lento va
#define PX_POR_UPD 3
#define COLOR_DEFAULT Qt::gray

typedef struct {
    int nro; // nro de nota
    int cuerda;  //cuerda donde va
    int pos;  //posicion en unidades de base de tiempo
    int duracion;  //para saber si es larga o corta;
    int delayTocado;//solo se usa para las largas para saber cuando se tocaron para despues finalizarlas
    char estado; //determina el estado de la nota:
                 //-1 : Se paso y no se toco
                 //0 : Esta en el futuro
                 //1 : Ya se toco bien
                 //2 : (Solo largas) se esta tocando
                 //3 : Esta en un momento donde se puede tocar
                 //4 : Se toco
                 //5 : (Solo largas) se solto a mitad de camino
    bool fueDibujada;  //Para saber si ya fue mostrada en pantalla
    QGraphicsLineItem * linePtr; //puntero para el rectangulo que conecta el noteon con el noteoff
    QGraphicsLineItem * linePtr2;  //Puntero para la linea cuando se toca la nota
    QGraphicsEllipseItem * circlePtr; //puntero para el circulito de la nota
    QGraphicsTextItem * textPtr; //puntero para el texto de la nota.
    QColor noteColor; //color de fondo de la nota
} nota;

class QNoteView : public QGraphicsView
{

Q_OBJECT

public:
    QNoteView(QWidget* parent = nullptr);
    ~QNoteView();
    //0 es q dura una sola base,1 es que hay que matenerlo una base mas
    void agregarNota(int nroNota, int nroCuerda, int posTemporal, int duracion = 0);
    bool tocarNota(int nroNota, int nroCuerda);
    bool soltarNota(int nroNota, int nroCuerda);
    int tam;
    void startTiempo();
    void stopTiempo();
    inline int getCuerdaMostrar(void) {return mostrar.cuerda;};
    inline int getNroMostrar(void) {return mostrar.nro;};
    inline int getEstadoMostrar(void) {return mostrar.estado;};
signals:
    void monitoreoSignal();
    void puntajeSignal();
private:
    QList<nota> noteArray;
    QGraphicsScene * scene;
    QGraphicsTextItem *counter;
    QTimer * updateTimer;
    bool isShown;
    int msCounter;
    nota mostrar;
    void mandarSignal(int i);
    void moverNota(nota &);
private slots:
    void moverNotas();
protected:
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // QNOTEVIEW_H
