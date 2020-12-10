#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>

#include <iostream>
#include <bitset>

#define DEBUG

#define BIG_BITS    0xF0    // 1111 0000
#define LOW_BITS    0x0F    // 0000 1111

#define INICIO_TRAMA    0xA0    // 1010 0000
#define FIN_TRAMA       0x05    // 0000 0101

#define TIMER_NOTE_OFF 500

typedef enum noteEnum{
    NOTA1 = 1,
    NOTA2,
    NOTA3,
    NOTA4,
    NOTA5,
    NOTA6,
    NOTA7,
    NOTA8,
    NOTA9,
    NOTA10,
    NOTA11,
    NOTA12,
    NOTA13,
    NOTA14,
    NOTA15,
    NOTA16,
    NOTA17,
    NOTA18,
    NOTA19,
    NOTA20,
    NOTA21,
    NOTA22,
    NOTA23,
    NOTA24,
    NOTA25,
    NOTA26,
    NOTA27,
    NOTA28,
}noteEnum;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void noteOn(char nota);
    void noteOff(char nota);
    void append_send();
    void debug(QByteArray datos);

private slots:

    void on_ActualizarButton_clicked();
    void on_conectarButton_clicked();
    //void on_datosRecibidos(); //no voy a recibir nada por puerto serie

    void on_note_1_pressed();
    void on_note_2_pressed();
    void on_note_3_pressed();
    void on_note_4_pressed();
    void on_note_5_pressed();
    void on_note_6_pressed();
    void on_note_7_pressed();
    void on_note_8_pressed();
    void on_note_9_pressed();
    void on_note_10_pressed();
    void on_note_11_pressed();
    void on_note_12_pressed();
    void on_note_13_pressed();
    void on_note_14_pressed();
    void on_note_15_pressed();
    void on_note_16_pressed();
    void on_note_17_pressed();
    void on_note_18_pressed();
    void on_note_19_pressed();
    void on_note_20_pressed();
    void on_note_21_pressed();
    void on_note_22_pressed();
    void on_note_23_pressed();
    void on_note_24_pressed();
    void on_note_25_pressed();
    void on_note_26_pressed();
    void on_note_27_pressed();
    void on_note_28_pressed();

    void on_note_1_released();
    void on_note_2_released();
    void on_note_3_released();
    void on_note_4_released();
    void on_note_5_released();
    void on_note_6_released();
    void on_note_7_released();
    void on_note_8_released();
    void on_note_9_released();
    void on_note_10_released();
    void on_note_11_released();
    void on_note_12_released();
    void on_note_13_released();
    void on_note_14_released();
    void on_note_15_released();
    void on_note_16_released();
    void on_note_17_released();
    void on_note_18_released();
    void on_note_19_released();
    void on_note_20_released();
    void on_note_21_released();
    void on_note_22_released();
    void on_note_23_released();
    void on_note_24_released();
    void on_note_25_released();
    void on_note_26_released();
    void on_note_27_released();
    void on_note_28_released();

private:
    Ui::MainWindow *ui;
    void enumerarPuertos();
    QSerialPort puerto; //lo abro, cierro, leo y escribo
    QByteArray datos;
    char data1, data2;
};
#endif // MAINWINDOW_H
