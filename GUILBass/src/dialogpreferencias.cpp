#include "dialogpreferencias.h"
#include "ui_dialogpreferencias.h"

DialogPreferencias::DialogPreferencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPreferencias)
{
    ui->setupUi(this);
    prefFile.setFileName(NOMBRE_ARCH_PREFS);
    on_pushButtonMidi_clicked();
    on_pushButtonSerie_clicked();
    cargarPrefs();
    if (!validarPuertoMidi(prefNombrePuertoMidi)) {
        prefNombrePuertoMidi = "";
    } else {
        int cant = puertoMidi.getSalidasDisponibles();
        for (int i=0; i<cant; i++) {
            if (prefNombrePuertoMidi == puertoMidi.getNombreSalida(i).trimmed()){
                ui->comboBoxMidi->setCurrentIndex(i);
                break;
            }
        }
    }
    if (!validarPuertoSerie(prefNombrePuertoSerie)) {
        prefNombrePuertoSerie = "";
    } else {
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for (int i=0; i<ports.count(); i++) {
            if (ports.at(i).portName().trimmed() == prefNombrePuertoSerie) {
                ui->comboBoxSerie->setCurrentIndex(i);
                break;
            }
        }

    }
}

DialogPreferencias::~DialogPreferencias()
{
    delete ui;
}

void DialogPreferencias::cargarPrefs() {
    QString line;
    bool flagConfig = false;
    //static bool configLoaded = false;

    if (prefFile.exists()) {
        if (!prefFile.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        while (!prefFile.atEnd()) {
            line = prefFile.readLine().trimmed();
            if (line == "[LASERBASS Prefs]") flagConfig = true;
            if (flagConfig && line.indexOf('=') != 0) {
                QStringList strl = line.split('=');
                if (strl.at(0).trimmed() == "pSerie") {
                    prefNombrePuertoSerie = strl.at(1).trimmed();
                } else if (strl.at(0).trimmed() == "pMidi") {
                    prefNombrePuertoMidi = strl.at(1).trimmed();
                }
            }
        }
        //configLoaded = true;
        prefFile.close();
    }
}

void DialogPreferencias::on_pushButtonMidi_clicked() {
    ui->comboBoxMidi->clear();
    ui->comboBoxMidi->addItems(puertoMidi.getNombresSalidas());
}


void DialogPreferencias::on_pushButtonSerie_clicked() {
    QList<QSerialPortInfo> puertos = QSerialPortInfo::availablePorts();
    ui->comboBoxSerie->clear();
    for(int i=0; i<puertos.count(); i++) {
        ui->comboBoxSerie->addItem(puertos.at(i).portName());
    }
}

void DialogPreferencias::on_buttonBox_accepted() {
    if (prefFile.exists()) prefFile.remove();
    if (prefFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        prefFile.write("[LASERBASS Prefs]\n");
        prefFile.write("pSerie=");
        prefFile.write(qPrintable(prefNombrePuertoSerie));
        prefFile.write("\npMidi=");
        prefFile.write(qPrintable(prefNombrePuertoMidi));
        prefFile.close();
    }
    this->accept();
}

void DialogPreferencias::on_buttonBox_rejected() {
    this->reject();
}

bool DialogPreferencias::validarPuertoSerie(QString puerto) {
    QList<QSerialPortInfo> puertos = QSerialPortInfo::availablePorts();
    for (int i=0; i<puertos.size(); i++) {
        if (puertos.at(i).portName() == puerto) return true;
    }
    return false;
}

bool DialogPreferencias::validarPuertoMidi(QString puerto) {
    QStringList puertos = puertoMidi.getNombresSalidas();
    for(int i=0; i<puertos.size(); i++) {
        //trimmed: remueve espacios blancos o enters y otros simialares
        if (puertos[i].trimmed() == puerto) return true;
    }
    return false;
}

void DialogPreferencias::on_comboBoxMidi_currentIndexChanged(int index)
{
    prefNombrePuertoMidi = ui->comboBoxMidi->itemText(index);
}

void DialogPreferencias::on_comboBoxSerie_currentIndexChanged(int index)
{
    prefNombrePuertoSerie = ui->comboBoxSerie->itemText(index);
}

QString DialogPreferencias::getSerialPortPref() {
    QString ret = "";
    //cargarPrefs();
    if (validarPuertoSerie(prefNombrePuertoSerie)) {
        ret = prefNombrePuertoSerie;
    }
    return ret;
}

QString DialogPreferencias:: getMidiPortPref() {
    QString ret = "";
    //cargarPrefs();
    if(validarPuertoMidi(prefNombrePuertoMidi)) {
        ret = prefNombrePuertoMidi;
    }
    return ret;
}
