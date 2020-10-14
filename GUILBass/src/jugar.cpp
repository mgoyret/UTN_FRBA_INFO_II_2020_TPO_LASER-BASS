#include "jugar.h"
#include "ui_jugar.h"

Jugar::Jugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Jugar)
{
    ui->setupUi(this);
}

Jugar::~Jugar()
{
    delete ui;
}
