#include "inc/menujugar.h"
#include "ui_menujugar.h"

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

void MenuJugar::on_PBpreGrabada_clicked()
{
    // CAMI ACA INICIA TU VENTANA
}

void MenuJugar::on_PBgrabarNueva_clicked()
{
    // VENTANA MARCOS
}
