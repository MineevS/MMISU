//#include "AMainWindow.h"

#include "settings.h"

#include "ilc.h"

#include <QApplication>

#if QT_VERSION <= 0x051500
#include <QDesktopWidget>
#include <QRect>
#endif

#include <QScreen>

int main(int argc, char *argv[]){
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    QApplication a(argc, argv);

    qApp->setProperty("settingsApp", QVariant::fromValue(new Settings()));

    ILC ilc;

#if QT_VERSION <= 0x051500
    QRect rect = QApplication::primaryScreen()->availableGeometry();
    ilc.setGeometry(0, 0, rect.width(), rect.height());
#endif

    ilc.show();

    return a.exec();
}
