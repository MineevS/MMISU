#include "wsettings.h"
#include "ui_wsettings.h"

#include <QRegularExpression>

#if defined(INCLUDE_SETTINGS)
#include "qteditorfactory.h"
#include "qtpropertybrowser.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#endif

WSettings::WSettings(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WSettings)
{
    ui->setupUi(this); // Можно установить только в QMainWindow;

    setWindowFlag(Qt::WindowType::FramelessWindowHint); ///< Отключение рамки окна определенной по умолчанию;

    // Обработчик закрытия окна:
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(close()));
    /*
     * ui->toolButton испускает сигнал clicked(). Метод close() наследуемый компонентом this [amainwindow] от QMainWindow закрывает окно.
     * Т. к. закрывается абстрактный класс, до и наследуемый класс тоже закрывается.
    */

    // Обработчик расширения/сужения окна окна:
    connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(expanded()));
    // Обработчик сворачивания окна:
    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(collapse2()));

    stylizer = new QStylizer();
    stylizer->loadStyleSheetFromQString(THEME_FIRST_PATH);
    currentStyleFirstTheme = std::move(stylizer->convertStyleSheetQStringToQMapRef()); // not copy/ Move;

    stylizer->loadStyleSheetFromQString(THEME_SECOND_PATH);
    currentStyleSecondTheme = std::move(stylizer->convertStyleSheetQStringToQMapRef()); // not copy/ Move;

#if defined(INCLUDE_SETTINGS)
    browser = new QtTreePropertyBrowser();

    QtGroupPropertyManager *groupManager = new QtGroupPropertyManager;
    QtProperty *task1;
    task1 = groupManager->addProperty("Свойства окна");

    QtColorPropertyManager * colorManagerTheme = new QtColorPropertyManager;

    QtProperty *background_color_first_theme;
    background_color_first_theme = colorManagerTheme->addProperty("Цвет фона первой темы");
    background_color_first_theme->setToolTip("Цвет фона первой темы");
    background_color_first_theme->setReadOnly(false); // Обязательно указываем флаг иначе не сможем изменять!

    QtProperty *background_color_second_theme;
    background_color_second_theme = colorManagerTheme->addProperty("Цвет фона второй темы");
    background_color_second_theme->setToolTip("Цвет фона второй темы");
    background_color_second_theme->setReadOnly(false);

    QtProperty *text_color_first_theme;
    text_color_first_theme = colorManagerTheme->addProperty("Цвет текста первой темы");
    text_color_first_theme->setToolTip("Цвет текста первой темы");
    text_color_first_theme->setReadOnly(false); // Обязательно указываем флаг иначе не сможем изменять!

    QtProperty *text_color_second_theme;
    text_color_second_theme = colorManagerTheme->addProperty("Цвет текста второй темы");
    text_color_second_theme->setToolTip("Цвет текста второй темы");
    text_color_second_theme->setReadOnly(false);

    QtProperty *text_fone_color_first_theme;
    text_fone_color_first_theme = colorManagerTheme->addProperty("Цвет фона текста первой темы");
    text_fone_color_first_theme->setToolTip("Цвет фона текста первой темы");
    text_fone_color_first_theme->setReadOnly(false); // Обязательно указываем флаг иначе не сможем изменять!

    QtProperty *text_fone_color_second_theme;
    text_fone_color_second_theme = colorManagerTheme->addProperty("Цвет фона текста второй темы");
    text_fone_color_second_theme->setToolTip("Цвет фона текста второй темы");
    text_fone_color_second_theme->setReadOnly(false);

    QtProperty *border_color_first_theme;
    border_color_first_theme = colorManagerTheme->addProperty("Цвет рамки первой темы");
    border_color_first_theme->setToolTip("Цвет рамки первой темы");
    border_color_first_theme->setReadOnly(false); // Обязательно указываем флаг иначе не сможем изменять!

    QtProperty *border_color_second_theme;
    border_color_second_theme = colorManagerTheme->addProperty("Цвет рамки второй темы");
    border_color_second_theme->setToolTip("Цвет рамки второй темы");
    border_color_second_theme->setReadOnly(false);

    QtIntPropertyManager* intManagerTheme = new QtIntPropertyManager;

    QtProperty *border_width_color_first_theme;
    border_width_color_first_theme = intManagerTheme->addProperty("Ширина рамки первой темы");
    border_width_color_first_theme->setToolTip("Ширина рамки первой темы");
    border_width_color_first_theme->setReadOnly(false); // Обязательно указываем флаг иначе не сможем изменять!

    QtProperty *border_width_color_second_theme;
    border_width_color_second_theme = intManagerTheme->addProperty("Ширина рамки второй темы");
    border_width_color_second_theme->setToolTip("Ширина рамки второй темы");
    border_width_color_second_theme->setReadOnly(false);

    QtProperty *border_radius_first_theme;
    border_radius_first_theme = intManagerTheme->addProperty("Радиус рамки первой темы");
    border_radius_first_theme->setToolTip("Радиус рамки первой темы");
    border_radius_first_theme->setReadOnly(false); // Обязательно указываем флаг иначе не сможем изменять!

    QtProperty *border_radius_second_theme;
    border_radius_second_theme = intManagerTheme->addProperty("Радиус рамки второй темы");
    border_radius_second_theme->setToolTip("Радиус рамки второй темы");
    border_radius_second_theme->setReadOnly(false);

    QtEnumPropertyManager *enumManagerTheme = new QtEnumPropertyManager;

    QtProperty *border_style_first_theme = enumManagerTheme->addProperty("Стиль рамки первой темы");
    border_style_first_theme->setToolTip("Стиль рамки первой темы");
    QtProperty *border_style_second_theme = enumManagerTheme->addProperty("Стиль рамки второй темы");
    border_style_second_theme->setToolTip("Стиль рамки второй темы");

    QStringList types;
    types << "solid" << "dashed" << "dotted" << "dot-dash" << "dot-dot-dash" << "double" << "groove" << "inset" << "outset" << "ridge" << "None";
    /*
    | dashed +
    | dot-dash +
    | dot-dot-dash +
    | dotted +
    | double +
    | groove +
    | inset +
    | outset +
    | ridge +
    | solid +
    | none +
    */

    QtFontPropertyManager *fontManagerTheme = new QtFontPropertyManager;

    QtProperty *font_first_theme = fontManagerTheme->addProperty("Шрифт первой темы");
    font_first_theme->setToolTip("Шрифт первой темы");
    font_first_theme->setReadOnly(false);
    QtProperty *font_second_theme = fontManagerTheme->addProperty("Шрифт второй темы");
    font_second_theme->setToolTip("Шрифт второй темы");
    font_second_theme->setReadOnly(false);

    // https://doc.qt.io/qt-6/stylesheet-reference.html

    enumManagerTheme->setEnumNames(border_style_first_theme, types);
    enumManagerTheme->setValue(border_style_first_theme, types.indexOf(QRegularExpression(currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-style"], QRegularExpression::CaseInsensitiveOption), 0));

    enumManagerTheme->setEnumNames(border_style_second_theme, types); // Qt::CaseInsensitive // // W3CXmlSchema11 // QRegularExpression::CaseInsensitiveOption
    enumManagerTheme->setValue(border_style_second_theme, types.indexOf(QRegularExpression(currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-style"], QRegularExpression::CaseInsensitiveOption), 0));

    colorManagerTheme->setValue(background_color_second_theme, QColor(currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["background-color"]));
    colorManagerTheme->setValue(background_color_first_theme, QColor(currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["background-color"]));

    colorManagerTheme->setValue(border_color_second_theme, QColor(currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-color"]));
    colorManagerTheme->setValue(border_color_first_theme, QColor(currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-color"]));

    colorManagerTheme->setValue(text_color_second_theme, QColor(currentStyleSecondTheme["QLabel"]["QLabel"]["color"]));
    colorManagerTheme->setValue(text_color_first_theme, QColor(currentStyleFirstTheme["QLabel"]["QLabel"]["color"]));

    colorManagerTheme->setValue(text_fone_color_second_theme, QColor(currentStyleSecondTheme["QLabel"]["QLabel"]["background-color"]));
    colorManagerTheme->setValue(text_fone_color_first_theme, QColor(currentStyleFirstTheme["QLabel"]["QLabel"]["background-color"]));

    // Реализовать проверки наличия ключей;

    intManagerTheme->setValue(border_width_color_second_theme, currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-width"].toInt());
    intManagerTheme->setValue(border_width_color_first_theme, currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-width"].toInt());

    intManagerTheme->setValue(border_radius_second_theme, currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-radius"].toInt());
    intManagerTheme->setValue(border_radius_first_theme, currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-radius"].toInt());

    fontManagerTheme->setValue(font_second_theme, currentStyleSecondTheme["QLabel"]["QLabel"]["font"]);
    fontManagerTheme->setValue(font_first_theme, currentStyleFirstTheme["QLabel"]["QLabel"]["font"]);

    task1->addSubProperty(background_color_first_theme);
    task1->addSubProperty(background_color_second_theme);

    task1->addSubProperty(text_color_first_theme);
    task1->addSubProperty(text_color_second_theme);

    task1->addSubProperty(text_fone_color_first_theme);
    task1->addSubProperty(text_fone_color_second_theme);

    task1->addSubProperty(border_color_first_theme);
    task1->addSubProperty(border_color_second_theme);

    task1->addSubProperty(border_width_color_first_theme);
    task1->addSubProperty(border_width_color_second_theme);

    task1->addSubProperty(border_radius_first_theme);
    task1->addSubProperty(border_radius_second_theme);

    task1->addSubProperty(border_style_first_theme);
    task1->addSubProperty(border_style_second_theme);

    task1->addSubProperty(font_first_theme);
    task1->addSubProperty(font_second_theme);

    QtColorEditorFactory *colorFactoryTheme = new QtColorEditorFactory;
    browser->setFactoryForManager(colorManagerTheme, colorFactoryTheme);

    QtSpinBoxFactory *spinBoxFactoryTheme = new QtSpinBoxFactory;
    browser->setFactoryForManager(intManagerTheme, spinBoxFactoryTheme);

    QtEnumEditorFactory *enumFactoryTheme = new QtEnumEditorFactory;
    browser->setFactoryForManager(enumManagerTheme, enumFactoryTheme);

    QtFontEditorFactory *fontFactoryTheme = new QtFontEditorFactory;
    browser->setFactoryForManager(fontManagerTheme, fontFactoryTheme);

    connect(colorManagerTheme, &QtColorPropertyManager::valueChanged,
            this, [=](QtProperty * property, const QColor & colorTheme){

        if(property == background_color_first_theme){
            currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["background-color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if (property == background_color_second_theme) {
            currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["background-color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        } else if (property == border_color_first_theme){
            currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if (property == border_color_second_theme){
            currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        } else if (property == text_color_first_theme){
            currentStyleFirstTheme["QLabel"]["QLabel"]["color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if (property == text_color_second_theme){
            currentStyleSecondTheme["QLabel"]["QLabel"]["color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        }else if (property == text_fone_color_first_theme){
            currentStyleFirstTheme["QLabel"]["QLabel"]["background-color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if (property == text_fone_color_second_theme){
            currentStyleSecondTheme["QLabel"]["QLabel"]["background-color"] = colorTheme.name();
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        }

        updateCurrentTheme();
    });

    connect(intManagerTheme, &QtIntPropertyManager::valueChanged,
            this, [=](QtProperty * property, const int & value){

        if (property == border_width_color_first_theme){
            currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-width"] = QString::number(value);
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if (property == border_width_color_second_theme){
            currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-width"] = QString::number(value);
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        }else if(property == border_radius_first_theme){
            currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-radius"] = QString::number(value);
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if(property == border_radius_second_theme){
            currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-radius"] = QString::number(value);
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        }

        updateCurrentTheme();
    });

    connect(enumManagerTheme, &QtEnumPropertyManager::valueChanged,
            this, [=](QtProperty * property, const int & value){

        if (property == border_style_first_theme){
            currentStyleFirstTheme["QMainWindow"]["QMainWindow"]["border-style"] = types.at(value);
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if (property == border_style_second_theme){
            currentStyleSecondTheme["QMainWindow"]["QMainWindow"]["border-style"] = types.at(value);
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        }

        updateCurrentTheme();
    });

    connect(fontManagerTheme, &QtFontPropertyManager::valueChanged,
            this, [=](QtProperty * property, const QFont &value){

        if (property == font_first_theme){
            currentStyleFirstTheme["QLabel"]["QLabel"]["font"] = value.toString();
            stylizer->saveStyleSheetFromQString(THEME_FIRST_PATH, stylizer->styleSheetFromQMap(currentStyleFirstTheme));
        } else if (property == font_second_theme){
            currentStyleSecondTheme["QLabel"]["QLabel"]["font"] = value.toString();
            stylizer->saveStyleSheetFromQString(THEME_SECOND_PATH, stylizer->styleSheetFromQMap(currentStyleSecondTheme));
        }

        updateCurrentTheme();
    });

    browser->addProperty(task1);
    ui->gridLayout_2->addWidget(browser /*widget*/, 0 /*row*/, 0 /*column*/, 1 /*rowspan*/, 2 /*colspan*/);
#endif
}

WSettings::~WSettings()
{
    delete stylizer;
    delete ui;
}
