#include "inc/menujugar.h"
#include "ui_menujugar.h"
#include "inc/grabar.h"
#include "jugar.h"

#include <QDebug>

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


/* Funcion para pasar el nombre del puerto de ventana en ventana */
void MenuJugar::set_nPuerto(QString name)
{
    nPuerto = name;
}



void MenuJugar::on_PBpreGrabada_clicked()
{
    // VENTANA CAMI
    Jugar c(this);
    c.setWindowTitle("Jugar");
    hide();
    c.exec();
    close();
}

void MenuJugar::on_PBgrabarNueva_clicked()
{
    // VENTANA MARCOS
    Grabar a(this);
    hide();
    a.setWindowTitle("Grabar");
    a.setPuerto(nPuerto);
    a.exec();
    a.desconectarPuerto();
    close();
}
