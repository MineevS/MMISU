#ifndef WSETTINGS_H
#define WSETTINGS_H

#include <QMainWindow>
#include <QColorDialog>
#include <QStyleFactory>
#include <QToolButton>

#include "qstylizer.h"
#include "settings.h"
//#include "qpropertyeditor.h"

#if defined(INCLUDE_SETTINGS)
//#include "qtbuttonpropertybrowser.h"
//#include "qteditorfactory.h"
//#include "qtgroupboxpropertybrowser.h"
//#include "qtpropertybrowser.h"
//#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"
//#include "qtvariantproperty.h"
#endif

namespace Ui {
class WSettings;
}

class WSettings : public QMainWindow
{
    Q_OBJECT
public:
    explicit WSettings(QWidget *parent = nullptr);

    ~WSettings();

public slots:
    void expanded(){
        setWindowState(windowState() ^ Qt::WindowState::WindowFullScreen);
    }

    void collapse2(){
        setWindowState(windowState() ^ Qt::WindowState::WindowMinimized);
    }

    void updateCurrentTheme(){
        Settings* settings = qApp->property("settingsApp").value<Settings*>();

        if(settings->getCurrentThemeApp().compare("theme_first") == 0){
            qApp->setStyleSheet(stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        }else{
            qApp->setStyleSheet(stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        }
    }

private:
    Ui::WSettings   *ui;

    QStylizer* stylizer;

#if defined(INCLUDE_SETTINGS)
    QtTreePropertyBrowser *browser;
#endif

    QMap<QString, QMap<QString, QMap<QString, QString>>> currentStyleFirstTheme;
    QMap<QString, QMap<QString, QMap<QString, QString>>> currentStyleSecondTheme;
};

#endif // WSETTINGS_H
