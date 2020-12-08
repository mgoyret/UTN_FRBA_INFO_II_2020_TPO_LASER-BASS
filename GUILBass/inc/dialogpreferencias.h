#ifndef DIALOGPREFERENCIAS_H
#define DIALOGPREFERENCIAS_H

#include <QDialog>
#include <QFile>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "clasemidi.h"

#define NOMBRE_ARCH_PREFS "prefs.ini"

namespace Ui {
class DialogPreferencias;
}

class DialogPreferencias : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPreferencias(QWidget *parent = nullptr);

    void getMainPrefsFromFile();
    QString getSerialPortPref();
    QString getMidiPortPref();

    ~DialogPreferencias();

private slots:
    void on_pushButtonMidi_clicked();

    void on_pushButtonSerie_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_comboBoxMidi_currentIndexChanged(int index);

    void on_comboBoxSerie_currentIndexChanged(int index);

private:
    Ui::DialogPreferencias *ui;
    QFile prefFile;
    QString prefNombrePuertoSerie;
    QString prefNombrePuertoMidi;
    QSerialPort puertoSerie;
    ClaseMIDI puertoMidi;

    void cargarPrefs();
    bool validarPuertoSerie(QString puerto);
    bool validarPuertoMidi(QString puerto);
};

#endif // DIALOGPREFERENCIAS_H
