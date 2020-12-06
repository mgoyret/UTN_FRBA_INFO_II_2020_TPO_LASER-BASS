#include "dialogjugar.h"
#include "ui_dialogjugar.h"

DialogJugar::DialogJugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogJugar)
{
    ui->setupUi(this);
    ui->comboBox->clear();
    ui->comboBox->addItems(parser.getCanciones());
}
DialogJugar::~DialogJugar()
{
    delete ui;
}

void DialogJugar::on_comboBox_currentIndexChanged(int index)
{
   cancion = ui->comboBox->itemText(index);
}
