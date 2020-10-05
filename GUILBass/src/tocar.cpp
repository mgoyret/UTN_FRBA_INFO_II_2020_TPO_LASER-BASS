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

void Tocar :: setPuerto(QString name){
    puerto.portName()=name;
    puerto.setBaudRate(QSerialPort::Baud9600);
    puerto.setDataBits(QSerialPort::Data8);
    puerto.setParity(QSerialPort::NoParity);
    puerto.setStopBits(QSerialPort::OneStop);
    puerto.setFlowControl(QSerialPort::NoFlowControl);
    connect(&puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
}
void Tocar::on_datosRecibidos(){

    QByteArray datos;
    int cant = int (puerto.bytesAvailable());
    datos.resize(cant);
    puerto.read(datos.data(), cant);
    //Procesar Dato y poner MIDI
    //Funcion que procese el dato y devuelva un string con la nota
    QString nota="#D+";
    ui->Nota->setText(QString(nota));
    //transforma el dato o la nota en el array para setColor
    //29 xq son 28 lugares que hay que cpnfigurar + 1 por el retun 0
    char status[29]="0011010101010111111111111110";
//    setColor(status);
}
/*void Tocar :: setColor(const char* estado){
    QColor red(255,0,0);
    QColor white(255,255,255);
    QColor green(0,255,0);
    if(estado[0]==ON){
        ui->Cuerda1->setPalette(red);
    }else{
        ui->Cuerda1->setPalette(white);
    }
    if(estado[7]==ON){
        ui->Punto6A->setPalette(green);
    }else{
        ui->Punto6A->setPalette(white);
    }
    if(estado[8]==ON){
        ui->Cuerda2->setPalette(green);
    }else{
        ui->Cuerda2->setPalette(white);
    }
    //y asi con el resto a mi se me ocurrio hacer esto para no tener 58 if
    //y de esta forma tmb queda separado lo otro que se me ocurrio sino
    //es q en vez del array uno le entrege un numero de noto y despues en esta funcion
    //pase esa nota al array ,seria otra opcion

}
*/
