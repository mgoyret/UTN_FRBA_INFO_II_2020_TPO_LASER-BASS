#ifndef QGUITARVIEW_H
#define QGUITARVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QPainterPath>
#include <cmath>
#include <QList>
#include <QVector2D>
#include <QVector4D>

#define L_CUAD_CAJA     128
#define L_RECT_MANGO    256
#define A_RECT_MANGO    64
#define R_BOTONES       4
#define R_CIRC_CAJA     32
#define A_CUERDAS       2
#define A_OUTLINE       2

class QGuitarView : public QGraphicsView
{
    Q_OBJECT


public:
    QGuitarView(QWidget *parent = nullptr);
    ~QGuitarView();

    int setNotaPrendida(int);
    int setNotaApagada(int);
    int setCuerdaPrendida(int);
    int setCuerdaApagada(int);
    inline void setColorNotaPrendida(QColor c) {noteColorOn = c;};
    inline void setColorCuerdaPrendida(QColor c) {stringColorOn = c;};
    inline void setColorNotaApagada(QColor c) {noteColorOff = c;};
    inline void setColorCuerdaApagada(QColor c) {stringColorOff = c;};


private:
    QGraphicsScene * scene;
    QColor noteColorOn;
    QColor noteColorOff;
    QColor stringColorOn;
    QColor stringColorOff;
    QList<QGraphicsEllipseItem *> noteArr;
    QList<QGraphicsLineItem *> stringArr;
    bool isShown;

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

};

#endif // QGUITARVIEW_H
