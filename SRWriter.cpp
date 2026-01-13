#include "SRWriter.h"
#include <dcmtk/dcmsr/dsrdoc.h>

void SRWriter::WriteSR(const std::string& filename,
                       const PatientInfo& info,
                       const MeasurementResult& result)
{
    DSRDocument sr;
    sr.createNewDocument(DSRTypes::DT_EnhancedSR);
    sr.getPatientName().putString(info.patientName.c_str());
    sr.getPatientID().putString(info.patientID.c_str());
    sr.getStudyInstanceUID().putString(info.studyUID.c_str());
    sr.getSeriesInstanceUID().putString(info.seriesUID.c_str());

    auto& tree = sr.getTree();

    tree.addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Text);
    tree.getCurrentContentItem().setConceptName(
        DSRCodedEntryValue("112031","DCM","Measurement Report"));

    tree.addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Num);
    tree.getCurrentContentItem().setConceptName(
        DSRCodedEntryValue("121206","DCM","Distance"));
    tree.getCurrentContentItem().setNumericValue(
        DSRNumericValue(result.distanceMM, "mm"));

    sr.writeFile(filename.c_str());
}
