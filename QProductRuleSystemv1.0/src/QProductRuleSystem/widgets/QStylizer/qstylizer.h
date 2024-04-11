#ifndef QSTYLIZER_H
#define QSTYLIZER_H

#include <QString>
#include <QMap>
#include <QRegularExpression>
#include <QFile>
#include <QString>

#include <QDebug>


class QStylizer
{
public:
    QStylizer();
    QStylizer(const QString &style);

    QMap<QString, QMap<QString, QMap<QString, QString>>>& getStyleSheetsQMapRef(){
        return map;
    }

    QString& getStyleSheetsQStringRef(){
        return _style;
    }

    QString& styleSheetFromQMap(QMap<QString, QMap<QString, QMap<QString, QString>>>& map){
        QString result;
        foreach(QString obj, map.keys()){
            QString res;
            foreach(QString type, map[obj].keys()){
                if(!type.compare(obj)){
                    res.append(type);
                } else res.append(type + "#" + obj);
                res.append(" {\n\t");
                foreach(QString property, map[obj][type].keys()){
                    res.append(property + ": " + map[obj][type][property] + ";\n\t");
                }
                res.remove(res.size() - 1, 1);
                res.append("}\n");
            }
            result.append(res);
        }

        _style = std::move(result); // not copy. Move;

        return _style;
    }

    QString& styleSheet(){
        QString result;
        foreach(QString obj, map.keys()){
            QString res;
            foreach(QString type, map[obj].keys()){
                if(!type.compare(obj)){
                    res.append(type);
                } else res.append(type + "#" + obj);
                res.append(" {\n\t");
                foreach(QString property, map[obj][type].keys()){
                    res.append(property + ": " + map[obj][type][property] + ";\n\t");
                }
                res.remove(res.size() - 1, 1);
                res.append("}\n");
            }
            result.append(res);
        }

        _style = std::move(result); // not copy. Move;

        return _style;
    }

    QMap<QString, QMap<QString, QMap<QString, QString>>>& convertStyleSheetQStringToQMapRef() {
        static QRegularExpression regex; // (RCER - Perl-compatible regular expressions)
        /*
            Для статических методов явно требуется задание паттерна (setPattern). Без использования конструктора! [static QRegularExpression regex(\\n) запрещается!]
        */
        regex.setPattern("\\n");
        _style.remove(regex);
#if QT_VERSION <= 0x051500
        auto flagSplitBehavior = QString::SplitBehavior::SkipEmptyParts;
#else
        auto flagSplitBehavior = Qt::SkipEmptyParts;
#endif

        regex.setPattern("(Q|\\*)");
        QStringList list = _style.split(regex, flagSplitBehavior);

        foreach (QString str, list) {
            (str[0] == '#') ? str.push_front('*'): str.push_front('Q'); // str[0].isUpper()

            regex.setPattern("(\\{|\\})");
            QStringList list2 = str.split(regex, flagSplitBehavior);

            // head: regex # | *;
            regex.setPattern("\\#");
            QStringList head = list2[0].split(regex, flagSplitBehavior);
            regex.setPattern("\\s");
            QString name = head.back().remove(regex); // В качестве головы берется последний элемент, а предыдущие элементы используются как дочерние.

            head.pop_back();

            map[name] = QMap<QString, QMap<QString,QString>>();

            QString nn;
            if(head.count() > 0){
                nn = head.first();
                map[name][nn.remove(regex)] = QMap<QString,QString>();
            }else{
                nn = name;
                map[name][nn] = QMap<QString,QString>();
            }

            regex.setPattern("\\;");
            QStringList body = list2[1].split(regex, flagSplitBehavior);

            foreach(QString str, body){
                regex.setPattern("\\:");
                QStringList properties = str.split(regex, flagSplitBehavior);
                regex.setPattern("\\s"); //                                       first(1)                           removeFirst()
                map[name][nn][properties.first().remove(regex)] = (properties.last().at(0) == ' ') ? properties.last().remove(0, 1) : properties.last(); // Вставлять элементы именно через квадратные скобки!; Удаление первого пробела;
            }

            //qDebug() << map[name][nn].keys();
        }

        return map;
    }

    bool saveStyleSheetFromQString(QString stylesheetPath){
        QFile file;
        file.setFileName(stylesheetPath);

        if(!file.exists()) return false;

        // TODO
        // Реализовать проверку наличия/отсутствия тем в путях.

        if(file.open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Text)){
            QTextStream stream(&file);
            stream << _style;
        }

        file.close();

        return true;
    }

    bool saveStyleSheetFromQString(QString styleSheetPath, QString styleSheet){
        QFile file ;//= QFile(styleSheetPath); //"style.css"
        file.setFileName(styleSheetPath);
        if(!file.exists()){
            qDebug() << "Файл не существует!";
            return false;
        }

        if(file.isOpen()) file.close();

        if(!file.open(QFile::WriteOnly | QFile::Truncate)){
            qDebug() << "Ошибка при открытии файла стиля!";
            qDebug() << file.error();
            qDebug() << file.errorString();
            return false;
        }

        QTextStream stream(&file);
        stream << styleSheet;

        file.close(); // Можно и не закрывать явно. т. к. при выходе из области видимости QFile метод close() вызывается его деструктором автоматически.

        return true;
    }

    QString loadStyleSheetFromQString(QString stylesheetPath){
        QFile file;
        file.setFileName(stylesheetPath);
        if(!file.exists()) return QString();

        // TODO
        // Реализовать проверку наличия/отсутствия тем в путях.

        if(file.open(QFile::OpenModeFlag::ReadOnly | QFile::OpenModeFlag::Text)){
            _style = file.readAll();
        }

        file.close();

        return _style;
    }

private:
    //     obj       head(type)   body(property value)
    QMap<QString, QMap<QString, QMap<QString, QString>>> map;

    QString _style;
};

#endif // QSTYLIZER_H
