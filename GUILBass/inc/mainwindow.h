#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <clasemidi.h>

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

    void on_PBActualizar_clicked();

    void on_PBConectar_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *puerto;
    ClaseMIDI *puertoMidi;
    void enumerarPuertos();
};
#endif // MAINWINDOW_H
