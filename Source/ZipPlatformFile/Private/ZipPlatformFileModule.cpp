#include "ZipPlatformFileModule.h"

#include "ZipPlatformFile.h"

#include <Modules/ModuleInterface.h>
#include <HAL/PlatformFilemanager.h>
#include <IPlatformFilePak.h>

DEFINE_LOG_CATEGORY(LogZipPlatformFile);

class FZipPlatformFileModule : public IModuleInterface
{
public:
    FZipPlatformFileModule()
    {
        //
    }

    virtual ~FZipPlatformFileModule()
    {
        //
    }

public:
    virtual void StartupModule()
    {
        //
    }

    virtual void ShutdownModule()
    {
        //
    }
};

IMPLEMENT_MODULE(FZipPlatformFileModule, ZipPlatformFile);
