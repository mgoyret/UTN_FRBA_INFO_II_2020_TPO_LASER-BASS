#ifndef DIALOGJUGAR_H
#define DIALOGJUGAR_H

#include <QDialog>
#include <parserpuntaje.h>
namespace Ui {
class DialogJugar;
}

class DialogJugar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogJugar(QWidget *parent = nullptr);
    ~DialogJugar();
    QString getNombreCancion(void);

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    ParserPuntaje parser;
    QString cancion;
    Ui::DialogJugar *ui;
};

#endif // DIALOGJUGAR_H
