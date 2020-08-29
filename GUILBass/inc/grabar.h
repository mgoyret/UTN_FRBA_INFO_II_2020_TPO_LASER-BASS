#ifndef GRABAR_H
#define GRABAR_H

#include <QDialog>

namespace Ui {
class grabar;
}

class grabar : public QDialog
{
    Q_OBJECT

public:
    explicit grabar(QWidget *parent = nullptr);
    ~grabar();

private:
    Ui::grabar *ui;
};

#endif // GRABAR_H
