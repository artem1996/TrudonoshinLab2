#include "mkewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MKEWindow w;
    w.show();

    return a.exec();
}
