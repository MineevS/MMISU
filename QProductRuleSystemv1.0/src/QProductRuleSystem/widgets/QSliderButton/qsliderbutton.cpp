#include "qsliderbutton.h"
#include <QPainter>

#include <QLinearGradient>

QSliderButton::QSliderButton(QWidget *parent, int stat)
{
    this->setParent(parent);

    // for Debug
    /*
        qDebug() << metaObject()->className();

        qDebug() << this->property("color");
        qDebug() << this->property("offColor");
        qDebug() << this->property("background");
        qDebug() << this->property("offBackground");
    */

    status = stat;
}

QSliderButton::QSliderButton()
{
}

void QSliderButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor("#fff"), 0.1));

    QString bgColorTxt = "#ffffff";
    QColor bgColor = QColor(bgColorTxt);
    painter.setBrush(bgColor);

    painter.drawRoundedRect(QRectF(0, 0, 50, 20),10,10);

    /*
        QLinearGradient linearGradBtn;
        linearGradBtn.setStart(QPointF(0, 0));
        linearGradBtn.setFinalStop(QPointF(16, 16));

        QString onColor = "#444";
        QColor mainColorOn = QColor(onColor);
        QColor subColorOn = QColor(onColor);
        subColorOn.setHsl(0,100,95,0);
    */
	
	if (this->status==QSliderButton::on) {
        /*
            QLinearGradient linearGrad(QPointF(32, 2), QPointF(46, 16));
            linearGrad.setColorAt(0, subColorOn);
            linearGrad.setColorAt(1, mainColorOn);

            painter.setBrush(linearGrad);

            painter.drawEllipse( QRectF(30, 2, 17, 16));
        */ // 16;
        QColor color = QColor("#fff");
        painter.setPen(QPen(color, 0.1));

		QString bgColorTxt = this->bg;
		QColor bgColor = QColor(bgColorTxt);
		painter.setBrush(bgColor);
		painter.drawRoundedRect(QRectF(0, 0, 50, 20),10,10);

		QString onColor = this->color;
        //QColor mainColorOn = QColor(onColor);
        QColor mainColorOn ;//= QColor(onColor);
		QColor subColorOn = QColor(onColor);
		subColorOn.setHsl(0,100,95,0);

        QLinearGradient linearGrad2; //= new QLinearGradient(QPointF(32, 2), QPointF(46, 16));
        linearGrad2.setStart(QPointF(32, 2));
        linearGrad2.setFinalStop(QPointF(46, 16));
        linearGrad2.setColorAt(0, subColorOn);
        linearGrad2.setColorAt(1, mainColorOn);

        painter.setBrush(linearGrad2);
		painter.drawEllipse( QRectF(30, 2, 16, 16) );
	} else {
        /*
            QLinearGradient linearGrad(QPointF(2, 2), QPointF(16, 16));
            linearGrad.setColorAt(0, subColorOn);
            linearGrad.setColorAt(1, mainColorOn);
            painter.setBrush(linearGrad);
            painter.drawEllipse( QRectF(2, 2, 16, 16));
        */
		
		QString bgColorTxt = this->offBg;
		QColor bgColor = QColor(bgColorTxt);
		painter.setBrush(bgColor);
		painter.drawRoundedRect(QRectF(0, 0, 50, 20),10,10);

        //qDebug() << this->offColor;
		QString aoffColor = this->offColor;
		QColor mainColorOff = QColor(aoffColor);
		QColor subColorOff = QColor(aoffColor);
		subColorOff.setHsl(0,100,95,0);

		QLinearGradient linearGrad(QPointF(2, 2), QPointF(16, 16));
		linearGrad.setColorAt(0, subColorOff);
		linearGrad.setColorAt(1, mainColorOff);

		painter.setBrush(linearGrad);
		painter.drawEllipse( QRectF(2, 2, 16, 16) );
	}

    /*
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(16, 16));
        linearGrad.setColorAt(0, subColorOn);
        linearGrad.setColorAt(1, mainColorOn);

        painter.setBrush(linearGrad);
        painter.drawEllipse( QRectF(2, 2, 16, 16) );
    */
}

QSize QSliderButton::sizeHint() const {
    return QSize(50, 20);
}

void QSliderButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton ) {
        //qDebug() << "Left Mouse button pressed";

        if (this->status== QSliderButton::on) {
            this->status = QSliderButton::off;
            emit toggled(this->status);
        } else {
            this->status = QSliderButton::on;
            emit toggled(this->status);
        }
        repaint();
    }
    emit this->clicked(event);
    emit this->click();
	
    /*
       if (event->button() == Qt::LeftButton ) {
        if (this->status==QSliderButton::on) {
            this->status = QSliderButton::off;
        } else {
            this->status = QSliderButton::on;
        }
        repaint();
    }*/
	
    /*
       if (event->button() == Qt::LeftButton ) {
        qDebug() << "Left Mouse button pressed";
        repaint();
    }*/
}

int QSliderButton::getStatus() const
{
    return status;
}

void QSliderButton::setStatus(int value)
{
    status = value;
}

QString QSliderButton::getOffBgQString() const
{
    return offBg;
}

void QSliderButton::setOffBg(QColor colorv)
{
    offBg = colorv.name();
}

void QSliderButton::setOffBgQString(const QString &value)
{
    offBg = value;
}

void QSliderButton::offBgChanged()
{
   // TODO;
}

QString QSliderButton::getBgQString() const
{
    return bg;
}

void QSliderButton::setBg(QColor colorv)
{
    bg = colorv.name();
}

void QSliderButton::setBgQString(const QString &value)
{
    bg = value;
}

void QSliderButton::bgChanged()
{
    // TODO;
}

QColor QSliderButton::getOffBg() const
{
    return QColor(offBg);
}

QString QSliderButton::getOffColorQString() const
{
    return offColor;
}

void QSliderButton::setOffColor(QColor colorv)
{
    offColor = colorv.name();
}

void QSliderButton::setOffColorQString(const QString &value)
{
    offColor = value;
}

void QSliderButton::offColorChanged()
{
    // TODO;
}

QColor QSliderButton::getBg() const
{
    return QColor(bg);
}

QColor QSliderButton::getColor() const
{
    return QColor(color);
}

QString QSliderButton::getColorQString() const
{
    return color;
}

void QSliderButton::setColor(QColor colorv)
{
    color = colorv.name();
}

void QSliderButton::setColorQString(const QString &value)
{
    color = value;
}

void QSliderButton::colorChanged()
{
    // TODO;
}

QColor QSliderButton::getOffColor() const
{
    return offColor;
}

/*void QSliderButton::toggle()
{
    if (this->status == 0) {
        this->status = 1;
    } else {
        this->status = 0;
    }
    emit toggled(this->status);
    repaint();
}*/
