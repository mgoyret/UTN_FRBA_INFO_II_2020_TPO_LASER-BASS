#include "inc/tocar.h"
#include "ui_tocar.h"

Tocar::Tocar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tocar)
{
    ui->setupUi(this);
    bufferSerie.clear();
}

Tocar::~Tocar()
{
    disconnect(conection);
    for(int i=1;i<29;i++)
        puertoMidi->enviarNoteOff(0, 32 + (uint8_t)i* 2);
    //qDebug()<<"allnoteOFF";
    delete ui;
}

void Tocar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
}

void Tocar::setPuertoMidi(ClaseMIDI *puertoExt)
{
    puertoMidi = puertoExt;
}

void Tocar::mostrarNota(char nota) {
    int cuerdaYNota = notaACuerdaYNota(std::abs(nota));
    if (nota > 0) {
        if ((cuerdaYNota & 0x000000ff) != 0xff) ui->graphicsView->setNotaPrendida(cuerdaYNota & 0x000000ff);
        ui->graphicsView->setCuerdaPrendida(cuerdaYNota >> 8);
    } else {
        if ((cuerdaYNota & 0x000000ff) != 0xff) ui->graphicsView->setNotaApagada(cuerdaYNota & 0x000000ff);
        ui->graphicsView->setCuerdaApagada(cuerdaYNota >> 8);
    }

    //qDebug() << "Valor nota de mostrar (Nota/Cuerda): " << (cuerdaYNota & 0x000000ff) << "/" << (cuerdaYNota >> 8);
}


void Tocar::on_datosRecibidos() {
    bufferSerie.append(puerto->readAll());
    validarDatos();
}

void Tocar::validarDatos() {
    int cant = bufferSerie.size();
    QByteArray datoAProcesar;
    while (cant > 1) {
        if (!(bufferSerie[0] & 0x50) && !(bufferSerie[1] & 0x0A) ) {
            datoAProcesar.clear();
            datoAProcesar.append(bufferSerie[0]);
            datoAProcesar.append(bufferSerie[1]);
            bufferSerie.remove(0, 2);
            procesarNotaATocar(datoAProcesar);
        } else {
            bufferSerie.remove(0, 1);
        }
        cant = bufferSerie.size();
    }
}

void Tocar::procesarNotaATocar(QByteArray dato) {
    char nota = 0;
    if (dato.size() != 2) qDebug() << "array de datos con mas de 2 bytes";
    nota |= (uint8_t)(dato.at(0) << 4) & 0xf0;
    nota |= (uint8_t)(dato.at(1) >> 4) & 0x0f;
   // qDebug() <<"la nota es"<<(int)nota;
   // qDebug() << "conversion a MIDI: " << notaANotaMidi((uint8_t)std::abs(nota));
    mostrarNota(nota);
    if (nota < 0) {
        qDebug() << puertoMidi->enviarNoteOff(0, notaANotaMidi((uint8_t)std::abs(nota)));
    } else {
        qDebug() << puertoMidi->enviarNoteOn(0, notaANotaMidi((uint8_t)std::abs(nota)), 127);
    }
}

uint8_t Tocar::notaANotaMidi(uint8_t nota) {
    uint8_t cuerda = (nota - 1) / 7;
    uint8_t traste = (nota - 1) % 7;
    return NOTAS_BASE + NOTAS_DESP_POR_CUERDA * cuerda + NOTAS_DESP_POR_TRASTE * traste;
}

int Tocar::notaACuerdaYNota(uint8_t nota) {
    int ret = 0, cuerda = 0, notaConv = 0;
    nota--;
    notaConv = nota % 7;
    if (notaConv) {
        cuerda = nota / 7;
        notaConv = (6 - notaConv) + (6 * cuerda);
    } else {
        cuerda = nota / 7;
        notaConv = 0xff;
    }
   // qDebug() << "Cuerda: " << cuerda << "\nNotaConvertida: " << notaConv;
    ret |= notaConv;
    ret |= cuerda << 8;
    return ret;
}
