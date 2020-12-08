#include "inc/tocar.h"
#include "ui_tocar.h"

Tocar::Tocar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tocar)
{
    ui->setupUi(this);
    bufferSerie.clear();
    qDebug() << puertoMidi.abrirPuerto(0);
       qDebug() << puertoMidi.getNombreSalida(0) << "\n" << puertoMidi.getNombresSalidas();
       qDebug() << puertoMidi.inicializarGS();
}

Tocar::~Tocar()
{
    delete ui;
}

void Tocar::setPuerto(QSerialPort *puertoExt)
{
    puerto = puertoExt;
    conection = connect(puerto, SIGNAL(readyRead()), this, SLOT(on_datosRecibidos()));
}

void Tocar::setNotaCorrecta(void)
{
    if(notaTocada >= 1 && notaTocada <= 28){
        //prendo la nota

        QGuitarView aux;

        if(aux.setNotaPrendida(notaTocada)){

            aux.setColorNotaPrendida(QColor::fromRgb(0,255,0));
            //aux.setColorCuerdaPrendida(QColor::fromRgb(0,255,0));
        }
    }

    if(notaTocada >= -28 && notaTocada <= -1){
        //apago la nota

        QGuitarView aux;

        if(aux.setNotaApagada(notaTocada)){

            aux.setColorNotaApagada(QColor::fromRgb(255));
            //aux.setColorCuerdaApagada(QColor c);
        }
    }
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

    qDebug() << "Valor nota de mostrar (Nota/Cuerda): " << (cuerdaYNota & 0x000000ff) << "/" << (cuerdaYNota >> 8);
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
    qDebug() << "Cuerda: " << cuerda << "\nNotaConvertida: " << notaConv;
    ret |= notaConv;
    ret |= cuerda << 8;
    return ret;
}

void Tocar::on_datosRecibidos() {
    bufferSerie.append(puerto->readAll());
    validarDatos();
}

void Tocar::validarDatos() {
    int cant = bufferSerie.size();
    QByteArray datoAProcesar;
    datoAProcesar.clear();
    while (cant > 1) {
        if (!(bufferSerie[0] & 0x50)) {
            if (cant == 1) break;
            datoAProcesar.append(bufferSerie[0]);
            datoAProcesar.append(bufferSerie[1]);
            bufferSerie.remove(0, 2);
            procesarNotaATocar(datoAProcesar);
            datoAProcesar.clear();
        } else if (bufferSerie.at(0) & 0x0a) {
            bufferSerie.remove(0,1);
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
    qDebug() << (uint8_t)nota;
    mostrarNota(nota);
    if (nota < 0) {
        qDebug() << puertoMidi.enviarNoteOff(0, 32 + (uint8_t)std::abs(nota) * 2);
    } else {
        qDebug() << puertoMidi.enviarNoteOn(0, 32 + (uint8_t)std::abs(nota) * 2, 127);
    }
}
