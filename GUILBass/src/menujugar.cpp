#include "ui_menujugar.h"
#include <menujugar.h>
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

/////////////////////////     PRIVATE SLOTS    //////////////////////////////////////////////////////

void MenuJugar::on_PBpreGrabada_clicked()
{
    // VENTANA CAMI
    Jugar wJugar(this);
    hide();
    wJugar.setWindowTitle("Jugar");
    wJugar.setPuerto(puerto);
    wJugar.exec();
    close();
}

void MenuJugar::on_PBgrabarNueva_clicked()
{
    // VENTANA MARCOS
    Grabar wGrabar(this);
    hide();
    wGrabar.setWindowTitle("Grabar");
    wGrabar.setPuerto(puerto);
    wGrabar.exec();
}

void MenuJugar::on_PBpuntajes_clicked()
{
    // VENTANA FELIPE
    TablaPuntajes a(this);
    a.setWindowTitle("Puntajes");
    //hide();
    a.exec();
}
