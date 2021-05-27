#include <QApplication>

#include "./field/hdr/field.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    auto* widget = new QWidget();
    auto* field = new Field(widget, 5, 5);
    widget->show();
    return QApplication::exec();
}
