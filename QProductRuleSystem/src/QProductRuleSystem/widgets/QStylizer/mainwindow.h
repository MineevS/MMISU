#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

#include "qstylizer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString& loadStyle(const QString& pathStyle){
        QFile file = QFile(pathStyle);
        if(!file.exists())
            qDebug() << "Error file style App!";

        // TODO
        // Реализовать проверку наличия/отсутствия тем в путях.

        if(file.open(QFile::OpenModeFlag::ReadOnly | QFile::OpenModeFlag::Text)){
            currentStyleApp = file.readAll();
        }

        //qDebug() << currentStyleApp;

        return currentStyleApp;
    }

private:
    Ui::MainWindow *ui;

    QString currentStyleApp;
};
#endif // MAINWINDOW_H
