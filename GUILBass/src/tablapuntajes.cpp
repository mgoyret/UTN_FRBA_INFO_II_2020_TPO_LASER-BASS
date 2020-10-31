#include "tablapuntajes.h"
#include "ui_tablapuntajes.h"

TablaPuntajes::TablaPuntajes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TablaPuntajes)
{
    ui->setupUi(this);
    ui->TWtablaPuntajes->verticalHeader()->hide();
    ui->TWtablaPuntajes->horizontalHeader()->hide();
    ui->TWtablaPuntajes->horizontalHeader()->setStretchLastSection(true);

    ui->CBselectCancion->clear();
    ui->CBselectCancion->addItems(parser.getCanciones());
    //QMessageBox::critical(this, "Error!", "Error al leer la tabla de puntajes!");

}

TablaPuntajes::~TablaPuntajes()
{
    //Deleteo los contenidos de las celdas
    for (int i=0; i < ui->TWtablaPuntajes->rowCount(); i++) {
        for (int j=0; j < ui->TWtablaPuntajes->columnCount(); j++) {
            delete ui->TWtablaPuntajes->item(i, j);
        }
    }
    delete ui;
}

void TablaPuntajes::on_CBselectCancion_currentIndexChanged(int index)
{
    //aca hay que cambiar los datos de la cancion
    QString cancion = ui->CBselectCancion->itemText(index);
    int cantidadPuntajes = parser.getCantidadPuntajes(cancion);
    QTableWidgetItem * itemTabla;
    puntaje punt;
    QBrush headerBrush(Qt::red, Qt::BrushStyle::Dense6Pattern);


    //me encargo de limpiar los items anteriores
    for (int i=0; i < ui->TWtablaPuntajes->rowCount(); i++) {
        for (int j=0; j < ui->TWtablaPuntajes->columnCount(); j++) {
            delete ui->TWtablaPuntajes->item(i, j);
        }
    }
    //limpio la tabla
    ui->TWtablaPuntajes->clear();
    ui->TWtablaPuntajes->setRowCount(cantidadPuntajes + 1);
    ui->TWtablaPuntajes->setColumnCount(2);
    //creo los headers
    itemTabla = new QTableWidgetItem("Iniciales");
    itemTabla->setData(Qt::UserRole, "Header");
    itemTabla->setTextAlignment(Qt::AlignHCenter + Qt::AlignVCenter);
    itemTabla->setFlags(Qt::ItemFlag::ItemIsEnabled);
    itemTabla->setBackground(headerBrush);
    ui->TWtablaPuntajes->setItem(0, 0, itemTabla);
    itemTabla = new QTableWidgetItem("Puntaje\t");
    itemTabla->setTextAlignment(Qt::AlignRight + Qt::AlignVCenter);
    itemTabla->setData(Qt::UserRole, "Header");
    itemTabla->setBackground(headerBrush);
    itemTabla->setFlags(Qt::ItemFlag::ItemIsEnabled);
    ui->TWtablaPuntajes->setItem(0, 1, itemTabla);
    //agrego los items

    for (int i=0; i<cantidadPuntajes; i++) {
        punt = parser.getPuntaje(cancion, i);
        if (punt.puntaje >= 0) {
            itemTabla = new QTableWidgetItem(parser.getNombrePuntaje(punt));
            itemTabla->setData(Qt::UserRole, cancion);
            itemTabla->setFlags(Qt::ItemFlag::ItemIsEnabled);
            itemTabla->setTextAlignment(Qt::AlignHCenter + Qt::AlignVCenter);
            ui->TWtablaPuntajes->setItem(i + 1, 0, itemTabla);
            itemTabla = new QTableWidgetItem(QString::number(parser.getValorPuntaje(punt)) + "\t");
            itemTabla->setTextAlignment(Qt::AlignRight + Qt::AlignVCenter);
            itemTabla->setData(Qt::UserRole, cancion);
            itemTabla->setData(Qt::UserRole + 1, parser.getValorPuntaje(punt));
            itemTabla->setFlags(Qt::ItemFlag::ItemIsEnabled);
            ui->TWtablaPuntajes->setItem(i + 1, 1, itemTabla);
        }
    }

    ui->TWtablaPuntajes->resizeRowsToContents();
    ui->TWtablaPuntajes->resizeColumnToContents(0);
    ui->TWtablaPuntajes->show();

}
