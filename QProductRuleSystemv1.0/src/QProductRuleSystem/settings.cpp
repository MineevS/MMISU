#include "settings.h"

Settings::Settings() {
    settingsApp = new QSettings(ORGANIZATION_NAME, APPLICATION_NAME);

    if(loadSettingsApp()){
        loadThemeCurrentApp();
        loadStyleCurrentApp();

        qApp->setStyleSheet(currentStyleApp);
    }
}

Settings::Settings(QApplication *app)
{
    settingsApp = new QSettings(ORGANIZATION_NAME, APPLICATION_NAME);

    if(loadSettingsApp()){
        loadThemeCurrentApp();
        loadStyleCurrentApp();

        app->setStyleSheet(currentStyleApp);
    }
}
