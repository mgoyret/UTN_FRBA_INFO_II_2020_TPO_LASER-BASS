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

//aca hay que llamar a la aplicacion de grabar
void MenuJugar::on_PBGrabar_clicked()
{

}

//aca hay que llamar a la app de jugar
void MenuJugar::on_PBJugar_clicked()
{

}


//hay que abrir la ventana de puntajes aca
void MenuJugar::on_PBVerpuntaje_clicked()
{

}

//handler para cuando se cambia el tema (por si hay que procesar algo)
void MenuJugar::on_CBTemas_currentIndexChanged(int index)
{

}
