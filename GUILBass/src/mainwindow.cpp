#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "../inc/tocar.h"
#include "../inc/menujugar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enumerarPuertos();
    //para probar si no tienen puerto serie virtual para conectarse
    //comenten las 2 dos lineas siguientes
    //ui->PBJugar->setDisabled(true);
    //ui->PBTocar->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enumerarPuertos()
{
    ui->CBPuertos->clear();

    QList<QSerialPortInfo> puertos = QSerialPortInfo::availablePorts();
    for (int i = 0; i < puertos.count(); i++) {
        ui->CBPuertos->addItem(puertos.at(i).portName());
    }
}
void MainWindow::on_PBJugar_clicked()
{
    MenuJugar wmenuJugar(this);
    hide();
    wmenuJugar.setWindowTitle("Maneras de jugar");
    wmenuJugar.exec();
    close();
}

void MainWindow::on_PBTocar_clicked()
{
    Tocar wtocar(this);
    hide();
    wtocar.exec();
    close();

}

void MainWindow::on_PBActualizar_clicked()
{
    enumerarPuertos();
}

void MainWindow::on_PBConectar_clicked()
{
    if (!puerto.isOpen()) {
        QString portName = ui->CBPuertos->currentText();
        puerto.setPortName(portName);
        puerto.setBaudRate(QSerialPort::Baud9600);
        puerto.setDataBits(QSerialPort::Data8);
        puerto.setParity(QSerialPort::NoParity);
        puerto.setStopBits(QSerialPort::OneStop);
        puerto.setFlowControl(QSerialPort::NoFlowControl);

        if (puerto.open(QIODevice::ReadWrite) == true) {
            ui->PBConectar->setText("DESCONECTAR");
            ui->PBTocar->setEnabled(true);
            ui->PBJugar->setEnabled(true);
        } else {
            QMessageBox::critical(this, "Error",
                                  "No se puedo abrir el puerto "+portName);
        }
    } else {
        puerto.close();
        ui->PBConectar->setText("CONECTAR");
        ui->PBTocar->setEnabled(false);
        ui->PBJugar->setEnabled(false);
    }
}
