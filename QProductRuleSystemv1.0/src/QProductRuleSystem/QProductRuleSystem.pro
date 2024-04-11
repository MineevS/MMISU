#
DEFINES += \
    ORGANIZATION_NAME=\\\"MIREA\\\" \
    ORGANIZATION_DOMAIN=\\\"mirea.su\\\" \
    APPLICATION_NAME=\\\"QProductRule\\\" \
    APPLICATION_VERSION=\\\"1.0\\\" \
    THEME_FIRST_PATH=\\\"./qss/ThemeFirst.css\\\" \
    THEME_SECOND_PATH=\\\"./qss/ThemeSecond.css\\\" \
    INCLUDE_SETTINGS # Включить/Отключить для добавления/удаления функциональности изменения настроек; (Обязательно пересобрать проект!)

QT     += core gui gui-private sql # uitools #qcss

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32 {
    QMAKE_CXXFLAGS += -Wa,-mbig-obj
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    amainwindow.cpp \
    ilc.cpp \
    main.cpp \
    packetshaper.cpp \
    settings.cpp \
    wsettings.cpp

HEADERS += \
    amainwindow.h \
    ilc.h \
    packetshaper.h \
    settings.h \
    wsettings.h

FORMS += \
    amainwindow.ui \
    ilc.ui \
    packetshaper.ui \
    wsettings.ui

#modules:
include(widgets/QSliderButton/qsliderbutton.pri)
include(widgets/QStylizer/qstylizer.pri)

contains(DEFINES, INCLUDE_SETTINGS) {
   message(include settings!)
   include(widgets/QPropertyBrowser/qpropertybrowser.pri)
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = icons/iconApp.ico

RESOURCES += \
    resources.qrc
