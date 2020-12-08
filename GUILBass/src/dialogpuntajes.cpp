#include "dialogpuntajes.h"
#include "ui_dialogpuntajes.h"

DialogPuntajes::DialogPuntajes(QWidget *parent, int puntos) :
    QDialog(parent),
    ui(new Ui::DialogPuntajes)
{
    ui->setupUi(this);
    ui->labelNombre->setText("Ingese 3 letras");
    ui->labelBajo->hide();
    ui->labelBajo->hide();
    ui->labelMedio_1->hide();
    ui->labelMedio_2->hide();
    ui->labelAlto->hide();

    if ( PUNTAJE_BAJO )
        ui->labelBajo->show();
    if ( PUNTAJE_BAJO )
    {
        ui->labelMedio_1->show();
        ui->labelMedio_2->show();
    }
    if ( PUNTAJE_BAJO )
        ui->labelAlto->show();
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
