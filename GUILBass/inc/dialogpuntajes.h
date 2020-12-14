#ifndef DIALOGPUNTAJES_H
#define DIALOGPUNTAJES_H

#include <QDialog>
#include <parserpuntaje.h>
#include <QMessageBox>
namespace Ui {
class DialogPuntajes;
}

class DialogPuntajes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPuntajes(QWidget *parent = nullptr, int puntos=0, int puntosMax=0);
    ~DialogPuntajes();

    inline QString getName( void ){return nombre;}

private slots:
    void on_PBok_clicked();

    void on_PBdescartar_clicked();

private:
    Ui::DialogPuntajes *ui;
    QString nombre;
};

#endif // DIALOGPUNTAJES_H
