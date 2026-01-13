#include "DicomSeriesLoader.h"
#include <vtkDICOMImageReader.h>
#include <iostream>

bool DicomSeriesLoader::LoadSeries(const std::string& folder)
{
    auto reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetDirectoryName(folder.c_str());
    reader->Update();

    m_volume = reader->GetOutput();

    // 첫 파일에서 메타정보 추출
    OFString file = reader->GetFileName(0);
    DcmFileFormat dcm;
    if (dcm.loadFile(file).good())
    {
        ExtractMetaInfo(dcm.getDataset());
        return true;
    }

    return false;
}

void DicomSeriesLoader::ExtractMetaInfo(DcmDataset* dataset)
{
    OFString str;
    if (dataset->findAndGetOFString(DCM_PatientName, str).good())
        m_info.patientName = str.c_str();
    if (dataset->findAndGetOFString(DCM_PatientID, str).good())
        m_info.patientID = str.c_str();
    if (dataset->findAndGetOFString(DCM_StudyInstanceUID, str).good())
        m_info.studyUID = str.c_str();
    if (dataset->findAndGetOFString(DCM_SeriesInstanceUID, str).good())
        m_info.seriesUID = str.c_str();

    std::cout << "Loaded Patient: " << m_info.patientName << "\n";
}
