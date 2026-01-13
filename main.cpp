#include "DicomSeriesLoader.h"
#include "Viewer3D.h"
#include "SRWriter.h"
#include <iostream>

int main()
{
    std::cout << "=== Samsung Medison Style DICOM Viewer + SR ===\n";

    DicomSeriesLoader loader;
    if (!loader.LoadSeries("DICOM_SERIES_FOLDER"))
    {
        std::cout << "Failed to load DICOM\n";
        return -1;
    }

    Viewer3D viewer;
    viewer.Initialize(loader.GetVolume());
    viewer.Start();

    MeasurementResult result = viewer.GetMeasurement();

    SRWriter sr;
    sr.WriteSR("Measurement_SR.dcm",
               loader.GetPatientInfo(),
               result);

    std::cout << "SR saved successfully.\n";
    return 0;
}
