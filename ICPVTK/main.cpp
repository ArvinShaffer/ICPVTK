#include "icpvtk.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    QApplication a(argc, argv);
    ICPVTK w;
    w.show();
    return a.exec();
}
