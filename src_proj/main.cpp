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

#define vtkSPtr vtkSmartPointer
#define vtkSPtrNew(Var, Type) vtkSPtr<Type> Var = vtkSPtr<Type>::New();
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);

using namespace std;

int main()
{
    // cylinder
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
    cylinder->SetResolution(24);
    vtkSmartPointer<vtkGLTFExporter> gltfexporter = vtkGLTFExporter::New();
    gltfexporter->SetFileName("test.gltf");
    // piechart
    vtkSmartPointer<vtkPieChartActor> pie = vtkPieChartActor::New();
    vtkSmartPointer<vtkActor> actor = vtkActor::New();
    actor->SetMapper(cylinderMapper);
    vtkSmartPointer<vtkRenderer> render = vtkRenderer::New();
    render->AddActor(actor);
    vtkSmartPointer<vtkRenderWindow> win = vtkRenderWindow::New();
    win->AddRenderer(render);
    vtkSmartPointer<vtkRenderWindowInteractor> inter = vtkRenderWindowInteractor::New();
    win->SetInteractor(inter);
    win->Render();
    win->SetSize(800, 600);
    gltfexporter->SetInput(win);
    gltfexporter->Update();
    inter->Start();
    return 0;
}
