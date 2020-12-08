#include "dialogjugar.h"
#include "ui_dialogjugar.h"

DialogJugar::DialogJugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogJugar)
{
    ui->setupUi(this);
    ui->CBcanciones->clear();
    nombreCancion = "";

    QStringList lista = QDir("../media").entryList();
    QString nombre;
    for (int i = 0; i < lista.size(); i++)
    {
        nombre = lista.at(i);
        if( (nombre != ".") && (nombre != "..") )
            ui->CBcanciones->addItem(lista.at(i));
    }

}

DialogJugar::~DialogJugar()
{
    delete ui;
}

void DialogJugar::on_pushButton_clicked()
{
    nombreCancion = ui->CBcanciones->currentText();
    hide();
}
