#include "grabar.h"
#include "ui_grabar.h"

grabar::grabar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::grabar)
{
    ui->setupUi(this);
}

grabar::~grabar()
{
    delete ui;
}
