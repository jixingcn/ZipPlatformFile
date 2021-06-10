#include "ZipPlatformFileEdModule.h"

#include "ZipPlatformFileSettings.h"

#include <Modules/ModuleManager.h>
#include <ISettingsModule.h>

DEFINE_LOG_CATEGORY(LogZipPlatformFileEd);

#define LOCTEXT_NAMESPACE "FZipPlatformFileEdModule"

class FZipPlatformFileEdModule : public IModuleInterface
{
public:
    FZipPlatformFileEdModule()
    {
        //
    }

    virtual ~FZipPlatformFileEdModule()
    {
        //
    }

public:
    virtual void StartupModule() override
    {
        if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->RegisterSettings("Project", "Plugins", "ZipPlatformFile",
                LOCTEXT("SettingsName", "ZipPlatformFile"),
                LOCTEXT("SettingsDescription", "Settings of the ZipPlatformFile."),
                GetMutableDefault<UZipPlatformFileSettings>());
        }
    }

    virtual void ShutdownModule() override
    {
        if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
            SettingsModule->UnregisterSettings("Project", "Plugins", "ZipPlatformFile");
        }
    }
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FZipPlatformFileEdModule, ZipPlatformFileEd);
