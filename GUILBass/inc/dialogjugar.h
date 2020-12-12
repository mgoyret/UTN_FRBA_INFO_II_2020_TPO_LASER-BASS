#ifndef DIALOGJUGAR_H
#define DIALOGJUGAR_H

#include <QDialog>
#include <QDir>
#include <QDebug>
#include "parserpuntaje.h"

namespace Ui {
class DialogJugar;
}

class DialogJugar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogJugar(QWidget *parent = nullptr);
    ~DialogJugar();

    inline QString getNombreCancion( void ) { return nombreCancion; }

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogJugar *ui;
    QString nombreCancion;
};

#endif // DIALOGJUGAR_H
