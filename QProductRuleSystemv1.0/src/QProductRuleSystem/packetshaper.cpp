#include "packetshaper.h"
#include "ui_packetshaper.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QModelIndex>
#include <QPair>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QAbstractItemView>
#include <QCheckBox>
#include <QToolButton>
#include <QSqlField>

PacketShaper::PacketShaper(QSqlDatabase & db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PacketShaper), _db(db)
{
    ui->setupUi(this);

    model_sutvec = new QSqlRelationalTableModel(this, _db);
    model_sutvec->setTable("SituationalVector");
    model_sutvec->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_sutvec->setSort(0, Qt::SortOrder::AscendingOrder);
    model_sutvec->select();

    ui->ipt_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->ipt_view->horizontalHeader()->setStretchLastSection(true);
    ui->ipt_view->setModel(model_sutvec);
    ui->ipt_view->setItemDelegate(new QSqlRelationalDelegate(ui->ipt_view));

    model_rule = new QSqlRelationalTableModel(this, _db);
    model_rule->setTable("ProductRules");
    model_rule->setEditStrategy(QSqlTableModel::OnManualSubmit); // OnManualSubmit // OnFieldChange // OnRowChange // OnManualSubmit
    model_rule->setSort(0, Qt::SortOrder::AscendingOrder);
    model_rule->select();

    ui->productrule_view->setItemDelegate(new QSqlRelationalDelegate(ui->productrule_view));
    ui->productrule_view->setModel(model_rule);
    ui->productrule_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    model_rule->setRelation(2,
      QSqlRelation("Pos_fighter_aircraft_rel_target_forRule",
                   "Местоположение_истребителя_по_отношению_к_цели",
                   "Местоположение_истребителя_по_отношению_к_цели"));

    model_rule->setRelation(3,
      QSqlRelation("Missile_guidance_system_type",
                   "Тип_системы_наведения_ракет",
                   "Тип_системы_наведения_ракет"));

    model_rule->setRelation(4,
      QSqlRelation("Need_for_guidance",
                   "Необходимость_наведения",
                   "Необходимость_наведения"));

    model_rule->setRelation(5,
      QSqlRelation("S_4",
                   "Требование_к_скрытности",
                   "Требование_к_скрытности"));

    model_rule->setRelation(6,
      QSqlRelation("S_5",
                   "Реализуемость_траектории_наведения",
                   "Реализуемость_траектории_наведения"));

    model_rule->setRelation(7,
      QSqlRelation("S_6",
                   "Отсутствие_или_наличие_перегрузок",
                   "Отсутствие_или_наличие_перегрузок"));

    model_rule->setRelation(8,
      QSqlRelation("Methods",
                   "Методы_наведения",
                   "Методы_наведения"));


    model_workMemory = new QSqlRelationalTableModel(this, _db);
    model_workMemory->setTable("WorkMemory");
    model_workMemory->setEditStrategy(QSqlTableModel::OnManualSubmit); // OnManualSubmit // OnFieldChange // OnRowChange // OnManualSubmit
    model_workMemory->select();

    ui->dec_view->setModel(model_workMemory);
    ui->dec_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->dec_view->setItemDelegate(new QSqlRelationalDelegate(ui->dec_view));

    model_workMemory->setRelation(1,
      QSqlRelation("Pos_fighter_aircraft_rel_target",
                   "Текущее_местоположение_истребителя_по_отношению_к_цели",
                   "Текущее_местоположение_истребителя_по_отношению_к_цели"));

    model_workMemory->setRelation(2,
      QSqlRelation("Missile_guidance_system_type",
                   "Тип_системы_наведения_ракет",
                   "Тип_системы_наведения_ракет"));

    for(int i = 0; i < 21; i += 7){
        model_workMemory->setRelation(4 + i,
          QSqlRelation("Pos_fighter_aircraft_rel_target",
                       "Текущее_местоположение_истребителя_по_отношению_к_цели",
                       "Текущее_местоположение_истребителя_по_отношению_к_цели"));

        model_workMemory->setRelation(5 + i,
          QSqlRelation("Missile_guidance_system_type",
                       "Тип_системы_наведения_ракет",
                       "Тип_системы_наведения_ракет"));

        model_workMemory->setRelation(6 + i,
          QSqlRelation("Need_for_guidance",
                       "Необходимость_наведения",
                       "Необходимость_наведения"));

        model_workMemory->setRelation(7 + i,
          QSqlRelation("S_4",
                       "Требование_к_скрытности",
                       "Требование_к_скрытности"));

        model_workMemory->setRelation(8 + i,
          QSqlRelation("S_5",
                       "Реализуемость_траектории_наведения",
                       "Реализуемость_траектории_наведения"));

        model_workMemory->setRelation(9 + i,
          QSqlRelation("S_6",
                       "Отсутствие_или_наличие_перегрузок",
                       "Отсутствие_или_наличие_перегрузок"));//
    }

    connect(ui->dec_view->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,const QItemSelection &)),
            this,
            SLOT(selectionChangedDecView(const QItemSelection &,const QItemSelection &)));

    connect(ui->create_parcel, &QToolButton::clicked, this, [this](){
        int row_count = model_workMemory->rowCount();
        QList<int> list;

        qDebug() << row_count;

        static QRegularExpression reg;
        reg.setPattern("(\\d+)");
        for (int i = 0; i < row_count; ++i) {
            QRegularExpressionMatch match = reg.match(model_workMemory->itemData(model_workMemory->index(i, 0))[0].toString().toStdString().c_str());
            if(match.isValid()) list << match.captured(0).toInt();
        }

        std::sort(list.begin(), list.end());

        int min = 1;
        auto it = list.cbegin();
        while(it != list.cend()){
            if(min != *it)
                break;
            min++;
            it++;
        }

        if(model_workMemory->insertRow(min - 1)) {
            ui->dec_view->selectRow(min - 1);
            model_workMemory->setData(model_workMemory->index(min - 1, 0), "Запрос № " + QString::number(min)); //Qt::EditRole
        } else ui->line_result->setText("Error insert Row!");
    });

    connect(ui->submitAll, &QToolButton::clicked, this, [this](){
        model_workMemory->submitAll();
        model_workMemory->select();

        ui->dec_view->update();
    });

    connect(ui->delete_parcel, &QToolButton::clicked, this, [this](){
        QModelIndexList selection = ui->dec_view->selectionModel()->selectedRows();
        for(int i = 0; i< selection.count(); i++)
            model_workMemory->removeRow(selection.at(i).row());

        if(!ui->create_parcel->isEnabled()) ui->create_parcel->setEnabled(true);
    });
}

PacketShaper::~PacketShaper(){
    delete ui;
}

void PacketShaper::on_create_record_clicked(){
    int row_count = model_rule->rowCount();
    QList<int> list;

    // Определяем минимальный номер продукционных правил.
    static QRegularExpression reg;
    reg.setPattern("(\\d+)");
    for (int i = 0; i < row_count; ++i){
        QRegularExpressionMatch match = reg.match(model_rule->itemData(model_rule->index(i, 0))[0].toString().toStdString().c_str());

        qDebug() << match.captured(0).toInt();
        if(match.isValid()) list << match.captured(0).toInt();
    }

    std::sort(list.begin(), list.end());

    int min = 1;
    auto it = list.cbegin();
    while(it != list.cend()){
        if(min != *it)
            break;
        min++;
        it++;
    }

    // Создаем новую строку с min - 1 номером в соответствующей строке!
    if(model_rule->insertRow(min - 1)){
        ui->productrule_view->selectRow(min - 1);
        model_rule->setData(model_rule->index(min - 1, 0), "Продукционное правило № " + QString::number(min)); //Qt::EditRole
    }
}


void PacketShaper::on_toolButton_clicked(){
    model_rule->submitAll();
    model_rule->select();

    model_workMemory->submitAll();
    model_workMemory->select();

    ui->productrule_view->update();
    ui->ipt_view->update();
}


void PacketShaper::on_delete_record_clicked(){
    QModelIndexList selection = ui->productrule_view->selectionModel()->selectedRows();

    for(int i = 0; i< selection.count(); i++)
        if(model_rule->removeRow(selection.at(i).row()))
            ui->productrule_view->model()->removeRow(selection.at(i).row());
}

void PacketShaper::on_clear_db_clicked(){
    ui->productrule_view->model()->removeRows(0,  ui->productrule_view->model()->rowCount());
    model_rule->removeRows(0, model_sutvec->rowCount());
}

