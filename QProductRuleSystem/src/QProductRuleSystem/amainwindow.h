#ifndef AMAINWINDOW_H
#define AMAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>

#include <QStyleFactory>

#include "wsettings.h"

#include "widgets/QSliderButton/qsliderbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AMainWindow;
}
QT_END_NAMESPACE

class AMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    AMainWindow(QWidget *parent = nullptr);
    ~AMainWindow();

protected:
    void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);

    QSliderButton * GetSldBtn(){
        return sldBtn;
    }

    Ui::AMainWindow * GetUI(){
        return ui;
    }

public slots:
    void collapse(){
        setWindowState(windowState() ^ Qt::WindowState::WindowFullScreen);
    }

    void collapse2(){
        setWindowState(windowState() ^ Qt::WindowState::WindowMinimized);
    }

    void changeSettings(){
        wsettings->setGeometry(this->pos().x() + this->width() / 4, this->pos().y() + this->height() / 4, this->width() / 2, this->height() / 2);
        wsettings->show(); 
    }

 private:
    Ui::AMainWindow *ui;
    QCursor _cursor;

    QSliderButton *sldBtn;

    WSettings* wsettings = nullptr;

signals:
    void clicked();
};
#endif // AMAINWINDOW_H
