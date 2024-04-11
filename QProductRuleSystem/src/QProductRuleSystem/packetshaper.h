#ifndef PACKETSHAPER_H
#define PACKETSHAPER_H

#include "ui_packetshaper.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QItemSelection>

#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QStandardItemModel>
#include <QBitArray>

namespace Ui {
class PacketShaper;
}

class PacketShaper : public QMainWindow
{
    Q_OBJECT
public:
    explicit PacketShaper(QSqlDatabase &, QWidget *parent = nullptr);
    ~PacketShaper();

public slots:
    void currentChangetView(const QModelIndex &current, const QModelIndex &previous){
        Q_UNUSED(current)
        Q_UNUSED(previous)

        qDebug() << current;

        qDebug() << previous;
    };

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
        Q_UNUSED(selected)
        Q_UNUSED(deselected)

        //qDebug() << selected;

        /*foreach(auto ix, selected.indexes())
            qDebug() << ix.row() << ix.column();

        //qDebug() << deselected;

        foreach(auto ix, deselected.indexes())
            qDebug() << ix.row() << ix.column();*/
    };

    void datachangetModel(const QModelIndex &topLeft, const QModelIndex &bottomRight){

        //// qDebug() << "datachangetModel";

        //static int  column = 0;

        //if(topLeft.column()==)

        ////qDebug() << topLeft << topLeft.row() << topLeft.column() << topLeft.data();

        ///qDebug() << bottomRight << bottomRight.data();
    }

    void selectionChangedDecView(const QItemSelection &selected, const QItemSelection &deselected){
        Q_UNUSED(selected)
        Q_UNUSED(deselected)

        /*foreach(auto ix, selected.indexes())
            qDebug() << ix.row() << ix.column();

        // qDebug() << deselected;

        foreach(auto ix, deselected.indexes())
            qDebug() << ix.row() << ix.column();*/

        // Проверк выполнения условий длям. перехвата:

        // lst [0]; - Запрос № 1;
        // lst [1] - текущее местоположение истребителя;
        // lst [2] - Тип системы наведения, установленный на истребителе;
        // lst [3:7:9] - параметры "Метод погони";
        // + lst[3] - Длина м. погони;
        // + lst[4] - Требование к начальному положению истребителя;
        // + lst[5] - Тип системы наведения;
        // + lst[6] - Необходимость наведения ;
        // + lst[7] - Скрытность;
        // + lst[8] - Реализуемость траектории;
        // + lst[9] - Требования к перегрузкам;
        // lst [10:7:16] - параметры "Метод маневра";
        // + lst[10] - Длина м. пманевра;
        // + lst[11] - Требование к начальному положению истребителя;
        // + lst[12] - Тип системы наведения;
        // + lst[13] - Необходимость наведения ;
        // + lst[14] - Скрытность;
        // + lst[15] - Реализуемость траектории;
        // + lst[16] - Требования к перегрузкам;
        // lst [17:7:23] - параметры "Метод перехвата";
        // + lst[17] - Длина м. перехвата;
        // + lst[18] - Требование к начальному положению истребителя;
        // + lst[19] - Тип системы наведения;
        // + lst[20] - Необходимость наведения ;
        // + lst[21] - Скрытность;
        // + lst[22] - Реализуемость траектории;
        // + lst[23] - Требования к перегрузкам;

        QList<QVariant> lst;
        foreach(auto ix, selected.indexes()) // Получение списка выделенной записи
            lst << model_workMemory->data(model_workMemory->index(ix.row(), ix.column())); // //func2(ix.row(), ix.column());
        qDebug() << lst;

        // lst_len[0] - len м. погони.
        // lst_len[1] - len м. маневра.
        // lst_len[2] - len м. перехвата.

        QList<int> lst_len;

        if(lst.isEmpty() || lst.count() < model_workMemory->rowCount()) return;

        for(int i = 0; i < 3; i++)
            lst_len << lst.at(3 + 7*i).toDouble();
        qDebug() << lst_len;

        double cond = lst_len.last();
        std::sort(lst_len.begin(), lst_len.end());

        // Если длина м. перехвата меньше длины других методов наведения,то выход.
        if(std::abs(cond - lst_len.first()) > 0.00001) {qDebug() << "";  return;}
        else if(lst_len[0] == lst_len[1] || lst_len[0] == lst_len[2] || lst_len[1]== lst_len[2]) {
            ui->line_rec->setText(" - ");
            ui->line_result->setText("Установите корректную длину траектории для методов наведения!"); return;
        }

        auto ff = [&](int row, int pos)-> bool {

            /*for(int j = 0; j < 7; j++)
                if( model_rule->data( // Абстрактная итерация
                    model_rule->index(i, j + 2)).toString().compare(lst[pos + j].toString()) != 0) return;*/

            if((model_rule->data( // Tекущее местонахождение истребителя по отношению к цели.
                              model_rule->index(row, 2)).toString().compare(lst[pos].toString()) != 0) &&
                (model_rule->data( // Tекущее местонахождение истребителя по отношению к цели.
                               model_rule->index(row, 2)).toString().compare(lst[1].toString()) != 0)
              ) return false;

            if((model_rule->data(  // Тип системы наведения ракет установленный на истребителе.
                              model_rule->index(row, 3)).toString().compare(lst[pos + 1].toString()) != 0) &&
                (model_rule->data(
                               model_rule->index(row, 3)).toString().compare("Радиолокационно-Оптический") != 0))  return false;

            if(model_rule->data( // Наведение в переднюю или заднюю полусферу.
                               model_rule->index(row, 4)).toString().compare(lst[pos + 2].toString()) != 0)  return false;

            if( model_rule->data( // Скрытность.
                              model_rule->index(row, 5)).toString().compare(lst[pos + 3].toString()) != 0)  return false;

            if( model_rule->data( // Реализуемость.
                              model_rule->index(row, 6)).toString().compare(lst[pos + 4].toString()) != 0)  return false;

            if( model_rule->data( // Перегрузки.
                              model_rule->index(row, 7)).toString().compare(lst[pos + 5].toString()) != 0)  return false;

            ui->line_result->setText(
                model_rule->data(
                              model_rule->index(row, model_rule->columnCount() - 1))
                    .toString());

            ui->line_rec->setText(
                model_rule->data(
                model_rule->index(row, 0))
                .toString());

            return true;
        };

        bool status = false;
        qDebug() << "rowC: " << model_rule->rowCount();

        for(int i = 0; i < model_rule->rowCount(); i++) // Получаем выводы (методы наведения)
            if( model_rule->data(
                model_rule->index(i, model_rule->columnCount() - 1))
                    .toString()
                    .compare("Метод перехвата") == 0){

                /*if( model_rule->data( // Tекущее местонахождение истребителя по отношению к цели.
                    model_rule->index(i, 2)).toString().compare(lst[18].toString()) != 0) continue;

                qDebug() << model_rule->data(
                            model_rule->index(i, 3)).toString().compare("Радиолокационно-Оптический");

                if( (model_rule->data(  // Тип системы наведения ракет установленный на истребителе.
                    model_rule->index(i, 3)).toString().compare(lst[19].toString()) != 0) &&
                    (model_rule->data(
                     model_rule->index(i, 3)).toString().compare("Радиолокационно-Оптический") != 0)) continue;

                if((model_rule->data( // Наведение в переднюю или заднюю полусферу.
                    model_rule->index(i, 4)).toString().compare(lst[20].toString()) != 0) ) continue;

                if( model_rule->data( // Скрытность.
                    model_rule->index(i, 5)).toString().compare(lst[21].toString()) != 0) continue;

                if( model_rule->data( // Реализуемость.
                    model_rule->index(i, 6)).toString().compare(lst[22].toString()) != 0) continue;

                if( model_rule->data( // Перегрузки.
                    model_rule->index(i, 7)).toString().compare(lst[23].toString()) != 0) continue;

                qDebug() << "Рекомендация м. Перехвата";

                ui->line_result->setText(
                    model_rule->data(
                    model_rule->index(i, model_rule->columnCount() - 1))
                        .toString());

                return; // Цикл по продукционным правилам прекращается! */

                if(ff(i, 18)) return;

            }else if(
                (model_rule->data( // м. погони.
                 model_rule->index(i, model_rule->columnCount() - 1))
                    .toString()
                    .compare("Метод погони") == 0) &&
                (lst_len[0] - lst_len[1]) < 0.00001){ // (lst_len[0] (Длина м. погони) - lst_len[1] (Длина м. маневра)) < 0.00001;

                if(ff(i, 4)) return;  // Цикл по продукционным правилам прекращается!
            } else if(
                (model_rule->data( // м. маневра.
                 model_rule->index(i, model_rule->columnCount() - 1))
                    .toString()
                    .compare("Метод маневра") == 0) &&
                       (lst_len[1] - lst_len[0]) < 0.00001) {

               if(ff(i, 11)) return;   // Цикл по продукционным правилам прекращается!
               else status = true; // пойдем на второй круг по м. погони
            }else if( // Если мы тут оказались, значит приоритет для м. погони выполнился, но не выполнились требования. Переходим к м. маневра с нимжим приоритетом.
                (model_rule->data( // м. маневра.
                 model_rule->index(i, model_rule->columnCount() - 1))
                    .toString()
                    .compare("Метод маневра") == 0) &&
                       (lst_len[0] - lst_len[1]) < 0.00001){

                if(ff(i, 11)) return;   // Цикл по продукционным правилам прекращается!
                else {ui->line_result->setText("Нет рекомендуемого метода наведения!"); ui->line_rec->setText(" - ");}
            }

        if(status) // Выполнился приоритет длины м. маневра, но раз мы тут оказались, значит не выполнились требования данного метода. Переходим к м. погони с нимжим приоритетом.
            for(int i = 1; i < model_rule->rowCount(); i++)
                if((model_rule->data( // м. погони.
                 model_rule->index(i, model_rule->columnCount() - 1))
                    .toString()
                    .compare("Метод погони") == 0) &&
                (lst_len[1] - lst_len[0]) < 0.00001){
                    // Идем на второй заход по м. погони.

                    if(ff(i, 4)) return;  // Цикл по продукционным правилам прекращается!
                    else {ui->line_result->setText("Нет рекомендуемого метода наведения!"); ui->line_rec->setText(" - ");}
                }
    };

    void datachangetModelDecView(const QModelIndex &topLeft, const QModelIndex &bottomRight){

        qDebug() << "datachangetModelDecView: " ;

        qDebug() << topLeft << topLeft.data();

        qDebug() << topLeft.row() << topLeft.column();
    }

private slots:
    void on_create_record_clicked();

    void on_toolButton_clicked();

    void on_delete_record_clicked();

    void on_clear_db_clicked();

private:
    Ui::PacketShaper *ui;

    QSqlDatabase &_db;

    QSqlRelationalTableModel *model_workMemory;

    QSqlRelationalTableModel *model_sutvec;

    // 0 - Продукционное правило № _.
    // 1 - Минимальная длина или невыполнение правил на приоритете выше.
    // 2 - текущее местонахождение истребителя по отношению к цели.
    // 3 - Тип системы наведения ракет установленный на истребителе.
    // 4 - Наведение в переднюю или заднюю полусферу.
    // 5 - Скрытность.
    // 6 - Реализуемость траектории.
    // 7 - Отсутствие или присутствие перегрузок.

    QSqlRelationalTableModel *model_rule;
};

#endif // PACKETSHAPER_H
