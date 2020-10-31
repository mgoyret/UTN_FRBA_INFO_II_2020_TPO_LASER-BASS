#ifndef TABLAPUNTAJES_H
#define TABLAPUNTAJES_H

#include <parserpuntaje.h>
#include <QDialog>
#include <QFile>

#define NOMBRE_ARCHIVO "asd.txt"


namespace Ui {
class TablaPuntajes;
}

class TablaPuntajes : public QDialog
{
    Q_OBJECT

public:
    explicit TablaPuntajes(QWidget *parent = nullptr);
    ~TablaPuntajes();

private slots:
    void on_CBselectCancion_currentIndexChanged(int index);

private:
    Ui::TablaPuntajes *ui;
    QFile archPuntajes;
    ParserPuntaje parser;

    int recargarPuntajes();

};

#endif // TABLAPUNTAJES_H
