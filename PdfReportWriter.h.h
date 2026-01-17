#pragma once
#include "DicomSeriesLoader.h"
#include "MeasurementManager.h"
#include <string>

class PdfReportWriter
{
public:
    bool WritePDF(const std::string& filename,
                  const PatientInfo& info,
                  const MeasurementResult& result);
};
