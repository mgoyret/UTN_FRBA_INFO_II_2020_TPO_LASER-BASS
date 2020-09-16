#include "inc/grabar.h"
#include "ui_grabar.h"
#include <QMessageBox>

#include "../../inc/mde_grabacion/AP_MdeE.h"
#include "../../inc/mde_grabacion/AP_FuncionesMdeE.h"

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



int notaTocada;
int flag;
int timer_0_25;
int contador;
int grabacion;

//boton iniciar grabacion
void Grabar::on_PBrec_clicked()
{
    FILE* fp = nullptr;

    ui->PBrec->setEnabled(false);
    ui->PBfinRec->setEnabled(true);
    // ACA EMPIEZA EL MECANISMO DE GRABACION

    crearArchivo(fp);

    grabacion = ON;

    inicializar();
    while(grabacion == ON) //suponiendo que aunq este en este while, se atiende el slot si la persona presiona detener
    {
        maquina_grabador(fp);
    }



}

//boton finalizar grabacion
void Grabar::on_PBfinRec_clicked()
{
    QMessageBox::StandardButton opcion;
    ui->PBfinRec->setEnabled(false);
    grabacion = OFF;

    //Pregunto si descartar grabacion o guardar
    opcion = QMessageBox::question(this, "titulo ventana", "guardar?");

    if( opcion == QMessageBox::StandardButton::Yes )
    {
        //se guarda la grabacion. El mensaje "guardada exitosamente" lo agregaria luego de haber implementado el guardado
    }else if ( (opcion == QMessageBox::StandardButton::No) || (opcion == QMessageBox::StandardButton::Escape) )
    {
        QMessageBox::information(this, "Atencion", "Grabacion descartada");
        //se descarta la grabacion
    }else
        QMessageBox::critical(this, "ERROR", "Ocurrio un error inesperado");

    ui->PBrec->setEnabled(true);
}
