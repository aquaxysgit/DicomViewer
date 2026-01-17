#include "DicomSeriesLoader.h"
#include "Viewer3D.h"
#include "SRWriter.h"
#include "StoreSCUManager.h"
#include "PdfReportWriter.h"
#include <iostream>

int main()
{
    std::cout << "=== DICOM Viewer REV.1 ===\n";

    // 1. Load DICOM
    DicomSeriesLoader loader;
    if (!loader.LoadSeries("DICOM_SERIES_FOLDER"))
    {
        std::cout << "DICOM Load Failed\n";
        return -1;
    }

    // 2. Viewer + Measurement
    Viewer3D viewer;
    viewer.Initialize(loader.GetVolume());
    viewer.Start();
    MeasurementResult result = viewer.GetMeasurement();

    // 3. Write SR
    SRWriter srWriter;
    srWriter.WriteSR("Measurement_SR.dcm",
                     loader.GetPatientInfo(),
                     result);

    // 4. Send SR to PACS
    StoreSCUManager scu;
    scu.SendSR("Measurement_SR.dcm",
               "127.0.0.1",   // PACS IP
               104,           // Port
               "MEDISON_AE",  // Calling AE
               "PACS_AE");    // Called AE

    // 5. Write PDF Report
    PdfReportWriter pdf;
    pdf.WritePDF("Measurement_Report.pdf",
                 loader.GetPatientInfo(),
                 result);

    std::cout << "REV.1 Workflow Complete\n";
    return 0;
}
