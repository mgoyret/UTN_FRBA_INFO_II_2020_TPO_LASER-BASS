#ifndef TOCAR_H
#define TOCAR_H

#include <QDialog>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
namespace Ui {
class Tocar;
}

class Tocar : public QDialog
{
    Q_OBJECT

public:
    explicit Tocar(QWidget *parent = nullptr);
    ~Tocar();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::Tocar *ui;
    QSerialPort puerto;
};

#endif // TOCAR_H
