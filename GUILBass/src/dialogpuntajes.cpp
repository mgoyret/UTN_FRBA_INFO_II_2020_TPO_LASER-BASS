#include "dialogpuntajes.h"
#include "ui_dialogpuntajes.h"

DialogPuntajes::DialogPuntajes(QWidget *parent, int puntos) :
    QDialog(parent),
    ui(new Ui::DialogPuntajes)
{
    ui->setupUi(this);

    ui->labelNombre->setText("Ingese 3 letras");
    ui->labelBajo->setVisible(false);
    ui->labelBajo->setVisible(false);
    ui->labelMedio_1->setVisible(false);
    ui->labelMedio_2->setVisible(false);
    ui->labelAlto->setVisible(false);


    if ( PUNTAJE_BAJO )
        ui->labelBajo->setVisible(true);
    if ( PUNTAJE_BAJO )
    {
        ui->labelMedio_1->setVisible(true);
        ui->labelMedio_2->setVisible(true);
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
