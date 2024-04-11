#ifndef ILC_H
#define ILC_H

#include <QMainWindow>
#include <QSqlDatabase>

#include "amainwindow.h"

namespace Ui {
class ILC;
}

class ILC : public AMainWindow
{
    Q_OBJECT
public:
    explicit ILC(QWidget *parent = nullptr);
    ~ILC();

    void func();

private:
    Ui::AMainWindow *ui_amw;
    Ui::ILC         *ui_ilc;

    QMetaObject::Connection conn; // Обязательно делаем приватным!

    QSqlDatabase db; // Обязательно обьявляем в *.h файле.

    // QMetaObject::Connection conn_one; // Обязательно делаем приватным!
    QMetaObject::Connection conn_close; // Обязательно делаем приватным!

    QMetaObject::Connection conn_packet;
    QMetaObject::Connection conn_cgramm;
    QMetaObject::Connection conn_run;
    QMetaObject::Connection conn_drun;
    QMetaObject::Connection conn_stat;
};

#endif // ILC_H
