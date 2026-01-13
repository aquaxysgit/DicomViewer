#include "Viewer3D.h"
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>

void Viewer3D::Initialize(vtkSmartPointer<vtkImageData> volume)
{
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_window = vtkSmartPointer<vtkRenderWindow>::New();
    m_window->AddRenderer(m_renderer);
    m_window->SetSize(1280, 900);

    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_interactor->SetRenderWindow(m_window);

    SetupVolumeRendering(volume);

    m_measurement.Initialize(m_interactor);
}

void Viewer3D::SetupVolumeRendering(vtkSmartPointer<vtkImageData> volume)
{
    auto mapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    mapper->SetInputData(volume);

    auto color = vtkSmartPointer<vtkColorTransferFunction>::New();
    color->AddRGBPoint(-1000, 0, 0, 0);
    color->AddRGBPoint(0, 1, 0.8, 0.7);
    color->AddRGBPoint(1000, 1, 1, 1);

    auto opacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
    opacity->AddPoint(-1000, 0.0);
    opacity->AddPoint(0, 0.2);
    opacity->AddPoint(1000, 0.8);

    auto property = vtkSmartPointer<vtkVolumeProperty>::New();
    property->SetColor(color);
    property->SetScalarOpacity(opacity);
    property->ShadeOn();
    property->SetInterpolationTypeToLinear();

    auto volumeActor = vtkSmartPointer<vtkVolume>::New();
    volumeActor->SetMapper(mapper);
    volumeActor->SetProperty(property);

    m_renderer->AddVolume(volumeActor);
    m_renderer->SetBackground(0.05, 0.05, 0.1);
}

void Viewer3D::Start()
{
    m_window->Render();
    m_interactor->Start();
}
