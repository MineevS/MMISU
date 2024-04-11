#include "ilc.h"
#include "ui_ilc.h"
#include "ui_amainwindow.h"

#include "packetshaper.h"

#include <QSqlDatabase>
#include <QSqlError>

#include <QDebug>

#include <QFileDialog>
#include <QSqlQuery>

ILC::ILC(QWidget *parent)
    : AMainWindow(parent)
    , ui_amw(GetUI()), ui_ilc(new Ui::ILC){
    QMainWindow* qmv = new QMainWindow(); // Посредник между внешним ui_amw и вложенным в него ui_ilc;
    qmv->setWindowFlags(Qt::Widget);
    qmv->setObjectName("qmv");

    ui_ilc->setupUi(qmv); // Можно установить только в QMainWindow;
    ui_amw->gridLayout->addWidget(qmv, 0, 0, 1, 1);

    connect(ui_ilc->select_db, &QToolButton::clicked, this, [&, this](bool val){
        Q_UNUSED(val)

        QString runPath = QCoreApplication::applicationDirPath();

        QUrl fileUrl = QFileDialog::getOpenFileUrl(this,
            tr("Открыть БД"),  runPath, tr("SQLITE (*.db)"));

        ui_ilc->path_db->setText(fileUrl.toLocalFile());

        QStringList drivers = QSqlDatabase::drivers();
        foreach(QString driver, drivers)
            qDebug() << driver;

        if(drivers.fill("QSQLITE").length() > 0) // Ответ на вопрос: Содержится ли плагин драйвера <QODBC> на данном устройстве?
            qDebug() << "YES!";

        db = QSqlDatabase::addDatabase("QSQLITE", "DB_001"); // Подключение драйвера!
        db.setDatabaseName(fileUrl.toLocalFile()); // Путь к БД (Полный или относительный); (Относительный обязательно через ./<name_db>) //C:/Users/msa/Documents/QTPROJECTS/build-QProSystem_ILC-Desktop_Qt_6_6_2_MinGW_64_bit-Debug/

        db.open();

        func();
    });
}

ILC::~ILC(){
    delete ui_amw;
    delete ui_ilc;
}

void ILC::func(){
    if (db.isOpen()) {
        qDebug("open");

        ui_ilc->button_packet->setStyleSheet("background-color: #00ff00;");

        ui_ilc->button_packet->setEnabled(true);

        ui_amw->status_bar->setText("Подключение к БД прошло успешно!");

        ui_ilc->select_db->setEnabled(false);
        ui_ilc->close_db->setEnabled(true);

        conn_close = connect(ui_ilc->close_db, &QToolButton::clicked, this, [&, this](bool val){
            Q_UNUSED(val)

            if (db.isOpen()) {
                {
                    db.close();

                    ui_ilc->button_packet->setStyleSheet("background-color: #ff0000;");
                    ui_ilc->button_packet->setEnabled(false);

                    disconnect(conn_packet);
                    disconnect(conn_close);
                }

                QSqlDatabase::removeDatabase("DB_001");

                ui_amw->status_bar->setText("Отключение от БД прошло успешно!"); // Закрытие БД с неявным вызовом close() и очисткой соответствующих hash;
            }

            ui_ilc->select_db->setEnabled(true);
            ui_ilc->close_db->setEnabled(false);

            ui_ilc->path_db->clear();
        });
    } else {
        qDebug() << db.lastError();

        ui_ilc->button_packet->setStyleSheet("background-color: #ff0000;");
    }

    ui_amw->status_bar->setText(db.lastError().text());

    conn_packet = connect(ui_ilc->button_packet, &QToolButton::clicked, this, [&](bool val){
        Q_UNUSED(val)

        PacketShaper *ps = new PacketShaper(db);
        ps->setObjectName("ps");

        ui_amw->gridLayout->parentWidget()->findChild<QMainWindow*>("qmv")->hide(); // Внутри lambda функций нельзя обращаться непосредственно к виджетам через явное использование qmv. Только с помощью поиска!
        ui_amw->gridLayout->addWidget(ps, 0, 0, 1, 1);

        ui_amw->close->show();
        conn = connect(ui_amw->close, &QToolButton::clicked, [this](){
            ui_amw->close->hide();
            ui_amw->gridLayout->removeWidget(ui_amw->gridLayout->parentWidget()->findChild<PacketShaper*>("ps"));
            ui_amw->gridLayout->parentWidget()->findChild<PacketShaper*>("ps")->deleteLater();
            ui_amw->gridLayout->parentWidget()->findChild<QMainWindow*>("qmv")->show();
            disconnect(conn);
        });
    });
}
