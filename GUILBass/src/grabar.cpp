#include "inc/grabar.h"
#include "ui_grabar.h"

Grabar::Grabar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabar)
{
    ui->setupUi(this);
}

Grabar::~Grabar()
{
    delete ui;
}

void Grabar::on_PBrec_clicked()
{
    ui->PBrec->serEnabled(false);
    ui->PBfinRec->serEnabled(true);
    // ACA EMPIEZA EL MECANISMO DE GRABACION
}

void Grabar::on_PBfinRec_clicked()
{
    ui->PBfinRec->serEnabled(false);
    //abria que ver aca si al terminar de grabar se puede descartar y
    //arrancar devuelta o q.
    ui->PBrec->serEnabled(true);
}
