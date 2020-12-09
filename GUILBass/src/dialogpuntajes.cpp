#include "dialogpuntajes.h"
#include "ui_dialogpuntajes.h"

DialogPuntajes::DialogPuntajes(QWidget *parent, int puntos, int puntosMax) :
    QDialog(parent),
    ui(new Ui::DialogPuntajes)
{
    ui->setupUi(this);

    ui->labelNombre->setText("Ingese 3 letras");
    ui->labelMensaje->setText("");

    if ( puntos>0 && puntos<puntosMax/3)
        ui->labelMensaje->setText("Hoy no es tu dia, sigue practicando!");
    if ( puntos>0 && puntos<(puntosMax*2/3))
        ui->labelMensaje->setText("Bien jugado, pero hay mejores formas\nde rascarce la oreja...");
    if ( puntos>(puntosMax*2/3))
        ui->labelMensaje->setText("EXCELENTE! ya podes tocar para el duko");
}

DialogPuntajes::~DialogPuntajes()
{
    delete ui;
}

void DialogPuntajes::on_PBok_clicked()
{
    if( ui->lineNombre->text().size() != 3){
        QMessageBox::warning(this, "Invalido", "Ingrese 3 letras");
    }else
    {
        nombre = ui->lineNombre->text();
        hide();
    }
}
