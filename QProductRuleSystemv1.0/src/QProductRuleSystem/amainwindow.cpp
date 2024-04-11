#include "ui_amainwindow.h"
#include "amainwindow.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include <QApplication>

#include "settings.h"

AMainWindow::AMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AMainWindow)
{
    ui->setupUi(this);

    setWindowFlag(Qt::WindowType::FramelessWindowHint); ///< Отключение рамки окна определенной по умолчанию;

    setStyle(QStyleFactory::create("Fusion"));

    Settings* settings = qApp->property("settingsApp").value<Settings*>();

    wsettings = new WSettings(this);

    sldBtn = new QSliderButton(this, settings->GetStatus());

    connect(sldBtn, &QSliderButton::click, settings, &Settings::changeTheme);
    
    ui->horizontalLayout->insertWidget(1, sldBtn, 0, Qt::AlignmentFlag::AlignVCenter);

    setMouseTracking(true);
    setCursor(_cursor);

    // Обработчик закрытия окна:
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(close()));
    /*
     * ui->toolButton испускает сигнал clicked(). Метод close() наследуемый компонентом this [amainwindow] от QMainWindow закрывает окно.
     * Т. к. закрывается абстрактный класс, до и наследуемый класс тоже закрывается.
    */

    // Обработчик расширения/сужения окна окна:
    connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(collapse()));
    // Обработчик сворачивания окна:
    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(collapse2()));
    // обработчик запуска окна настроек программы
    connect(ui->toolButton_4, SIGNAL(clicked(bool)), this, SLOT(changeSettings()));

    ui->close->hide();
}

void AMainWindow::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing);
    painter.setBrush(QColor(0, 0, 0, 100));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.setOpacity(0.5);

    QString offColor = "#ffffff";//#000000

    //qDebug() << offColor;
    QString aoffColor = offColor;
    QColor mainColorOff = QColor(aoffColor);
    QColor subColorOff = QColor(aoffColor);
    //subColorOff.setHsl(0,100,95,0);

    //QLinearGradient linearGrad(QPointF(2, 2), QPointF(this->width() / 2, this->height() / 2));
    QLinearGradient linearGrad(QPointF(0, this->width() / 2), QPointF(0, this->height() / 2));
    linearGrad.setColorAt(0, subColorOff);
    linearGrad.setColorAt(1, mainColorOff);

    painter.setBrush(linearGrad);

    painter.drawRect(rect());
}

void AMainWindow::mousePressEvent(QMouseEvent *event)
{
    this->setProperty("dragPos", event->pos());

    event->accept();

    _cursor.setShape(Qt::CursorShape::ClosedHandCursor);

    QMainWindow::mousePressEvent(event);
}

void AMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(_cursor.shape() == Qt::CursorShape::ClosedHandCursor){
        QPoint globPoint;

#if QT_VERSION <= 0x051500
        globPoint = event->globalPos();
#else
        globPoint = event->globalPosition().toPoint();
#endif

        move(globPoint - property("dragPos").toPoint());

        event->accept();
    }

    QMainWindow::mouseMoveEvent(event);
}

void AMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    _cursor.setShape(Qt::CursorShape::OpenHandCursor);

    QMainWindow::mouseReleaseEvent(event);
}

AMainWindow::~AMainWindow()
{
    if(wsettings != nullptr) delete  wsettings;

    delete sldBtn;
}
