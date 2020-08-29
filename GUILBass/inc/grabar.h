#ifndef GRABAR_H
#define GRABAR_H

#include <QDialog>

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

#endif // GRABAR_H
