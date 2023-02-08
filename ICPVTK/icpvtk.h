#ifndef ICPVTK_H
#define ICPVTK_H

#include <QMainWindow>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>


#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);

QT_BEGIN_NAMESPACE
namespace Ui { class ICPVTK; }
QT_END_NAMESPACE

class ICPVTK : public QMainWindow
{
    Q_OBJECT

public:
    ICPVTK(QWidget *parent = nullptr);
    ~ICPVTK();

private:
    Ui::ICPVTK *ui;
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

public slots:
    void createSphere();
    void createCone();
    void createCylinder();
    void createCubic();
};
#endif // ICPVTK_H
