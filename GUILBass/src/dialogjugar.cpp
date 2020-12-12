#include "dialogjugar.h"
#include "ui_dialogjugar.h"

DialogJugar::DialogJugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogJugar)
{
    ui->setupUi(this);
    ui->CBcanciones->clear();
    nombreCancion = "";

    ParserPuntaje pp;
    QStringList lista = QDir("../media").entryList();
    QStringList listaCancionesGuardadas = pp.getCanciones();


    //primero, elimino de la lista de nombres de archivos
    //los que no sean .csv, y remuevo la extensión
    //hay que recorrer la lista al reves porque al usar
    //el remove se me alteran las posiciones. arrancando
    //al final y restando verifico y remuevo de atras para
    //adelante y entonces no hago overflow ni nada de eso

    for (int i=lista.size()-1; i>=0; i--) {
        if (!lista.at(i).contains(".csv")) {
            lista.removeAt(i);
        } else {
            lista[i].remove(".csv");
        }
    }

    //Ahora recorro la lista de canciones guardadas y agrego
    //las que no estaban antes (esta el archivo pero no el
    //puntaje

    for (int i=0; i<lista.size(); i++) {
        if (!listaCancionesGuardadas.contains(lista.at(i))) {
            pp.agregarCancion(lista.at(i));
        }
        //aprovecho el loop para agregar las canciones a la
        //combobox
        ui->CBcanciones->addItem(lista.at(i));
    }

    //Y ahora borro las canciones que no esten en los archivos
    //es decir, que quiza se eliminaron y no tiene sentido
    //conservar el puntaje

    for (int i=0; i<listaCancionesGuardadas.size(); i++) {
        if (!lista.contains(listaCancionesGuardadas.at(i))) {
            pp.borrarCancion(listaCancionesGuardadas.at(i));
        }
    }

    //Por ultimo, guardo los cambios hechos en el archivo
    //de puntajes
    pp.guardarPuntajes();

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
