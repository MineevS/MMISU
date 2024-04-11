#include "statisticsanalyzer.h"
#include "ui_statisticsanalyzer.h"

StatisticsAnalyzer::StatisticsAnalyzer(QSqlDatabase & db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StatisticsAnalyzer), _db(db)
{
    ui->setupUi(this);
}

StatisticsAnalyzer::~StatisticsAnalyzer()
{
    delete ui;
}
