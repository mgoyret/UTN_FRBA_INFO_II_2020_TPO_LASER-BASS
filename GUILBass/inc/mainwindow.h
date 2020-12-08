#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QColorDialog>
#include <clasemidi.h>
#include <dialogpreferencias.h>
#include "../inc/tocar.h"
#include "../inc/menujugar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void cerrarPuerto();
private slots:
    void on_PBJugar_clicked();

    void on_PBTocar_clicked();

    void on_actionPreferencias_triggered();

private:
    Ui::MainWindow *ui;
    QSerialPort *puerto;
    ClaseMIDI *puertoMidi;
    void configurarPuertoSerie(QString portName);
    void configurarPuertoMidi(QString portName);
    bool verificarConfiguracionPuertos();
};
#endif // MAINWINDOW_H
