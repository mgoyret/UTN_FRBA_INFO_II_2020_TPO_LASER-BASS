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


void MainWindow::enviarNota(uint8_t nota)
{
    noteOn(nota);
    noteOff(nota);
}


void MainWindow::noteOn(uint8_t nota)
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
void MainWindow::noteOff(uint8_t nota)
{
    switch (nota) {
    case 1: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_1())); break;
    case 2: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_2())); break;
    case 3: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_3())); break;
    case 4: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_4())); break;
    case 5: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_5())); break;
    case 6: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_6())); break;
    case 7: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_7())); break;
    case 8: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_8())); break;
    case 9: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_9())); break;
    case 10: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_10())); break;
    case 11: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_11())); break;
    case 12: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_12())); break;
    case 13: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_13())); break;
    case 14: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_14())); break;
    case 15: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_15())); break;
    case 16: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_16())); break;
    case 17: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_17())); break;
    case 18: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_18())); break;
    case 19: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_19())); break;
    case 20: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_20())); break;
    case 21: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_21())); break;
    case 22: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_22())); break;
    case 23: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_23())); break;
    case 24: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_24())); break;
    case 25: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_25())); break;
    case 26: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_26())); break;
    case 27: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_27())); break;
    case 28: QTimer::singleShot(TIMER_NOTE_OFF, this, SLOT(timer_handler_28())); break;
    }
}


/////////////////////// SLOTS DE BOTONES

void MainWindow::on_note_1_clicked()
{
    enviarNota(1);
}

void MainWindow::on_note_2_clicked()
{
    enviarNota(2);
}

void MainWindow::on_note_3_clicked()
{
    enviarNota(3);
}

void MainWindow::on_note_4_clicked()
{
    enviarNota(4);
}

void MainWindow::on_note_5_clicked()
{
    enviarNota(5);
}

void MainWindow::on_note_6_clicked()
{
    enviarNota(6);
}

void MainWindow::on_note_7_clicked()
{
    enviarNota(7);
}

void MainWindow::on_note_8_clicked()
{
    enviarNota(8);
}

void MainWindow::on_note_9_clicked()
{
    enviarNota(9);
}

void MainWindow::on_note_10_clicked()
{
    enviarNota(10);
}

void MainWindow::on_note_11_clicked()
{
    enviarNota(11);
}

void MainWindow::on_note_12_clicked()
{
    enviarNota(12);
}

void MainWindow::on_note_13_clicked()
{
    enviarNota(13);
}

void MainWindow::on_note_14_clicked()
{
    enviarNota(14);
}

void MainWindow::on_note_15_clicked()
{
    enviarNota(15);
}

void MainWindow::on_note_16_clicked()
{
    enviarNota(16);
}

void MainWindow::on_note_17_clicked()
{
    enviarNota(17);
}

void MainWindow::on_note_18_clicked()
{
    enviarNota(18);
}

void MainWindow::on_note_19_clicked()
{
    enviarNota(19);
}

void MainWindow::on_note_20_clicked()
{
    enviarNota(20);
}

void MainWindow::on_note_21_clicked()
{
    enviarNota(21);
}

void MainWindow::on_note_22_clicked()
{
    enviarNota(22);
}

void MainWindow::on_note_23_clicked()
{
    enviarNota(23);
}

void MainWindow::on_note_24_clicked()
{
    enviarNota(24);
}

void MainWindow::on_note_25_clicked()
{
    enviarNota(25);
}

void MainWindow::on_note_26_clicked()
{
    enviarNota(26);
}

void MainWindow::on_note_27_clicked()
{
    enviarNota(27);
}

void MainWindow::on_note_28_clicked()
{
    enviarNota(28);
}

////////////////////// HANDLERS PARA NOTEOFF

void MainWindow::timer_handler_1()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA1)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA1)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_2()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA2)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA2)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_3()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA3)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA3)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_4()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA4)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA4)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_5()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA5)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA5)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_6()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA6)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA6)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_7()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA7)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA7)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_8()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA8)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA8)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_9()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA9)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA9)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_10()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA10)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA10)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_11()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA11)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA11)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_12()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA12)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA12)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_13()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA13)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA13)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_14()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA14)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA14)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_15()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA15)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA15)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_16()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA16)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA16)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_17()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA17)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA17)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_18()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA18)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA18)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_19()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA19)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA19)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}


void MainWindow::timer_handler_20()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA20)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA20)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_21()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA21)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA21)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_22()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA22)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA22)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_23()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA23)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA23)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_24()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA24)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA24)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_25()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA25)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA25)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_26()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA26)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA26)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_27()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA27)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA27)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}

void MainWindow::timer_handler_28()
{
    data1=0;
    data1 |= INICIO_TRAMA;
    data1 |= ( ((char)NOTA28)>>4 )&LOW_BITS;

    data2=0;
    data2 |= FIN_TRAMA;
    data2 |= ( (((char)NOTA28)&LOW_BITS )<<4)&BIG_BITS;

    append_send();
}


