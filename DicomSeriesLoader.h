#pragma once
#include <string>
#include <vector>
#include <dcmtk/dcmdata/dctk.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

struct PatientInfo
{
    std::string patientName;
    std::string patientID;
    std::string studyUID;
    std::string seriesUID;
};

class DicomSeriesLoader
{
public:
    bool LoadSeries(const std::string& folder);
    vtkSmartPointer<vtkImageData> GetVolume() { return m_volume; }
    PatientInfo GetPatientInfo() { return m_info; }

private:
    vtkSmartPointer<vtkImageData> m_volume;
    PatientInfo m_info;

    void ExtractMetaInfo(DcmDataset* dataset);
};
