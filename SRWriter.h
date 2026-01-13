#pragma once
#include "DicomSeriesLoader.h"
#include "MeasurementManager.h"
#include <string>

class SRWriter
{
public:
    void WriteSR(const std::string& filename,
                 const PatientInfo& info,
                 const MeasurementResult& result);
};
