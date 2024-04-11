#ifndef STATISTICSANALYZER_H
#define STATISTICSANALYZER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class StatisticsAnalyzer;
}

class StatisticsAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatisticsAnalyzer(QSqlDatabase &,QWidget *parent = nullptr);
    ~StatisticsAnalyzer();

private:
    Ui::StatisticsAnalyzer *ui;

    QSqlDatabase &_db;

    QSqlTableModel *model;
};

#endif // STATISTICSANALYZER_H
