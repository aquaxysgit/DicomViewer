#pragma once
#include <string>

class StoreSCUManager
{
public:
    bool SendSR(const std::string& filename,
                const std::string& pacsIP,
                int pacsPort,
                const std::string& callingAET,
                const std::string& calledAET);
};
