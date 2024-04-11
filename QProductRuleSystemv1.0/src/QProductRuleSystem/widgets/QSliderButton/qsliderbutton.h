#ifndef QSLIDERBUTTON_H
#define QSLIDERBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>

class QSliderButton : public QWidget {
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(QColor offColor READ getOffColor WRITE setOffColor NOTIFY offColorChanged FINAL)
    Q_PROPERTY(QColor background READ getBg WRITE setBg NOTIFY bgChanged FINAL)
    Q_PROPERTY(QColor offBackground READ getOffBg WRITE setOffBg NOTIFY offBgChanged FINAL)
public:
    explicit QSliderButton(QWidget* parent, int status = 0);
    QSliderButton();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual QSize sizeHint() const;
	
	virtual void mousePressEvent(QMouseEvent * event);

public:    
    int getStatus() const;
    void setStatus(int value);

    static const int off = 0;
    static const int on  = 1;

private:
    int status = 0;
	
private:
    QString color = "#444";
    QString offColor = "#444";
    QString bg = "#ffffff";
    QString offBg = "#ffffff";
	
public:

    QColor getColor() const;
    QString getColorQString() const;
    void setColor(QColor colorv);
    void setColorQString(const QString &value);
    void colorChanged();

    QColor getOffColor() const;
    QString getOffColorQString() const;
    void setOffColor(QColor colorv);
    void setOffColorQString(const QString &value);
    void offColorChanged();

    QColor getBg() const;
    QString getBgQString() const;
    void setBg(QColor colorv);
    void setBgQString(const QString &value);
    void bgChanged();

    QColor getOffBg() const;
    QString getOffBgQString() const;
    void setOffBg(QColor colorv);
    void setOffBgQString(const QString &value);
    void offBgChanged();

signals:
    void clicked(QMouseEvent *event);
    void toggled(int status);
    void click();

};

#endif // QSLIDERBUTTON_H
