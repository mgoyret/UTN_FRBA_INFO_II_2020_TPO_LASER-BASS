#include "dialogborrar.h"
#include "ui_dialogborrar.h"

DialogBorrar::DialogBorrar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBorrar)
{
    ui->setupUi(this);
    ui->comboBox->clear();
    QStringList lista = QDir("../media").entryList();
    for(uint8_t i=0; i<lista.size(); i++)
    {
        if( (lista[i] != ".") && (lista[i] != "..") && (lista[i] != "") )
            ui->comboBox->addItem(lista[i].remove(lista[i].size()-4, 4)); //elimino los .csv
    }
}

DialogBorrar::~DialogBorrar()
{
    delete ui;
}

void DialogBorrar::on_pushButton_2_clicked()
{
    QDialog::reject();
}

void DialogBorrar::on_pushButton_clicked()
{
    if( (QMessageBox::question(this, "Atencion", "Esta seguro que desea eliminar la cancion?")) ==  QMessageBox::StandardButton::Yes)
    {
        QFile songFile((ui->comboBox->currentText()).prepend(SONG_FOLDER_PATH).append(SONG_FILE_TYPE));
        if( !songFile.remove() )
            QMessageBox::critical(this, "Atencion!", "Error al eliminar la cancion");
        else
        {
            QMessageBox::information(this, "Atencion!", "Cancion eliminada");
            parser.borrarCancion( ui->comboBox->currentText() );
            parser.guardarPuntajes();//para que guarde los cambios
            QDialog::accept();
        }
    }

}
