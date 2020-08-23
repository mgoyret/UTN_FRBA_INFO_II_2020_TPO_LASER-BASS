/********************************************************************************
** Form generated from reading UI file 'menujugar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUJUGAR_H
#define UI_MENUJUGAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_MenuJugar
{
public:

    void setupUi(QDialog *MenuJugar)
    {
        if (MenuJugar->objectName().isEmpty())
            MenuJugar->setObjectName(QString::fromUtf8("MenuJugar"));
        MenuJugar->resize(400, 300);

        retranslateUi(MenuJugar);

        QMetaObject::connectSlotsByName(MenuJugar);
    } // setupUi

    void retranslateUi(QDialog *MenuJugar)
    {
        MenuJugar->setWindowTitle(QApplication::translate("MenuJugar", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuJugar: public Ui_MenuJugar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUJUGAR_H
