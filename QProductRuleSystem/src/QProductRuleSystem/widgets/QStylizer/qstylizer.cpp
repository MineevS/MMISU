#include "qstylizer.h"

QStylizer::QStylizer() {

}

QStylizer::QStylizer(const QString& style) {
    _style = style; // ! copy Data;

    convertStyleSheetQStringToQMapRef();
}

