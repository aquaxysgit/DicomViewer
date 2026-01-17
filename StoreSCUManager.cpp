#include "StoreSCUManager.h"
#include <dcmtk/dcmnet/scu.h>
#include <dcmtk/dcmdata/dctk.h>
#include <iostream>

bool StoreSCUManager::SendSR(const std::string& filename,
                              const std::string& pacsIP,
                              int pacsPort,
                              const std::string& callingAET,
                              const std::string& calledAET)
{
    DcmSCU scu;
    scu.setAETitle(callingAET.c_str());
    scu.setPeerAETitle(calledAET.c_str());
    scu.setPeerHostName(pacsIP.c_str());
    scu.setPeerPort(pacsPort);

    scu.addPresentationContext(UID_EnhancedSRStorage);

    if (scu.initNetwork().bad()) return false;
    if (scu.negotiateAssociation().bad()) return false;

    DcmFileFormat dcm;
    if (dcm.loadFile(filename.c_str()).bad()) return false;

    OFString sopClass, sopInstance;
    dcm.getDataset()->findAndGetOFString(DCM_SOPClassUID, sopClass);
    dcm.getDataset()->findAndGetOFString(DCM_SOPInstanceUID, sopInstance);

    T_ASC_PresentationContextID presID =
        scu.findPresentationContextID(sopClass.c_str(), "");

    if (presID == 0) return false;

    if (scu.sendSTORERequest(presID, sopInstance.c_str(), dcm.getDataset()).bad())
        return false;

    scu.closeAssociation(DCMSCU_RELEASE_ASSOCIATION);

    std::cout << "SR successfully sent to PACS\n";
    return true;
}
