#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadStyle(":/qss/ThemeFirst.css");

    QStylizer stylizer(this->currentStyleApp);


}

MainWindow::~MainWindow()
{
    delete ui;
}
