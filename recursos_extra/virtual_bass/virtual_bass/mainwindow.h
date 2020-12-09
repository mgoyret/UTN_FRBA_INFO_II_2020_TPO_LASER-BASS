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

typedef enum noteOffEnum{
    NOTA28 = -28,
    NOTA27 = -27,
    NOTA26,
    NOTA25,
    NOTA24,
    NOTA23,
    NOTA22,
    NOTA21,
    NOTA20,
    NOTA19,
    NOTA18,
    NOTA17,
    NOTA16,
    NOTA15,
    NOTA14,
    NOTA13,
    NOTA12,
    NOTA11,
    NOTA10,
    NOTA9,
    NOTA8,
    NOTA7,
    NOTA6,
    NOTA5,
    NOTA4,
    NOTA3,
    NOTA2,
    NOTA1,
}noteOffEnum;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void enviarNota(uint8_t nota); //desde la nota 16, se envia big=1 para que ponga data1=1
    void noteOn(uint8_t nota);
    void noteOff(uint8_t nota);
    void append_send();
    void debug(QByteArray datos);

private slots:

    void on_ActualizarButton_clicked();
    void on_conectarButton_clicked();
    //void on_datosRecibidos(); //no voy a recibir nada por puerto serie

    //BOTONES
    void on_note_1_clicked();
    void on_note_2_clicked();
    void on_note_3_clicked();
    void on_note_4_clicked();
    void on_note_5_clicked();
    void on_note_6_clicked();
    void on_note_7_clicked();
    void on_note_8_clicked();
    void on_note_9_clicked();
    void on_note_10_clicked();
    void on_note_11_clicked();
    void on_note_12_clicked();
    void on_note_13_clicked();
    void on_note_14_clicked();
    void on_note_15_clicked();
    void on_note_16_clicked();
    void on_note_17_clicked();
    void on_note_18_clicked();
    void on_note_19_clicked();
    void on_note_20_clicked();
    void on_note_21_clicked();
    void on_note_22_clicked();
    void on_note_23_clicked();
    void on_note_24_clicked();
    void on_note_25_clicked();
    void on_note_26_clicked();
    void on_note_27_clicked();
    void on_note_28_clicked();

    // NOTEOFF
    void timer_handler_1();
    void timer_handler_2();
    void timer_handler_3();
    void timer_handler_4();
    void timer_handler_5();
    void timer_handler_6();
    void timer_handler_7();
    void timer_handler_8();
    void timer_handler_9();
    void timer_handler_10();
    void timer_handler_11();
    void timer_handler_12();
    void timer_handler_13();
    void timer_handler_14();
    void timer_handler_15();
    void timer_handler_16();
    void timer_handler_17();
    void timer_handler_18();
    void timer_handler_19();
    void timer_handler_20();
    void timer_handler_21();
    void timer_handler_22();
    void timer_handler_23();
    void timer_handler_24();
    void timer_handler_25();
    void timer_handler_26();
    void timer_handler_27();
    void timer_handler_28();



private:
    Ui::MainWindow *ui;
    void enumerarPuertos();
    QSerialPort puerto; //lo abro, cierro, leo y escribo
    QByteArray datos;
    char data1, data2;
};
#endif // MAINWINDOW_H
