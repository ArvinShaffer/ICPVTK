#include "icpvtk.h"
#include "ui_icpvtk.h"
#include "interact.h"

ICPVTK::ICPVTK(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ICPVTK)
{
    ui->setupUi(this);
    QObject::connect(ui->actionCubic, &QAction::triggered, this, &ICPVTK::createCubic);
    QObject::connect(ui->actionSphere, &QAction::triggered, this, &ICPVTK::createSphere);
    QObject::connect(ui->actionCone, &QAction::triggered, this, &ICPVTK::createCone);
    QObject::connect(ui->actionCylinder, &QAction::triggered, this, &ICPVTK::createCylinder);


    QObject::connect(ui->actionPointPicker, &QAction::triggered, this, &ICPVTK::pointPicker);
    QObject::connect(ui->actionMovePoint, &QAction::triggered, this, &ICPVTK::movePoint);

    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("ICPVTK");
    setCentralWidget(ui->openGLWidget);
    ui->openGLWidget->setRenderWindow(renderWindow);
}

void ICPVTK::createCubic()
{
    vtkNew<vtkCubeSource> cubicSource;
    vtkNew<vtkPolyDataMapper> cubicMapper;
    cubicMapper->SetInputConnection(cubicSource->GetOutputPort());
    vtkNew<vtkActor> cubicActor;
    cubicActor->SetMapper(cubicMapper);
    //cubicActor->GetProperty()->SetColor(colors->GetColor3d("SlateGray").GetData());
    cubicActor->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
    renderer->AddActor(cubicActor);
    ui->openGLWidget->update();
}

void ICPVTK::createSphere()
{
    vtkNew<vtkSphereSource> sphereSource;
    vtkNew<vtkPolyDataMapper> sphereMapper;
    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkNew<vtkActor> sphereActor;
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
    sphereActor->SetPosition(2,1,1);
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


void ICPVTK::pointPicker()
{
    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->Update();
    vtkNew<vtkPointPicker> pointPicker;
    // Create a mapper and actor
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("MistyRose").GetData());

    // Create a renderer, render window, and interactor
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("PointPicker");
    this->ui->openGLWidget->interactor()->SetPicker(pointPicker);
    this->ui->openGLWidget->interactor()->SetRenderWindow(renderWindow);
    vtkNew<MouseInteractorStylePP> style;
    this->ui->openGLWidget->interactor()->SetInteractorStyle(style);
    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
    this->ui->openGLWidget->update();
    this->ui->openGLWidget->interactor()->Start();
}


void ICPVTK::movePoint()
{
    vtkNew<vtkPoints> points;
    points->InsertNextPoint(0, 0, 0);
    points->InsertNextPoint(0.1, 0, 0);
    points->InsertNextPoint(0.2, 0, 0);

    vtkNew<vtkPolyData> input;
    input->SetPoints(points);

    vtkNew<vtkSphereSource> glyphSource;
    glyphSource->SetRadius(0.01);
    glyphSource->Update();
    vtkNew<vtkGlyph3D> glyph3D;
    glyph3D->GeneratePointIdsOn();
    glyph3D->SetSourceConnection(glyphSource->GetOutputPort());
    glyph3D->SetInputData(input);
    glyph3D->SetScaleModeToDataScalingOff();
    glyph3D->Update();

    // Create a mapper and actor
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(glyph3D->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

    renderer->AddActor(actor);
    vtkNew<InteractorStyleMoveGlyph> style;
    this->ui->openGLWidget->interactor()->SetRenderWindow(renderWindow);
    this->ui->openGLWidget->interactor()->SetInteractorStyle(style);
    style->Data = input;
    style->GlyphData = glyph3D->GetOutput();

    renderer->GetActiveCamera()->Zoom(0.9);

    this->ui->openGLWidget->update();
    this->ui->openGLWidget->interactor()->Start();
}













