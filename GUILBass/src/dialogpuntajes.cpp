#include "dialogpuntajes.h"
#include "ui_dialogpuntajes.h"

DialogPuntajes::DialogPuntajes(QWidget *parent, int puntos) :
    QDialog(parent),
    ui(new Ui::DialogPuntajes)
{
    ui->setupUi(this);
    ui->labelNombre->setText("Ingese 3 letras");
    ui->labelBajo->setDisabled(true);
    ui->labelMedio_1->setDisabled(true);
    ui->labelMedio_2->setDisabled(true);
    ui->labelAlto->setDisabled(true);
    if ( PUNTAJE_BAJO )
        ui->labelBajo->setEnabled(true);
    if ( PUNTAJE_BAJO )
    {
        ui->labelMedio_1->setEnabled(true);
        ui->labelMedio_2->setEnabled(true);
    }
    if ( PUNTAJE_BAJO )
        ui->labelAlto->setEnabled(true);
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
