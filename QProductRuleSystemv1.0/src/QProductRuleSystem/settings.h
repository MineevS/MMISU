#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

#include <QSettings>
#include <QApplication>
#include <QFile>
#include <QDebug>

#include <QUrl>
#include <QDesktopServices>
//#include "amainwindow.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();

    Settings(QApplication* app);

    /*
        @brief  Проверка наличия настроек в реестре и установка в случае их отсутствия.
    */
    bool loadSettingsApp(){
        if(settingsApp->allKeys().count() == 0){
            createSettingsApp();
            return loadSettingsApp();
        } else return true;
    }

    bool GetStatus(){
        return !(currentThemeApp.compare("theme_first") == 0);
    }

    /*
        @brief  Создание настроек приложения
    */
    void createSettingsApp(){
        settingsApp->beginGroup("BaseSettings");

        settingsApp->setValue("NameApp",    QString(APPLICATION_NAME));
        settingsApp->setValue("VersionApp", QString(APPLICATION_VERSION));

        settingsApp->endGroup();

        settingsApp->beginGroup("StyleSettings");

        settingsApp->setValue("theme_current", "theme_first");

        settingsApp->endGroup();

        settingsApp->sync();  // Фиксация настроек приложения
    }

    /*
        @brief Загрузка из реестра информации по текущей теме приложения.
    */
    QString& loadThemeCurrentApp(){
        settingsApp->beginGroup("StyleSettings");

        currentThemeApp = QString(settingsApp->value("theme_current").toString());

        settingsApp->endGroup();

        return currentThemeApp;
    }

    bool loadStyleCurrentApp(){
        const QString pathStyle = (currentThemeApp.compare("theme_first") == 0) ? THEME_FIRST_PATH : THEME_SECOND_PATH;

        qApp->setStyleSheet(loadStyle(pathStyle));

        //qDebug() << pathStyle;
        //qDebug() << loadStyle(pathStyle);

        return true;
    }

    QString& loadStyle(const QString& pathStyle){
        QFile file;//= QFile(pathStyle); //"style.css"
        file.setFileName(pathStyle);
        if(!file.exists())
            qDebug() << "Error file style App!";

        // TODO
        // Реализовать проверку наличия/отсутствия тем в путях.

        if(file.open(QFile::OpenModeFlag::ReadOnly | QFile::OpenModeFlag::Text)){
            currentStyleApp = file.readAll();
        }

        //qDebug() << "|||" << currentStyleApp;

        file.close();

        return currentStyleApp;
    }

public slots:
    void changeTheme(){
        QString pathStyle = (currentThemeApp.compare("theme_first") == 0) ?  THEME_SECOND_PATH : THEME_FIRST_PATH;

        qApp->setStyleSheet(loadStyle(pathStyle));

        currentThemeApp = (currentThemeApp.compare("theme_first") == 0) ? "theme_second" : "theme_first";

        settingsApp->beginGroup("StyleSettings");
        settingsApp->setValue("theme_current", currentThemeApp);
        settingsApp->endGroup();

        settingsApp->sync();

    }

    QString getCurrentThemeApp(){
        return currentThemeApp;
    }

private:
    QSettings* settingsApp;

    QString currentThemeApp;
    QString currentStyleApp;
};

#endif // SETTINGS_H
