#ifndef WINDOWPUNTAJES_H
#define WINDOWPUNTAJES_H

#include <QWidget>

namespace Ui {
class WindowPuntajes;
}

class WindowPuntajes : public QWidget
{
    Q_OBJECT

public:
    explicit WindowPuntajes(QWidget *parent = nullptr);
    ~WindowPuntajes();

private:
    Ui::WindowPuntajes *ui;
};

#endif // WINDOWPUNTAJES_H
