#include "ui_menujugar.h"
#include <menujugar.h>
#include <dialogjugar.h>

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

/////////////////////////     PUBLIC     //////////////////////////////////////////////////////

void MenuJugar::setPuerto( QSerialPort *puertoExt )
{
    puerto = puertoExt;
}

void MenuJugar::setPuertoMidi( ClaseMIDI *puertoExt )
{
    puertoMidi = puertoExt;
}
/////////////////////////     PRIVATE SLOTS    //////////////////////////////////////////////////////
void MenuJugar::on_PBpreGrabada_clicked()
{

    QString nombreCancion = "";
    DialogJugar SeleccionCancion(this);
    SeleccionCancion.exec();
    nombreCancion = SeleccionCancion.getNombreCancion();
    SeleccionCancion.close();
    // VENTANA CAMI
    if( nombreCancion != "" )
    {
        Jugar wJugar(this, nombreCancion);
        wJugar.setWindowTitle("Jugar");
        wJugar.setPuerto(puerto);
        wJugar.setPuertoMidi(puertoMidi);
        wJugar.exec();
    }
}

void MenuJugar::on_PBgrabarNueva_clicked()
{
    // VENTANA MARCOS
    Grabar wGrabar(this);
    wGrabar.setWindowTitle("Grabar");
    wGrabar.setPuerto(puerto);
    wGrabar.setPuertoMidi(puertoMidi);
    wGrabar.exec();
}

void MenuJugar::on_PBpuntajes_clicked()
{
    // VENTANA FELIPE
    TablaPuntajes a(this);
    a.setWindowTitle("Puntajes");
    a.exec();
}

void MenuJugar::on_PBborrar_clicked()
{
    DialogBorrar dBorrar(this);
    dBorrar.exec();
}
