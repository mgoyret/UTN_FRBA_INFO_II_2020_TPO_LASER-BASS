#include "tablapuntajes.h"
#include "ui_tablapuntajes.h"

TablaPuntajes::TablaPuntajes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TablaPuntajes)
{
    ui->setupUi(this);

    archPuntajes.setFileName(NOMBRE_ARCHIVO);
    if (parser.cargarDesdeArchivo(archPuntajes)) {
        ui->CBselectCancion->clear();
        ui->CBselectCancion->addItems(parser.getCanciones());
    } else {
        QMessageBox::critical(this, "Error!", "Error al leer la tabla de puntajes!");
    }

}

TablaPuntajes::~TablaPuntajes()
{
    delete ui;
}

void TablaPuntajes::on_CBselectCancion_currentIndexChanged(int index)
{
    //aca hay que cambiar los datos de la cancion
    QString cancion = ui->CBselectCancion->itemText(index);
    int cantidadPuntajes = parser.getCantidadPuntajes(cancion);
    QTableWidgetItem * itemTabla;
    puntaje punt;

    ui->TWtablaPuntajes->clear();

    for (int i=0; i<cantidadPuntajes; i++) {
        punt = parser.getPuntaje(cancion, i);
        itemTabla = new QTableWidgetItem(parser.getNombrePuntaje(punt));
        itemTabla->setData(Qt::UserRole, cancion);
        itemTabla->setFlags(Qt::ItemFlag::ItemIsEnabled);
        ui->TWtablaPuntajes->setItem(i + 1, 0, itemTabla);
        itemTabla = new QTableWidgetItem(parser.getNombrePuntaje(punt));
        itemTabla->setData(Qt::TextAlignmentRole, Qt::AlignmentFlag::AlignRight);
        itemTabla->setData(Qt::UserRole, cancion);
        itemTabla->setData(Qt::UserRole + 1, parser.getNombrePuntaje(punt));
        itemTabla->setFlags(Qt::ItemFlag::ItemIsEnabled);
        ui->TWtablaPuntajes->setItem(i + 1, 1, itemTabla);
    }


}
