#ifndef DIALOGPUNTAJES_H
#define DIALOGPUNTAJES_H

#include <QDialog>
#include <parserpuntaje.h>
#include <QMessageBox>

#define PUNTAJE_BAJO    (puntos>0)&&(puntos<100)
#define PUNTAJE_MEDIO   (puntos>=100)&&(puntos<200)
#define PUNTAJE_ALTO    (puntos>=200)

namespace Ui {
class DialogPuntajes;
}

class DialogPuntajes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPuntajes(QWidget *parent = nullptr, int puntos = 0);
    ~DialogPuntajes();

    inline QString getName( void ){return nombre;}

private slots:
    void on_PBok_clicked();

private:
    Ui::DialogPuntajes *ui;
    QString nombre;
};

#endif // DIALOGPUNTAJES_H
