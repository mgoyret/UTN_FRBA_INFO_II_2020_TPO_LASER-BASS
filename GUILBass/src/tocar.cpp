#include "inc/tocar.h"
#include "ui_tocar.h"

Tocar::Tocar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tocar)
{
    ui->setupUi(this);
}

Tocar::~Tocar()
{
    delete ui;
}

//Este pushbotton va ser reemplazado por cserie q con la senal va ejecutar el slot
void Tocar::on_pushButton_3_clicked()
{
    static int i=0;
    QColor red(255,0,0);
    QColor white(255,255,255);
    QColor green(0,255,0);
    i++;
    if(i==1){
        ui->Cuerda1->setPalette(red);
        ui->Cuerda2->setPalette(white);
        ui->Cuerda3->setPalette(white);
        ui->Cuerda4->setPalette(white);
        ui->Punto1A->setPalette(white);
        ui->Punto2A->setPalette(white);
        ui->Punto3A->setPalette(white);
        ui->Punto4A->setPalette(green);
        ui->Punto5A->setPalette(white);
        ui->Punto6A->setPalette(white);
        ui->Punto1B->setPalette(white);
        ui->Punto2B->setPalette(white);
        ui->Nota->setText("#F");
    }
    if(i==2){
        ui->Cuerda1->setPalette(white);
        ui->Cuerda2->setPalette(red);
        ui->Cuerda3->setPalette(red);
        ui->Cuerda4->setPalette(white);
        ui->Punto1A->setPalette(white);
        ui->Punto2A->setPalette(white);
        ui->Punto3A->setPalette(white);
        ui->Punto4A->setPalette(white);
        ui->Punto5A->setPalette(white);
        ui->Punto6A->setPalette(white);
        ui->Punto1B->setPalette(white);
        ui->Punto2B->setPalette(red);
        ui->Nota->setText("#D+");
    }

}
