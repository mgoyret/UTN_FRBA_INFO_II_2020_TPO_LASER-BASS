#ifndef JUGAR_H
#define JUGAR_H

#include <QDialog>

namespace Ui {
class Jugar;
}

class Jugar : public QDialog
{
    Q_OBJECT

public:
    explicit Jugar(QWidget *parent = nullptr);
    ~Jugar();

private:
    Ui::Jugar *ui;
    //funcion para el line_edit Puntos
};

#endif // JUGAR_H
