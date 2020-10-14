#ifndef MENUJUGAR_H
#define MENUJUGAR_H

#include <QDialog>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
namespace Ui {
class MenuJugar;
}

class MenuJugar : public QDialog
{
    Q_OBJECT

public:
    explicit MenuJugar(QWidget *parent = nullptr);
    ~MenuJugar();

    void set_nPuerto(QString name);

private slots:
    void on_PBpreGrabada_clicked();

    void on_PBgrabarNueva_clicked();


private:
    Ui::MenuJugar *ui;
    QString nPuerto;
};

#endif // MENUJUGAR_H
