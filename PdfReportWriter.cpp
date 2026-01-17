#include "PdfReportWriter.h"
#include <fstream>

bool PdfReportWriter::WritePDF(const std::string& filename,
                                const PatientInfo& info,
                                const MeasurementResult& result)
{
    std::ofstream pdf(filename, std::ios::binary);
    if (!pdf.is_open()) return false;

    pdf << "%PDF-1.4\n";
    pdf << "1 0 obj<<>>endobj\n";
    pdf << "2 0 obj<< /Length 300 >>stream\n";
    pdf << "BT /F1 18 Tf 72 720 Td\n";
    pdf << "(Samsung Medison Measurement Report) Tj\n";
    pdf << "0 -40 Td (Patient: " << info.patientName << ") Tj\n";
    pdf << "0 -30 Td (Patient ID: " << info.patientID << ") Tj\n";
    pdf << "0 -30 Td (Distance: " << result.distanceMM << " mm) Tj\n";
    pdf << "ET\nendstream\nendobj\n";
    pdf << "3 0 obj<< /Type /Page /Parent 4 0 R /Contents 2 0 R >>endobj\n";
    pdf << "4 0 obj<< /Type /Pages /Kids [3 0 R] /Count 1 >>endobj\n";
    pdf << "5 0 obj<< /Type /Catalog /Pages 4 0 R >>endobj\n";
    pdf << "xref\n0 6\n0000000000 65535 f\n";
    pdf << "trailer<< /Root 5 0 R /Size 6 >>\nstartxref\n%%EOF";

    pdf.close();
    std::cout << "PDF Report generated\n";
    return true;
}
