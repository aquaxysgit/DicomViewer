#include "MeasurementManager.h"
#include <vtkDistanceRepresentation2D.h>
#include <vtkCommand.h>
#include <iostream>

void MeasurementManager::Initialize(vtkRenderWindowInteractor* interactor)
{
    m_distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
    m_distanceWidget->SetInteractor(interactor);
    m_distanceWidget->CreateDefaultRepresentation();
    m_distanceWidget->On();

    auto cb = vtkSmartPointer<vtkCallbackCommand>::New();
    cb->SetCallback(DistanceCallback);
    cb->SetClientData(this);
    m_distanceWidget->AddObserver(vtkCommand::InteractionEvent, cb);
}

void MeasurementManager::DistanceCallback(vtkObject* caller,
                                           unsigned long,
                                           void* clientdata,
                                           void*)
{
    auto self = reinterpret_cast<MeasurementManager*>(clientdata);
    auto widget = reinterpret_cast<vtkDistanceWidget*>(caller);
    auto rep = reinterpret_cast<vtkDistanceRepresentation2D*>(widget->GetRepresentation());

    self->m_result.distanceMM = rep->GetDistance();
    std::cout << "[Measurement] Distance = " << self->m_result.distanceMM << " mm\n";
}
