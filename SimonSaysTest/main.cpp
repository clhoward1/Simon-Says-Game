#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QStyle* style = QStyleFactory::create("windows");
    QApplication a(argc, argv);
    a.setStyle(style);

    MainWindow w;
    w.show();
    return a.exec();
}
