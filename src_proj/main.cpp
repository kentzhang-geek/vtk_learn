#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPieChartActor.h>
#include <vtkMapper2D.h>
#include <vtkDataSet.h>
#include <vtkCylinderSource.h>
#include <vtkDataArray.h>
#include <vtkGLTFExporter.h>
#include <vtkImageData.h>
#include <vtkCommand.h>
#include <vtkCamera.h>
#include <vtkProperty.h>

#define vtkSPtr vtkSmartPointer
#define vtkSPtrNew(Var, Type) vtkSPtr<Type> Var = vtkSPtr<Type>::New();
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);

using namespace std;

class TestCommand : public vtkCommand {
    void Execute(vtkObject *caller, unsigned long eventId, void *callData) override {
        vtkRenderer * ren = vtkRenderer::SafeDownCast(caller);
        if (ren) {
            std::cout << ren->GetActiveCamera()->GetPosition()[0] << " ";
            std::cout << ren->GetActiveCamera()->GetPosition()[1] << " ";
            std::cout << ren->GetActiveCamera()->GetPosition()[2] << std::endl;
            std::flush(std::cout);
        }
    }
    
};

int main()
{
    // cylinder
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
    cylinder->SetResolution(24);
    // piechart
    vtkSmartPointer<vtkPieChartActor> pie = vtkPieChartActor::New();
    vtkSmartPointer<vtkActor> actor = vtkActor::New();
    actor->SetMapper(cylinderMapper);
    actor->GetProperty()->SetInterpolationToPBR();
    actor->GetProperty()->SetRoughness(0.2);
    actor->GetProperty()->SetMetallic(0.5);
    actor->GetProperty()->SetColor(1, 0.4, 0.2);
    vtkSmartPointer<vtkRenderer> render = vtkRenderer::New();
    render->AddActor(actor);
    vtkSmartPointer<vtkRenderWindow> win = vtkRenderWindow::New();
    win->AddRenderer(render);
    vtkSmartPointer<vtkRenderWindowInteractor> inter = vtkRenderWindowInteractor::New();
    win->SetInteractor(inter);
    win->Render();
    win->SetSize(800, 600);
    TestCommand * tm = new TestCommand;
    render->AddObserver(vtkCommand::StartEvent, tm);
//    render->AddObserver(vtkCommand::StartRotateEvent, tm);
//    actor->AddObserver(vtkCommand::StartRotateEvent, tm);
//    inter->AddObserver(vtkCommand::StartRotateEvent, tm);
//    cylinder->AddObserver(vtkCommand::StartRotateEvent, tm);
//    cylinderMapper->AddObserver(vtkCommand::StartRotateEvent, tm);
    inter->Start();
    return 0;
}
