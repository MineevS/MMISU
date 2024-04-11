# module: QPropertyBrowser
#
SOURCES += \
    $$PWD/src/qtbuttonpropertybrowser.cpp \
    $$PWD/src/qteditorfactory.cpp \
    $$PWD/src/qtgroupboxpropertybrowser.cpp \
    $$PWD/src/qtpropertybrowser.cpp \
    $$PWD/src/qtpropertybrowserutils.cpp \
    $$PWD/src/qtpropertymanager.cpp \
    $$PWD/src/qttreepropertybrowser.cpp \
    $$PWD/src/qtvariantproperty.cpp

HEADERS += \
    $$PWD/inc/qtbuttonpropertybrowser.h \
    $$PWD/inc/qteditorfactory.h \
    $$PWD/inc/qtgroupboxpropertybrowser.h \
    $$PWD/inc/qtpropertybrowser.h \
    #$$PWD/inc/qtpropertybrowserutils.h \
    $$PWD/inc/qtpropertybrowserutils_p.h \
    $$PWD/inc/qtpropertymanager.h \
    $$PWD/inc/qttreepropertybrowser.h \
    $$PWD/inc/qtvariantproperty.h

INCLUDEPATH += $$PWD/inc/

#message($$PWD)

# FORMS += widget.ui

# Add in base: include(qpropertybrowser.pri)

# http://www.wiki.crossplatform.ru/index.php/The_Property_Browser_Framework
