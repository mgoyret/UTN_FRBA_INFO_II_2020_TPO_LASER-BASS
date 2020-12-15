#ifndef DIALOGBORRAR_H
#define DIALOGBORRAR_H

#include <QDialog>
#include <parserpuntaje.h>

#define SONG_FOLDER_PATH    "../media/"
#define SONG_FILE_TYPE      ".csv"


namespace Ui {
class DialogBorrar;
}

class DialogBorrar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBorrar(QWidget *parent = nullptr);
    ~DialogBorrar();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DialogBorrar *ui;
    ParserPuntaje parser;

};

#endif // DIALOGBORRAR_H
