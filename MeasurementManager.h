#pragma once
#include <vtkSmartPointer.h>
#include <vtkDistanceWidget.h>
#include <vtkAngleWidget.h>
#include <vtkAreaContourWidget.h>

struct MeasurementResult
{
    double distanceMM = 0.0;
    double angleDeg = 0.0;
    double areaMM2 = 0.0;
};

class MeasurementManager
{
public:
    void Initialize(vtkRenderWindowInteractor* interactor);
    MeasurementResult GetResults() { return m_result; }

private:
    vtkSmartPointer<vtkDistanceWidget> m_distanceWidget;
    vtkSmartPointer<vtkAngleWidget> m_angleWidget;
    vtkSmartPointer<vtkAreaContourWidget> m_areaWidget;

    MeasurementResult m_result;

    static void DistanceCallback(vtkObject*, unsigned long, void*, void*);
};
