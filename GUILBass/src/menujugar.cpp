#include "inc/menujugar.h"
#include "ui_menujugar.h"
#include "inc/grabar.h"
#include "jugar.h"

MenuJugar::MenuJugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuJugar)
{
    ui->setupUi(this);
}

MenuJugar::~MenuJugar()
{
    delete ui;
}



void MenuJugar::setPuerto(QString name){
    puerto.portName() = name;
    puerto.setBaudRate(QSerialPort::Baud9600);
    puerto.setDataBits(QSerialPort::Data8);
    puerto.setParity(QSerialPort::NoParity);
    puerto.setStopBits(QSerialPort::OneStop);
    puerto.setFlowControl(QSerialPort::NoFlowControl);
    connect(&puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
}



void MenuJugar::on_PBpreGrabada_clicked()
{
    // VENTANA CAMI
    Jugar c(this);
    c.setWindowTitle("Jugar");
    hide();
    c.exec();
}

void MenuJugar::on_PBgrabarNueva_clicked()
{
    // VENTANA MARCOS
    Grabar a(this);
    hide();
    a.setWindowTitle("Grabar");
    a.setPuerto(puerto.portName());
    a.exec();
}
