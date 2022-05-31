#include "icpvtk.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ICPVTK w;
    w.show();
    return a.exec();
}
