#include "windowpuntajes.h"
#include "ui_windowpuntajes.h"

WindowPuntajes::WindowPuntajes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowPuntajes)
{
    ui->setupUi(this);
}

WindowPuntajes::~WindowPuntajes()
{
    delete ui;
}
