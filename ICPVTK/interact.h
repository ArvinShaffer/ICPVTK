#ifndef INTERACT_H
#define INTERACT_H

#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPointPicker.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSphereSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkCellPicker.h>
#include <vtkIdTypeArray.h>
#include <vtkGlyph3D.h>
#include <vtkCamera.h>
#include <vtkPointData.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>


namespace {

// Define interaction style
class MouseInteractorStylePP : public vtkInteractorStyleTrackballCamera
{
public:
    static MouseInteractorStylePP* New();
    vtkTypeMacro(MouseInteractorStylePP, vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown() override
    {
        std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0]
                  << " " << this->Interactor->GetEventPosition()[1] << std::endl;
        this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                this->Interactor->GetEventPosition()[1],
                0, // always zero.
                this->Interactor->GetRenderWindow()
                ->GetRenderers()
                ->GetFirstRenderer());
        double picked[3];
        this->Interactor->GetPicker()->GetPickPosition(picked);
        std::cout << "Picked value: " << picked[0] << " " << picked[1] << " "
                  << picked[2] << std::endl;
        // Forward events
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
};
vtkStandardNewMacro(MouseInteractorStylePP);
} // namespace

namespace {

// Define interaction style
class InteractorStyleMoveGlyph : public vtkInteractorStyleTrackballActor
{
public:
  static InteractorStyleMoveGlyph* New();
  vtkTypeMacro(InteractorStyleMoveGlyph, vtkInteractorStyleTrackballActor);

  InteractorStyleMoveGlyph()
  {
    this->MoveSphereSource = vtkSmartPointer<vtkSphereSource>::New();
    this->MoveSphereSource->SetRadius(.01);
    this->MoveSphereSource->Update();

    this->MoveMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    this->MoveMapper->SetInputConnection(
        this->MoveSphereSource->GetOutputPort());

    this->MoveActor = vtkSmartPointer<vtkActor>::New();
    this->MoveActor->SetMapper(this->MoveMapper);
    this->MoveActor->GetProperty()->SetColor(
        this->color->GetColor3d("Pink").GetData());
    // this->MoveActor->VisibilityOff();

    this->Move = false;
  }

  void OnMouseMove() override
  {
    if (!this->Move)
    {
      return;
    }

    vtkInteractorStyleTrackballActor::OnMouseMove();
  }

  void OnMiddleButtonUp() override
  {
    // Forward events
    vtkInteractorStyleTrackballActor::OnMiddleButtonUp();
    this->Move = false;
    this->MoveActor->VisibilityOff();

    this->Data->GetPoints()->SetPoint(this->SelectedPoint,
                                      this->MoveActor->GetPosition());
    this->Data->Modified();
    this->GetCurrentRenderer()->Render();
    this->GetCurrentRenderer()->GetRenderWindow()->Render();
  }
  void OnMiddleButtonDown() override
  {
    // Forward events
    vtkInteractorStyleTrackballActor::OnMiddleButtonDown();
    this->MoveActor->VisibilityOn();
    if (static_cast<vtkCellPicker*>(this->InteractionPicker)->GetPointId() >= 0)
    {
      vtkIdType id =
          dynamic_cast<vtkIdTypeArray*>(
              this->GlyphData->GetPointData()->GetArray("InputPointIds"))
              ->GetValue(static_cast<vtkCellPicker*>(this->InteractionPicker)
                             ->GetPointId());
      std::cout << "Id: " << id << std::endl;
      this->Move = true;
      this->SelectedPoint = id;

      double p[3];
      this->Data->GetPoint(id, p);
      std::cout << "p: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
      this->MoveActor->SetPosition(p);
    }

    this->GetCurrentRenderer()->AddActor(this->MoveActor);
    this->InteractionProp = this->MoveActor;
  }
  vtkNew<vtkNamedColors> color;

  vtkPolyData* Data;
  vtkPolyData* GlyphData;

  vtkSmartPointer<vtkPolyDataMapper> MoveMapper;
  vtkSmartPointer<vtkActor> MoveActor;
  vtkSmartPointer<vtkSphereSource> MoveSphereSource;

  bool Move;
  vtkIdType SelectedPoint;
};
vtkStandardNewMacro(InteractorStyleMoveGlyph);

} // namespace



#endif // INTERACT_H
