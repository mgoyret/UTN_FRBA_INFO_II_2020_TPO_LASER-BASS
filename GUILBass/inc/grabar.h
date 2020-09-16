#ifndef GRABAR_H
#define GRABAR_H

#include <QDialog>
#include "../inc/mde_grabacion/AP_MdeE.h"
#include "../inc/mde_grabacion/AP_FuncionesMdeE.h"

namespace Ui {
class Grabar;
}

class Grabar : public QDialog
{
    Q_OBJECT

public:
    explicit Grabar(QWidget *parent = nullptr);
    ~Grabar();

private slots:
    void on_PBrec_clicked();

    void on_PBfinRec_clicked();

private:
    Ui::Grabar *ui;
};


void crearArchivo(FILE*);


#endif // GRABAR_H
