#ifndef MENUJUGAR_H
#define MENUJUGAR_H

#include <grabar.h>
#include <jugar.h>

#include <QDialog>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "grabar.h"
#include "jugar.h"
#include "tablapuntajes.h"

namespace Ui {
class MenuJugar;
}

class MenuJugar : public QDialog
{
    Q_OBJECT

public:
    explicit MenuJugar(QWidget *parent = nullptr);
    ~MenuJugar();

    void setPuerto(QSerialPort*);

private slots:
    void on_PBpreGrabada_clicked();

    void on_PBgrabarNueva_clicked();

    void on_PBpuntajes_clicked();

private:
    Ui::MenuJugar *ui;
    QSerialPort *puerto;
};

#endif // MENUJUGAR_H
