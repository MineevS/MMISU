// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTPROPERTYMANAGER_H
#define QTPROPERTYMANAGER_H

#include "qtpropertybrowser.h"

QT_BEGIN_NAMESPACE

class QDate;
class QTime;
class QDateTime;
class QLocale;
class QRegularExpression;

class QtGroupPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtGroupPropertyManager(QObject *parent = 0);
    ~QtGroupPropertyManager();

protected:
    bool hasValue(const QtProperty *property) const override;

    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
};

class QtIntPropertyManagerPrivate;

class QtIntPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtIntPropertyManager(QObject *parent = 0);
    ~QtIntPropertyManager();

    int value(const QtProperty *property) const;
    int minimum(const QtProperty *property) const;
    int maximum(const QtProperty *property) const;
    int singleStep(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, int val);
    void setMinimum(QtProperty *property, int minVal);
    void setMaximum(QtProperty *property, int maxVal);
    void setRange(QtProperty *property, int minVal, int maxVal);
    void setSingleStep(QtProperty *property, int step);
Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);
    void rangeChanged(QtProperty *property, int minVal, int maxVal);
    void singleStepChanged(QtProperty *property, int step);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtIntPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtIntPropertyManager)
#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtIntPropertyManager)
#endif
};

class QtBoolPropertyManagerPrivate;

class QtBoolPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtBoolPropertyManager(QObject *parent = 0);
    ~QtBoolPropertyManager();

    bool value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, bool val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, bool val);
protected:
    QString valueText(const QtProperty *property) const override;
    QIcon valueIcon(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtBoolPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtBoolPropertyManager)

#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtBoolPropertyManager)
#endif
};

class QtDoublePropertyManagerPrivate;

class QtDoublePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtDoublePropertyManager(QObject *parent = 0);
    ~QtDoublePropertyManager();

    double value(const QtProperty *property) const;
    double minimum(const QtProperty *property) const;
    double maximum(const QtProperty *property) const;
    double singleStep(const QtProperty *property) const;
    int decimals(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, double val);
    void setMinimum(QtProperty *property, double minVal);
    void setMaximum(QtProperty *property, double maxVal);
    void setRange(QtProperty *property, double minVal, double maxVal);
    void setSingleStep(QtProperty *property, double step);
    void setDecimals(QtProperty *property, int prec);
Q_SIGNALS:
    void valueChanged(QtProperty *property, double val);
    void rangeChanged(QtProperty *property, double minVal, double maxVal);
    void singleStepChanged(QtProperty *property, double step);
    void decimalsChanged(QtProperty *property, int prec);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtDoublePropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtDoublePropertyManager)

#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtDoublePropertyManager)
#endif
};

class QtStringPropertyManagerPrivate;

class QtStringPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtStringPropertyManager(QObject *parent = 0);
    ~QtStringPropertyManager();

    QString value(const QtProperty *property) const;
    QRegularExpression regExp(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QString &val);
    void setRegExp(QtProperty *property, const QRegularExpression &regExp);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QString &val);
    void regExpChanged(QtProperty *property, const QRegularExpression &regExp);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtStringPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtStringPropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtStringPropertyManager)
#endif
};

class QtDatePropertyManagerPrivate;

class QtDatePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtDatePropertyManager(QObject *parent = 0);
    ~QtDatePropertyManager();

    QDate value(const QtProperty *property) const;
    QDate minimum(const QtProperty *property) const;
    QDate maximum(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, QDate val);
    void setMinimum(QtProperty *property, QDate minVal);
    void setMaximum(QtProperty *property, QDate maxVal);
    void setRange(QtProperty *property, QDate minVal, QDate maxVal);
Q_SIGNALS:
    void valueChanged(QtProperty *property, QDate val);
    void rangeChanged(QtProperty *property, QDate minVal, QDate maxVal);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtDatePropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtDatePropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtDatePropertyManager)
#endif
};

class QtTimePropertyManagerPrivate;

class QtTimePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtTimePropertyManager(QObject *parent = 0);
    ~QtTimePropertyManager();

    QTime value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, QTime val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, QTime val);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtTimePropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtTimePropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtTimePropertyManager)
#endif
};

class QtDateTimePropertyManagerPrivate;

class QtDateTimePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtDateTimePropertyManager(QObject *parent = 0);
    ~QtDateTimePropertyManager();

    QDateTime value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QDateTime &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QDateTime &val);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtDateTimePropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtDateTimePropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtDateTimePropertyManager)
#endif
};

class QtKeySequencePropertyManagerPrivate;

class QtKeySequencePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtKeySequencePropertyManager(QObject *parent = 0);
    ~QtKeySequencePropertyManager();

    QKeySequence value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QKeySequence &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QKeySequence &val);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtKeySequencePropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtKeySequencePropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtKeySequencePropertyManager)
#endif
};

class QtCharPropertyManagerPrivate;

class QtCharPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtCharPropertyManager(QObject *parent = 0);
    ~QtCharPropertyManager();

    QChar value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QChar &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QChar &val);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtCharPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtCharPropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtCharPropertyManager)
#endif
};

class QtEnumPropertyManager;
class QtLocalePropertyManagerPrivate;

class QtLocalePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtLocalePropertyManager(QObject *parent = 0);
    ~QtLocalePropertyManager();

    QtEnumPropertyManager *subEnumPropertyManager() const;

    QLocale value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QLocale &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QLocale &val);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtLocalePropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtLocalePropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtLocalePropertyManager)
#endif
};

class QtPointPropertyManagerPrivate;

class QtPointPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtPointPropertyManager(QObject *parent = 0);
    ~QtPointPropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;

    QPoint value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QPoint &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QPoint &val);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtPointPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtPointPropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtPointPropertyManager)
#endif
};

class QtPointFPropertyManagerPrivate;

class QtPointFPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtPointFPropertyManager(QObject *parent = 0);
    ~QtPointFPropertyManager();

    QtDoublePropertyManager *subDoublePropertyManager() const;

    QPointF value(const QtProperty *property) const;
    int decimals(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QPointF &val);
    void setDecimals(QtProperty *property, int prec);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QPointF &val);
    void decimalsChanged(QtProperty *property, int prec);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtPointFPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtPointFPropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtPointFPropertyManager)
#endif
};

class QtSizePropertyManagerPrivate;

class QtSizePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtSizePropertyManager(QObject *parent = 0);
    ~QtSizePropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;

    QSize value(const QtProperty *property) const;
    QSize minimum(const QtProperty *property) const;
    QSize maximum(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QSize &val);
    void setMinimum(QtProperty *property, const QSize &minVal);
    void setMaximum(QtProperty *property, const QSize &maxVal);
    void setRange(QtProperty *property, const QSize &minVal, const QSize &maxVal);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QSize &val);
    void rangeChanged(QtProperty *property, const QSize &minVal, const QSize &maxVal);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtSizePropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtSizePropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtSizePropertyManager)
#endif
};

class QtSizeFPropertyManagerPrivate;

class QtSizeFPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtSizeFPropertyManager(QObject *parent = 0);
    ~QtSizeFPropertyManager();

    QtDoublePropertyManager *subDoublePropertyManager() const;

    QSizeF value(const QtProperty *property) const;
    QSizeF minimum(const QtProperty *property) const;
    QSizeF maximum(const QtProperty *property) const;
    int decimals(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QSizeF &val);
    void setMinimum(QtProperty *property, const QSizeF &minVal);
    void setMaximum(QtProperty *property, const QSizeF &maxVal);
    void setRange(QtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);
    void setDecimals(QtProperty *property, int prec);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QSizeF &val);
    void rangeChanged(QtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);
    void decimalsChanged(QtProperty *property, int prec);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtSizeFPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtSizeFPropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtSizeFPropertyManager)
#endif
};

class QtRectPropertyManagerPrivate;

class QtRectPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtRectPropertyManager(QObject *parent = 0);
    ~QtRectPropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;

    QRect value(const QtProperty *property) const;
    QRect constraint(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QRect &val);
    void setConstraint(QtProperty *property, const QRect &constraint);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QRect &val);
    void constraintChanged(QtProperty *property, const QRect &constraint);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtRectPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtRectPropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtRectPropertyManager)
#endif
};

class QtRectFPropertyManagerPrivate;

class QtRectFPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtRectFPropertyManager(QObject *parent = 0);
    ~QtRectFPropertyManager();

    QtDoublePropertyManager *subDoublePropertyManager() const;

    QRectF value(const QtProperty *property) const;
    QRectF constraint(const QtProperty *property) const;
    int decimals(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QRectF &val);
    void setConstraint(QtProperty *property, const QRectF &constraint);
    void setDecimals(QtProperty *property, int prec);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QRectF &val);
    void constraintChanged(QtProperty *property, const QRectF &constraint);
    void decimalsChanged(QtProperty *property, int prec);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtRectFPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtRectFPropertyManager)


#if QT_VERSION >= 0x051300
    Q_DISABLE_COPY_MOVE(QtRectFPropertyManager)
#endif
};

class QtEnumPropertyManagerPrivate;

class QtEnumPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtEnumPropertyManager(QObject *parent = 0);
    ~QtEnumPropertyManager();

    int value(const QtProperty *property) const;
    QStringList enumNames(const QtProperty *property) const;
    QMap<int, QIcon> enumIcons(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, int val);
    void setEnumNames(QtProperty *property, const QStringList &names);
    void setEnumIcons(QtProperty *property, const QMap<int, QIcon> &icons);
Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);
    void enumNamesChanged(QtProperty *property, const QStringList &names);
    void enumIconsChanged(QtProperty *property, const QMap<int, QIcon> &icons);
protected:
    QString valueText(const QtProperty *property) const override;
    QIcon valueIcon(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtEnumPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtEnumPropertyManager)


#if QT_VERSION >= 0x051300
     Q_DISABLE_COPY_MOVE(QtEnumPropertyManager)
#endif
};

class QtFlagPropertyManagerPrivate;

class QtFlagPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtFlagPropertyManager(QObject *parent = 0);
    ~QtFlagPropertyManager();

    QtBoolPropertyManager *subBoolPropertyManager() const;

    int value(const QtProperty *property) const;
    QStringList flagNames(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, int val);
    void setFlagNames(QtProperty *property, const QStringList &names);
Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);
    void flagNamesChanged(QtProperty *property, const QStringList &names);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtFlagPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtFlagPropertyManager)


#if QT_VERSION >= 0x051300
     Q_DISABLE_COPY_MOVE(QtFlagPropertyManager)
#endif
};

class QtSizePolicyPropertyManagerPrivate;

class QtSizePolicyPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtSizePolicyPropertyManager(QObject *parent = 0);
    ~QtSizePolicyPropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;
    QtEnumPropertyManager *subEnumPropertyManager() const;

    QSizePolicy value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QSizePolicy &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QSizePolicy &val);
protected:
    QString valueText(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtSizePolicyPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtSizePolicyPropertyManager)

#if QT_VERSION >= 0x051300
     Q_DISABLE_COPY_MOVE(QtSizePolicyPropertyManager)
#endif
};

class QtFontPropertyManagerPrivate;

class QtFontPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtFontPropertyManager(QObject *parent = 0);
    ~QtFontPropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;
    QtEnumPropertyManager *subEnumPropertyManager() const;
    QtBoolPropertyManager *subBoolPropertyManager() const;

    QFont value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QFont &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QFont &val);
protected:
    QString valueText(const QtProperty *property) const override;
    QIcon valueIcon(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtFontPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtFontPropertyManager)


#if QT_VERSION >= 0x051300
      Q_DISABLE_COPY_MOVE(QtFontPropertyManager)
#endif
};

class QtColorPropertyManagerPrivate;

class QtColorPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtColorPropertyManager(QObject *parent = 0);
    ~QtColorPropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;

    QColor value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QColor &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QColor &val);
protected:
    QString valueText(const QtProperty *property) const override;
    QIcon valueIcon(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtColorPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtColorPropertyManager)


#if QT_VERSION >= 0x051300
      Q_DISABLE_COPY_MOVE(QtColorPropertyManager)
#endif
};

class QtCursorPropertyManagerPrivate;

class QtCursorPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtCursorPropertyManager(QObject *parent = 0);
    ~QtCursorPropertyManager();

#ifndef QT_NO_CURSOR
    QCursor value(const QtProperty *property) const;
#endif

public Q_SLOTS:
    void setValue(QtProperty *property, const QCursor &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QCursor &val);
protected:
    QString valueText(const QtProperty *property) const override;
    QIcon valueIcon(const QtProperty *property) const override;
    void initializeProperty(QtProperty *property) override;
    void uninitializeProperty(QtProperty *property) override;
private:
    QScopedPointer<QtCursorPropertyManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QtCursorPropertyManager)


#if QT_VERSION >= 0x051300
      Q_DISABLE_COPY_MOVE(QtCursorPropertyManager)
#endif
};

QT_END_NAMESPACE

#endif
