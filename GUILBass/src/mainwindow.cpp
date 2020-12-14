#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "../inc/tocar.h"
#include "../inc/menujugar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int fontID = QFontDatabase::addApplicationFont(":/fonts/neuropol-x-regular.ttf");
    DialogPreferencias pref(this);

    ui->setupUi(this);
    setWindowIcon(QIcon(":/IconoProyectoInfo.ico"));
    setWindowTitle("Menu Principal");
    ui->textBrowser_2->setStyleSheet("border:0px; background:transparent");
    ui->lineEditLaserBass->setStyleSheet("border:0px; background:transparent");
    ui->lineEditLaserBass->setFont(QFont(QFontDatabase::applicationFontFamilies(fontID).at(0), ui->lineEditLaserBass->fontInfo().pointSize(), QFont::Normal, false));
    //para probar si no tienen puerto serie virtual para conectarse
    //comenten las 2 dos lineas siguientes
    ui->PBJugar->setDisabled(true);
    ui->PBTocar->setDisabled(true);
    puerto = new QSerialPort();
    puertoMidi = new ClaseMIDI();
    if (verificarConfiguracionPuertos()) {
        configurarPuertoMidi(pref.getMidiPortPref());
        configurarPuertoSerie(pref.getSerialPortPref());
        ui->PBTocar->setDisabled(false);
        ui->PBJugar->setDisabled(false);
        ui->label->hide();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if (puerto->isOpen()) puerto->close();
    delete puerto;
    if (puertoMidi->estaAbierto()) puertoMidi->cerrarPuerto();
    delete puertoMidi;
}


void MainWindow::on_PBJugar_clicked()
{
    MenuJugar wMenuJugar(this);
    this->hide();
    wMenuJugar.setPuerto(puerto);
    wMenuJugar.setPuertoMidi(puertoMidi);
    wMenuJugar.setWindowTitle("Maneras de jugar");
    wMenuJugar.exec();
    this->show();
}

void MainWindow::on_PBTocar_clicked()
{
    Tocar wtocar(this);
    this->hide();
    wtocar.setPuerto(puerto);
    wtocar.setPuertoMidi(puertoMidi);
    wtocar.exec();
    this->show();
}


bool MainWindow::verificarConfiguracionPuertos() {
    DialogPreferencias pref(this);
    if (pref.getMidiPortPref() != "" && pref.getSerialPortPref() != "") return true;
    return false;
}

void MainWindow::on_actionConexion_triggered()
{
    DialogPreferencias pref(this);
    QString serialPortName = pref.getSerialPortPref();
    QString midiPortName;
    int retValue;
    this->hide();
    retValue = pref.exec();
    midiPortName = pref.getMidiPortPref();
    serialPortName = pref.getSerialPortPref();
    if (retValue == QDialog::Accepted) {
        configurarPuertoSerie(serialPortName);
        configurarPuertoMidi(midiPortName);
    } else {
        if (!verificarConfiguracionPuertos()) {
            ui->PBTocar->setDisabled(true);
            ui->PBJugar->setDisabled(true);
            ui->label->show();
        } else {
            configurarPuertoSerie(serialPortName);
            configurarPuertoMidi(midiPortName);
        }
    }
    this->show();
}

void MainWindow::configurarPuertoSerie(QString portName) {
    if (!puerto->isOpen()) {
        puerto->setPortName(portName);
        puerto->setBaudRate(QSerialPort::Baud9600);
        puerto->setDataBits(QSerialPort::Data8);
        puerto->setParity(QSerialPort::NoParity);
        puerto->setStopBits(QSerialPort::OneStop);
        puerto->setFlowControl(QSerialPort::NoFlowControl);

        if (puerto->open(QIODevice::ReadWrite) == true) {
            ui->PBTocar->setEnabled(true);
            ui->PBJugar->setEnabled(true);
        } else {
            QMessageBox::critical(this, "Error", "No se puedo abrir el puerto "+portName);
        }
    } else if (puerto->portName() != portName) {
        puerto->close();
        configurarPuertoSerie(portName);
    }
}

void MainWindow::configurarPuertoMidi(QString portName) {
    QStringList portNames = puertoMidi->getNombresSalidas();
    for (int i=0; i<portNames.count(); i++) {
        if (portName == portNames[i]) {
            if (puertoMidi->estaAbierto()) puertoMidi->cerrarPuerto(); //no puedo obtener el nombre del puerto abierto, ni el indice
                                                                       //sino podría hacer lo mismo que hice para el serie
            puertoMidi->abrirPuerto(i);
            puertoMidi->inicializarGS();
            puertoMidi->enviarProgramChange(0, 33);
            return;
        }
    }
    QMessageBox::critical(this, "Error", "No se puedo abrir el puerto MIDI " + portName);
}
