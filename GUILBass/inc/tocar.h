#ifndef TOCAR_H
#define TOCAR_H

#include <QDialog>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#define ON 1
#define OFF 0
namespace Ui {
class Tocar;
}

class Tocar : public QDialog
{
    Q_OBJECT

public:
    explicit Tocar(QWidget *parent = nullptr);
    ~Tocar();
    void setPuerto(QString name);

private slots:
    void on_datosRecibidos();

private:
    Ui::Tocar *ui;
    QSerialPort puerto;
    void setColor(const char * estado);
};

#endif // TOCAR_H
