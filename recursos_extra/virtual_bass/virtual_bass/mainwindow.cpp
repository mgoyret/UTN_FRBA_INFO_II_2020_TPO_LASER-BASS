#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


void MainWindow::debug(QByteArray datos)
{
    std::bitset<8> z(datos[0]);
    std::bitset<8> k(datos[1]);
    std::cout << "Trama enviada: " << z << " " << k << std::endl;
}



MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("LASER BASS - TPO INFO II - UTN");
    ui->BassContainer->setDisabled(true);
    enumerarPuertos();

    datos.resize(2);
}

MainWindow::~MainWindow()
{
    if(puerto.isOpen())
        puerto.close();
    delete ui;
}

void MainWindow::enumerarPuertos()
{
    int i;
    QList<QSerialPortInfo> puertos;

    ui->puertosComboBox->clear();
    puertos = QSerialPortInfo::availablePorts();
    for(i=0; i<puertos.count(); i++)
    {
        ui->puertosComboBox->addItem(puertos.at(i).portName());
    }
}

void MainWindow::on_ActualizarButton_clicked()
{
    enumerarPuertos();
}

void MainWindow::on_conectarButton_clicked()
{
    if(!puerto.isOpen())
    {
        QString portName = ui->puertosComboBox->currentText();
        puerto.setPortName(portName);
        // COPIADO DE OTRO CODIGO, LO VEREMOS DESPUES
        //////////////////////////////////////////////////
        puerto.setBaudRate(QSerialPort::Baud9600);
        puerto.setDataBits(QSerialPort::Data8);
        puerto.setParity(QSerialPort::NoParity);
        puerto.setStopBits(QSerialPort::OneStop);
        puerto.setFlowControl(QSerialPort::NoFlowControl);
        //////////////////////////////////////////////////

        if(puerto.open(QIODevice::ReadWrite) == true)
        {
            ui->conectarButton->setText("Desconectar");
            ui->puertosComboBox->setDisabled(true);
            ui->ActualizarButton->setDisabled(true);
            ui->BassContainer->setEnabled(true);
            ui->statusbar->showMessage(puerto.portName()+" conectado", 4000);

            //connect(&puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
        }else
        {
            QMessageBox::critical(this, "ERROR", "No pudo abrirse el puerto: "+portName);
        }
    } else
    {
        puerto.close();
        ui->conectarButton->setText("Conectar");
        ui->puertosComboBox->setEnabled(true);
        ui->ActualizarButton->setEnabled(true);
        ui->BassContainer->setDisabled(true);
        ui->statusbar->showMessage(puerto.portName()+" desconectado", 4000);
    }
}

//arma el QByteArray y lo envia por puertoserie
void MainWindow::append_send()
{
    datos.clear();
    datos.append(data1);
    datos.append(data2);
    puerto.write(datos.data(), datos.size());
    #ifdef  DEBUG
        debug(datos);
    #endif
}


void MainWindow::noteOn(char nota)
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= (nota>>4)&LOW_BITS; //el & por las dudas

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ((nota&LOW_BITS)<<4)&BIG_BITS;

    append_send();
}

//se podria desarrollar con puntero a funcion, haciendo todos los defines correspondientes timer_handler[i]
void MainWindow::noteOff(char nota)
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)(-nota))>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)(-nota))&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}


void MainWindow::on_note_1_pressed()
{
    noteOn(NOTA1);
}

void MainWindow::on_note_2_pressed()
{
    noteOn(NOTA2);
}

void MainWindow::on_note_3_pressed()
{
    noteOn(NOTA3);
}

void MainWindow::on_note_4_pressed()
{
    noteOn(NOTA4);
}

void MainWindow::on_note_5_pressed()
{
    noteOn(NOTA5);
}

void MainWindow::on_note_6_pressed()
{
    noteOn(NOTA6);
}

void MainWindow::on_note_7_pressed()
{
    noteOn(NOTA7);
}

void MainWindow::on_note_8_pressed()
{
    noteOn(NOTA8);
}

void MainWindow::on_note_9_pressed()
{
    noteOn(NOTA9);
}

void MainWindow::on_note_10_pressed()
{
    noteOn(NOTA10);
}

void MainWindow::on_note_11_pressed()
{
    noteOn(NOTA11);
}

void MainWindow::on_note_12_pressed()
{
    noteOn(NOTA12);
}

void MainWindow::on_note_13_pressed()
{
    noteOn(NOTA13);
}

void MainWindow::on_note_14_pressed()
{
    noteOn(NOTA14);
}

void MainWindow::on_note_15_pressed()
{
    noteOn(NOTA15);
}

void MainWindow::on_note_16_pressed()
{
    noteOn(NOTA16);
}

void MainWindow::on_note_17_pressed()
{
    noteOn(NOTA17);
}

void MainWindow::on_note_18_pressed()
{
    noteOn(NOTA18);
}

void MainWindow::on_note_19_pressed()
{
    noteOn(NOTA19);
}

void MainWindow::on_note_20_pressed()
{
    noteOn(NOTA20);
}

void MainWindow::on_note_21_pressed()
{
    noteOn(NOTA21);
}

void MainWindow::on_note_22_pressed()
{
    noteOn(NOTA22);
}

void MainWindow::on_note_23_pressed()
{
    noteOn(NOTA23);
}

void MainWindow::on_note_24_pressed()
{
    noteOn(NOTA24);
}

void MainWindow::on_note_25_pressed()
{
    noteOn(NOTA25);
}

void MainWindow::on_note_26_pressed()
{
    noteOn(NOTA26);
}

void MainWindow::on_note_27_pressed()
{
    noteOn(NOTA27);
}

void MainWindow::on_note_28_pressed()
{
    noteOn(NOTA28);
}




void MainWindow::on_note_1_released()
{
    noteOff(NOTA1);
}

void MainWindow::on_note_2_released()
{
    noteOff(NOTA2);
}

void MainWindow::on_note_3_released()
{
    noteOff(NOTA3);
}

void MainWindow::on_note_4_released()
{
    noteOff(NOTA4);
}

void MainWindow::on_note_5_released()
{
    noteOff(NOTA5);
}

void MainWindow::on_note_6_released()
{
    noteOff(NOTA6);
}

void MainWindow::on_note_7_released()
{
    noteOff(NOTA7);
}

void MainWindow::on_note_8_released()
{
    noteOff(NOTA8);
}

void MainWindow::on_note_9_released()
{
    noteOff(NOTA9);
}

void MainWindow::on_note_10_released()
{
    noteOff(NOTA10);
}

void MainWindow::on_note_11_released()
{
    noteOff(NOTA11);
}

void MainWindow::on_note_12_released()
{
    noteOff(NOTA12);
}

void MainWindow::on_note_13_released()
{
    noteOff(NOTA13);
}

void MainWindow::on_note_14_released()
{
    noteOff(NOTA14);
}

void MainWindow::on_note_15_released()
{
    noteOff(NOTA15);
}

void MainWindow::on_note_16_released()
{
    noteOff(NOTA16);
}

void MainWindow::on_note_17_released()
{
    noteOff(NOTA17);
}

void MainWindow::on_note_18_released()
{
    noteOff(NOTA18);
}

void MainWindow::on_note_19_released()
{
    noteOff(NOTA19);
}

void MainWindow::on_note_20_released()
{
    noteOff(NOTA20);
}

void MainWindow::on_note_21_released()
{
    noteOff(NOTA21);
}

void MainWindow::on_note_22_released()
{
    noteOff(NOTA22);
}

void MainWindow::on_note_23_released()
{
    noteOff(NOTA23);
}

void MainWindow::on_note_24_released()
{
    noteOff(NOTA24);
}

void MainWindow::on_note_25_released()
{
    noteOff(NOTA25);
}

void MainWindow::on_note_26_released()
{
    noteOff(NOTA26);
}

void MainWindow::on_note_27_released()
{
    noteOff(NOTA27);
}

void MainWindow::on_note_28_released()
{
    noteOff(NOTA28);
}

