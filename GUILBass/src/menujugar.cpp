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

void MenuJugar::set_puerto( QSerialPort *puertoExt )
{
    puerto = puertoExt;
}

/////////////////////////     PRIVATE SLOTS    //////////////////////////////////////////////////////

void MenuJugar::on_PBpreGrabada_clicked()
{
    // VENTANA CAMI
    Jugar wJugar(this);
    wJugar.setWindowTitle("Jugar");
    hide();
    wJugar.exec();
    close();
}

void MenuJugar::on_PBgrabarNueva_clicked()
{
    // VENTANA MARCOS
    Grabar wGrabar(this);
    hide();
    wGrabar.setWindowTitle("Grabar");
    wGrabar.set_puerto(puerto);
    wGrabar.exec();
}
