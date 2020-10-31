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
    // VENTANA CAMI
    Jugar c(this);
    c.setWindowTitle("Jugar");
    //hide();
    c.exec();
}

void MenuJugar::on_PBgrabarNueva_clicked()
{
    // VENTANA MARCOS
    Grabar a(this);
    a.setWindowTitle("Grabar");
    //hide();
    a.exec();
}

void MenuJugar::on_PBpuntajes_clicked()
{
    // VENTANA FELIPE
    TablaPuntajes a(this);
    a.setWindowTitle("Puntajes");
    //hide();
    a.exec();
}
