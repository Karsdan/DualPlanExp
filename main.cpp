#include "applicationwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationWindow w;
    w.setFixedSize(500,500);
    w.show();
    return a.exec();
}
