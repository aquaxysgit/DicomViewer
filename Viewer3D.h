#pragma once
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include "MeasurementManager.h"

class Viewer3D
{
public:
    void Initialize(vtkSmartPointer<vtkImageData> volume);
    void Start();
    MeasurementResult GetMeasurement() { return m_measurement.GetResults(); }

private:
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkRenderWindow> m_window;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
    MeasurementManager m_measurement;

    void SetupVolumeRendering(vtkSmartPointer<vtkImageData> volume);
};
