#include "parserpuntaje.h"

ParserPuntaje::ParserPuntaje()
{
    jDocPuntajes = nullptr;
    cargarDesdeArchivo();

}
ParserPuntaje::~ParserPuntaje() {
    delete jDocPuntajes;
}

/** 
 *  \fn         QStringList getCanciones()
 *  \details    Obtinene los puntajes del archivo json de canciones
 *  \param      void
 *  \return     QStringList Lista_de_canciones 
 */

QStringList ParserPuntaje::getCanciones() {
    QStringList listaCanciones;
    QJsonArray jArrayCanciones;
    QJsonObject jObjetoCancion;
    int cantCanciones = 0;

    listaCanciones.clear();
    jArrayCanciones = jDocPuntajes->array();
    cantCanciones = jArrayCanciones.size();
    for (int i=0; i < cantCanciones; i++) {
        jObjetoCancion = jArrayCanciones[i].toObject();
        if (jObjetoCancion.contains(STRING_KEY_NOMBRE_CANCION)) {
            if (jObjetoCancion[STRING_KEY_NOMBRE_CANCION].isString()) {
                listaCanciones.append(jObjetoCancion[STRING_KEY_NOMBRE_CANCION].toString());
            } else {
                listaCanciones.append("");
            }
        } else {
            listaCanciones.append("");
        }
    }

    return listaCanciones;
}

/** 
 *  \fn         int getCantidadPuntajes(QString cancion)
 *  \details    Obtiene la cantidad de puntajes para la cancion "cancion"
 *  \param      QString cancion
 *  \return     int cant_de_puntajes    -1: en caso de error
 */

int ParserPuntaje::getCantidadPuntajes(QString cancion) {
    QJsonArray jArrayCanciones;
    QJsonObject jObjetoCancion;

    jArrayCanciones = jDocPuntajes->array();
    for (int i=0; i < jArrayCanciones.size(); i++) {
        jObjetoCancion = jArrayCanciones[i].toObject();
        //busco la cancion y agrego el puntaje
        if (cancion == jObjetoCancion[STRING_KEY_NOMBRE_CANCION].toString()) {
            return jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES].toArray().size();
        }
    }
    return -1;
}

/** 
 *  \fn         puntaje getPuntaje(QString cancion, int indice)
 *  \details    Devuelve un struct puntaje con el puntaje para cierta cancion en determinado indice
 *  \param      QString cancion, int indice
 *  \return     struct puntaje      ""/-1 si hubo error
 */

puntaje ParserPuntaje::getPuntaje(QString cancion, int indice) {
    QJsonArray jArrayCanciones;
    QJsonArray jArrayPuntajes;
    QJsonObject jObjetoCancion;
    QJsonObject jObjetoPuntaje;
    puntaje retPuntaje;

    retPuntaje.iniciales = "";
    retPuntaje.puntaje = -1;

    jArrayCanciones = jDocPuntajes->array();
    for (int i=0; i < jArrayCanciones.size(); i++) {
        jObjetoCancion = jArrayCanciones[i].toObject();
        //busco la cancion y agrego el puntaje
        if (cancion == jObjetoCancion[STRING_KEY_NOMBRE_CANCION].toString()) {
            jArrayPuntajes = jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES].toArray();
            if (indice < jArrayPuntajes.size()) {
                jObjetoPuntaje = jArrayPuntajes.at(indice).toObject();
                retPuntaje.iniciales = jObjetoPuntaje[STRING_KEY_JUGADOR].toString();
                retPuntaje.iniciales.truncate(CARACT_MAX_PUNT_TABLA);
                retPuntaje.iniciales = retPuntaje.iniciales.toUpper();
                retPuntaje.puntaje = jObjetoPuntaje[STRING_KEY_PUNTAJE_JUGADOR].toInt();
            }
        }
    }
    return retPuntaje;
}

/** 
 *  \fn         void cargarDesdeArchivo()
 *  \details    Funcion utilitaria que se encarga de cargar un archivo
				o crear un documento vacio
 *  \param      void
 *  \return     void 
 */

void ParserPuntaje::cargarDesdeArchivo() {
    QByteArray rawTextData;
    QJsonDocument jDoc;
    QFile arch(STRING_ARCHIVO_NOMBRE);
    //qDebug() << QDir::current();

    if (jDocPuntajes != nullptr) delete jDocPuntajes;

    if(arch.exists()) {
        qDebug()<<"Archivo de puntajes encontrado";
        if (arch.open(QIODevice::ReadOnly)) {
            qDebug()<<"Archivo de puntajes abierto";
            rawTextData = arch.readAll();
            arch.close();
            jDoc = QJsonDocument::fromJson(rawTextData);
            if (verificarDocumentoJson(jDoc)) {
                jDocPuntajes = new QJsonDocument(jDoc);
            } else {
                jDoc.setArray(QJsonArray());
                jDocPuntajes = new QJsonDocument(jDoc);
            }
        } else {
            qDebug()<<"ERROR al abrir archivo de puntajes";
            jDoc.setArray(QJsonArray());
            jDocPuntajes = new QJsonDocument(jDoc);
        }
    } else {
        //si no hay archivo, creo un array vacío y lo pongo de base para el
        //document
        qDebug()<<"Archivo de puntajes NO encontrado";
        jDoc.setArray(QJsonArray());
        jDocPuntajes = new QJsonDocument(jDoc);
    }
    ordenarCancionesYPuntajes(*jDocPuntajes, true);
}

/** 
 *  \fn         int guardarPuntajes()
 *  \details    Interfaz publica para la funcion guardarArchivo();
 *  \param      void
 *  \return     0: salio todo bien		-1:no se pudo guardar el archivo
 */

int ParserPuntaje::guardarPuntajes() {
    return guardarArchivo();
}

/** 
 *  \fn         int guardarArchivo()
 *  \details    Guarda el archivo de puntajes;
 *  \param      void
 *  \return     0: salio todo bien		-1: no se pudo guardar el archivo
 */

int ParserPuntaje::guardarArchivo() {
    QFile aux(STRING_ARCHIVO_NOMBRE);
    QTextStream writeData;
    if (aux.open(QIODevice::WriteOnly)) {
        writeData.setDevice(&aux);
        writeData << jDocPuntajes->toJson();
        aux.close();
    } else {
        return -1;
    }
    return 0;
}

/** 
 *  \fn         int agregarCancion(QString cancion)
 *  \details    Agrega una cancion a la lista de puntajes
 *  \param      void
 *  \return     0: se agrego la cancion		-1: la cancion ya existe
 */

int ParserPuntaje::agregarCancion(QString cancion) {
    QJsonArray jArrayCanciones;
    QJsonObject jObjetoCancion;
	
	jArrayCanciones = jDocPuntajes->array();
	for (int i=0; i < jArrayCanciones.size(); i++) {
		jObjetoCancion = jArrayCanciones[i].toObject();
		//si ya existe el nombre de la cancion tiro error
		if (cancion == jObjetoCancion[STRING_KEY_NOMBRE_CANCION].toString()) return -1;
	}
	jObjetoCancion.insert(STRING_KEY_NOMBRE_CANCION, cancion);
	jObjetoCancion.insert(STRING_KEY_ARRAY_PUNTAJES, QJsonArray());
	jArrayCanciones.append(jObjetoCancion);
	jDocPuntajes->setArray(jArrayCanciones);
	ordenarCancionesYPuntajes(*jDocPuntajes);

    return 0;
}

/** 
 *  \fn         void borrarCancion(QString cancion)
 *  \details    Borra una cancion de la lista de puntajes
 *  \param      QString nombre_de_cancion
 *  \return     void
 */

void ParserPuntaje::borrarCancion(QString cancion) {
    QJsonArray jArrayCanciones;
    QJsonObject jObjetoCancion;

    
	jArrayCanciones = jDocPuntajes->array();
	for (int i=0; i < jArrayCanciones.size(); i++) {
		jObjetoCancion = jArrayCanciones[i].toObject();
		//si existe la saco con take y seteo el nuevo array
		if (cancion == jObjetoCancion[STRING_KEY_NOMBRE_CANCION].toString()) {
			jArrayCanciones.takeAt(i);
			jDocPuntajes->setArray(jArrayCanciones);
		}
	}
}

/**
 *  \fn         void agregarPuntaje(QString cancion, puntaje & punt)
 *  \details    Agrega un puntaje a una cancion determinada
 *  \param      QString nombre_de_cancion, puntaje & struct_de_puntaje
 *  \return     0: se agrego el puntaje     -1: hubo error (no existe la cancion, por ejemplo)
 */

int ParserPuntaje::agregarPuntaje(QString cancion, puntaje & punt) {
    QJsonArray jArrayCanciones;
    QJsonArray jArrayPuntajes;
    QJsonObject jObjetoCancion;
    QJsonObject jObjetoPuntaje;

    punt.iniciales = punt.iniciales.toUpper();
    punt.iniciales.truncate(CARACT_MAX_PUNT_TABLA);
    jObjetoPuntaje.insert(STRING_KEY_JUGADOR, punt.iniciales);
    jObjetoPuntaje.insert(STRING_KEY_PUNTAJE_JUGADOR, punt.puntaje);

    jArrayCanciones = jDocPuntajes->array();
    for (int i=0; i < jArrayCanciones.size(); i++) {
        jObjetoCancion = jArrayCanciones[i].toObject();
        //busco la cancion y agrego el puntaje
        if (cancion == jObjetoCancion[STRING_KEY_NOMBRE_CANCION].toString()) {
            jArrayPuntajes = jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES].toArray();
            jArrayPuntajes.append(jObjetoPuntaje);
            jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES] = jArrayPuntajes;
            jArrayCanciones[i] = jObjetoCancion;

            jDocPuntajes->setArray(jArrayCanciones);
            return 0;
        }
    }

    return -1;
}

/**
 *  \fn         void borrarPuntaje(QString cancion, puntaje & punt)
 *  \details    Borra un puntaje de la lista de puntajes
 *  \param      QString nombre_de_cancion, puntaje & puntaje_a_borrar
 *  \return     void
 */

void ParserPuntaje::borrarPuntaje(QString cancion, puntaje & punt) {
    QJsonArray jArrayCanciones;
    QJsonArray jArrayPuntajes;
    QJsonObject jObjetoCancion;
    QJsonObject jObjetoPuntaje;

    punt.iniciales = punt.iniciales.toUpper();
    punt.iniciales.truncate(CARACT_MAX_PUNT_TABLA);
    jObjetoPuntaje.insert(STRING_KEY_JUGADOR, punt.iniciales);
    jObjetoPuntaje.insert(STRING_KEY_PUNTAJE_JUGADOR, punt.puntaje);

    jArrayCanciones = jDocPuntajes->array();
    for (int i=0; i < jArrayCanciones.size(); i++) {
        jObjetoCancion = jArrayCanciones[i].toObject();
        //busco la cancion y agrego el puntaje
        if (cancion == jObjetoCancion[STRING_KEY_NOMBRE_CANCION].toString()) {
            jArrayPuntajes = jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES].toArray();
            for (int j=0; j < jArrayPuntajes.size(); j++) {
                if (jArrayPuntajes[j].toObject() == jObjetoPuntaje) {
                    jArrayPuntajes.takeAt(j);
                    jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES] = jArrayPuntajes;
                    jArrayCanciones[i] = jObjetoCancion;
                    jDocPuntajes->setArray(jArrayCanciones);
                    ordenarCancionesYPuntajes(*jDocPuntajes, true);
                }
            }
        }
    }
}

/**
 *  \fn         void limpiarPuntajes(QString cancion)
 *  \details    Limpia los puntajes de unas determinada cancion
 *  \param      QString nombre_de_cancion
 *  \return     void
 */

void ParserPuntaje::limpiarPuntajes(QString cancion) {
    int cantPuntajes = getCantidadPuntajes(cancion);
    puntaje punt;
    for (int i=0; i < cantPuntajes; i++) {
        //como uso takeat, los puntajes se manejan con una
        //lista, y al remover un item se cambian los indices
        //automaticamente
        punt = getPuntaje(cancion, 0);
        borrarPuntaje(cancion, punt);
    }
}

/**
 *  \fn         void getNombrePuntaje(puntaje & punt)
 *  \details    Devuelve el nombre (las iniciales) de un struct puntaje
 *  \param      puntaje & puntaje_jugador
 *  \return     QString iniciales
 */

QString ParserPuntaje::getNombrePuntaje(puntaje & punt) {
    return punt.iniciales;
}

/**
 *  \fn         int getValorPuntaje(puntaje & punt)
 *  \details    Devuelve los puntos de un determinado puntaje
 *  \param      puntaje & puntaje_jugador
 *  \return     int valor_punt
 */

int ParserPuntaje::getValorPuntaje(puntaje & punt) {
    return punt.puntaje;
}

/**
 *  \fn         bool verificarDocumentoJson(QJsonDocument & jDoc)
 *  \details    Verifica que el docuemnto abierto del archivo sea valido.
 *              Valida todas las estructuras
 *  \param      QJsonDocument & jDoc
 *  \return     bool verificado
 */

bool ParserPuntaje::verificarDocumentoJson(QJsonDocument & jDoc) {
    //se encarga de verificar la estructura del json cargado
    bool archValido = false;
    QJsonArray jArrayCanciones;
    QJsonArray jArrayPuntajes;
    QJsonObject jObjetoCancion;
    QJsonObject jObjetoPuntaje;

    if(!jDoc.isNull() && jDoc.isArray()) {
        jArrayCanciones = jDoc.array();
        if (jArrayCanciones.size() != 0) {
            for (int i=0; i < jArrayCanciones.size(); i++) {
                jObjetoCancion = jArrayCanciones[i].toObject();
                if (jObjetoCancion.contains(STRING_KEY_NOMBRE_CANCION) && jObjetoCancion[STRING_KEY_NOMBRE_CANCION].isString()) {
                    if (jObjetoCancion.contains(STRING_KEY_ARRAY_PUNTAJES) && jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES].isArray()) {
                        jArrayPuntajes = jObjetoCancion[STRING_KEY_ARRAY_PUNTAJES].toArray();
                        if (jArrayPuntajes.size() != 0) {
                            for (int j=0; j < jArrayPuntajes.size(); j++) {
                                jObjetoPuntaje = jArrayPuntajes[j].toObject();
                                if(jObjetoPuntaje.contains(STRING_KEY_JUGADOR) && jObjetoPuntaje[STRING_KEY_JUGADOR].isString()) {
                                    if (jObjetoPuntaje.contains(STRING_KEY_PUNTAJE_JUGADOR) && jObjetoPuntaje[STRING_KEY_PUNTAJE_JUGADOR].isDouble()) {
                                        //Si todo esta bien
                                        archValido = true;
                                    } else {
                                        //si el objeto puntajes no tiene la key de puntaje
                                        //o no tiene un valor numerico (Qt lo toma como
                                        //double en JSON)
                                        archValido = false;
                                    }
                                } else {
                                    //Si el objeto puntajes no tiene la key de jugador
                                    //o el nombre no es una string
                                    archValido = false;
                                }
                            }
                        } else {
                            //El array de puntajes esta vacio pero el resto
                            //de la estructura esta bien
                            archValido = true;
                        }
                    } else {
                        //El objeto cancion no tiene la key de puntajes
                        //o no es un array
                        archValido = false;
                    }
                } else {
                    //El objeto cancion no tiene la key con el nombre de la
                    //cancion o no es una string
                    archValido = false;
                }
            }
        } else {
            //El documento tiene el array de puntajes
            //vacio, pero arranca con un array
            //asi que tiene la estructura que aceptamos
            archValido = true;
        }
    }
    //si sale del if inmediatamente, quiere decir que el documento no arrancaba con un array
    //o hubo un error y es nulo (invalido)
    return archValido;
}

/**
 *  \fn         void ordenarCancionesYPuntajes(QJsonDocument & jDoc, bool tambienPuntajes)
 *  \details    Ordena las canciones por orden alfabético y los puntajes por valor
 *  \param      QJsonDocument & documento, bool tambien_ordenar_puntajes
 *  \return     void
 */

void ParserPuntaje::ordenarCancionesYPuntajes(QJsonDocument & jDoc, bool tambienPuntajes) {
    QJsonArray jArrayCanciones, jArrayPuntajes;
    QJsonObject a, b;
    if (!jDoc.isNull() && jDoc.isArray()) {
    jArrayCanciones = jDoc.array();
        if (!jArrayCanciones.isEmpty()) {
            for (int i=0; i < jArrayCanciones.size() - 1; i++) {
                for (int j=i; j < jArrayCanciones.size(); j++) {
                    a = jArrayCanciones[i].toObject();
                    b = jArrayCanciones[j].toObject();
                    if (a[STRING_KEY_NOMBRE_CANCION].toString() > b[STRING_KEY_NOMBRE_CANCION].toString()) {
                        jArrayCanciones[i] = b;
                        jArrayCanciones[j] = a;
                    }
                }
                if (tambienPuntajes) {
                    a = jArrayCanciones[i].toObject();
                    jArrayPuntajes = a[STRING_KEY_ARRAY_PUNTAJES].toArray();
                    if (!jArrayPuntajes.isEmpty()) {
                        ordenarPuntajes(jArrayPuntajes);
                    }
                    a[STRING_KEY_ARRAY_PUNTAJES] = jArrayPuntajes;
                    jArrayCanciones[i] = a;
                }
            }
            jDoc.setArray(jArrayCanciones);
        }
    }
}

/**
 *  \fn         void ordenarPuntajes(QJsonArray & jArrayPuntajes)
 *  \details    Ordena los "puntajes" dentro del array JSON de puntajes
 *  \param      QJsonArray & JSON_array_puntajes
 *  \return     void
 */

void ParserPuntaje::ordenarPuntajes(QJsonArray & jArrayPuntajes) {
    QJsonObject a, b;
    if (jArrayPuntajes.size() != 0) {
        for (int i=0; i < jArrayPuntajes.size() - 1; i++) {
            for (int j=i; j < jArrayPuntajes.size(); j++) {
                a = jArrayPuntajes[i].toObject();
                b = jArrayPuntajes[j].toObject();
                if (a[STRING_KEY_PUNTAJE_JUGADOR].toInt() < b[STRING_KEY_PUNTAJE_JUGADOR].toInt()) {
                    jArrayPuntajes[i] = b;
                    jArrayPuntajes[j] = a;
                }
            }
        }
    }
}
