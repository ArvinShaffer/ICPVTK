#include "icpvtk.h"
#include "ui_icpvtk.h"

ICPVTK::ICPVTK(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ICPVTK)
{
    ui->setupUi(this);
    QObject::connect(ui->actionSphere, &QAction::triggered, this, &ICPVTK::createSphere);
    QObject::connect(ui->actionCone, &QAction::triggered, this, &ICPVTK::createCone);
    QObject::connect(ui->actionCylinder, &QAction::triggered, this, &ICPVTK::createCylinder);
    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("ICPVTK");
    setCentralWidget(ui->openGLWidget);
    ui->openGLWidget->setRenderWindow(renderWindow);
}

void ICPVTK::createSphere()
{
    vtkNew<vtkSphereSource> sphereSource;
    vtkNew<vtkPolyDataMapper> sphereMapper;
    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkNew<vtkActor> sphereActor;
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
    renderer->AddActor(sphereActor);
    ui->openGLWidget->update();
}

void ICPVTK::createCylinder()
{
    vtkNew<vtkCylinderSource> cylinderSource;
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinderSource->GetOutputPort());
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
    cylinderActor->SetPosition(1,1,1);
    renderer->AddActor(cylinderActor);
    ui->openGLWidget->update();
}

void ICPVTK::createCone()
{
    vtkNew<vtkConeSource> coneSource;
    vtkNew<vtkPolyDataMapper> coneMapper;
    coneMapper->SetInputConnection(coneSource->GetOutputPort());
    vtkNew<vtkActor> coneActor;
    coneActor->SetMapper(coneMapper);
    coneActor->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());
    coneActor->SetPosition(-1,-1,-1);
    renderer->AddActor(coneActor);
    ui->openGLWidget->update();
}


ICPVTK::~ICPVTK()
{
    delete ui;
}

