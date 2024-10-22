/*
 *
 * En este parser se trabaja con una estructura JSon encargada de mantener las canciones y los puntajes
 * La estructura es la siguiente
 * [
 *   {
 *     "cancion":"nombre de la cancion",
 *     "puntajes":[
 *                  {
 *                    "jugador":"iniciales del jugador",
 *                    "puntaje":123
 *                  }
 *                  ...
 *                ]
 *   }
 *   ...
 * ]
 *
 * Hay un ARRAY principal que contiene a los OBJETOS cancion. Los OBJETOS
 * cancion contienen el nombre de la cancion en "cancion", y los puntajes
 * en un ARRAY bajo la key "puntajes". El ARRAY puntajes tiene a su vez
 * OBJETOS puntaje, los cuales se componen de una key "jugador" con las
 * iniciales del jugador y una key "puntaje" con el valor del puntaje
 *
 *
 *
 *
 */
#ifndef PARSERPUNTAJE_H
#define PARSERPUNTAJE_H

#include <QFile>
#include <QDir>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <string.h>
#include <QTextStream>

#define STRING_KEY_NOMBRE_CANCION "cancion"
#define STRING_KEY_ARRAY_PUNTAJES "puntajes"
#define STRING_KEY_JUGADOR "jugador"
#define STRING_KEY_PUNTAJE_JUGADOR "puntaje"
#define STRING_ARCHIVO_NOMBRE "../puntajes/archivoPuntajes.tema"
#define CARACT_MAX_PUNT_TABLA 5

typedef struct {
    QString iniciales;
    int puntaje;
} puntaje;

class ParserPuntaje
{
public:
    ParserPuntaje();
    ~ParserPuntaje();

    int guardarPuntajes();

    QStringList getCanciones();
    int getCantidadPuntajes(QString cancion);
    puntaje getPuntaje(QString cancion, int indice);

    int agregarCancion(QString cancion);
    void borrarCancion(QString cancion);
    int agregarPuntaje(QString cancion, puntaje & punt);
    void borrarPuntaje(QString cancion, puntaje & punt);
    void limpiarPuntajes(QString cancion);

    QString getNombrePuntaje(puntaje & punt);
    int getValorPuntaje(puntaje & punt);


private:
    QJsonDocument * jDocPuntajes;
    bool verificarDocumentoJson(QJsonDocument & jDoc);
    void ordenarCancionesYPuntajes(QJsonDocument & jDoc, bool tambienPuntajes = false);
    void ordenarPuntajes(QJsonArray & jArrayPuntajes);
    void cargarDesdeArchivo();
    int guardarArchivo();

};

#endif // PARSERPUNTAJE_H
