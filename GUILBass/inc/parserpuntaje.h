#ifndef PARSERPUNTAJE_H
#define PARSERPUNTAJE_H

#include <QFile>
#include <QList>
#include <QStringList>
#include <QMessageBox>

typedef struct {
    char iniciales[3];
    int puntaje;
} puntaje;

class ParserPuntaje
{
public:
    ParserPuntaje();
    QStringList getCanciones();
    int getCantidadPuntajes(QString &);
    puntaje getPuntaje(QString &, int);
    int cargarDesdeArchivo(QFile &);
    int agregarPuntaje(QString cancion, puntaje &);
    int borrarPuntaje(QString cancion, puntaje &);
    void limpiarPuntajes();

    QString getNombrePuntaje(puntaje &);
    int getValorPuntaje(puntaje &);

private:
    QList<puntaje> *listaPuntajes;
};

#endif // PARSERPUNTAJE_H
