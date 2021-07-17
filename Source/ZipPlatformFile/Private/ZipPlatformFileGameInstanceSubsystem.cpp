#include "ZipPlatformFileGameInstanceSubsystem.h"

#include "ZipPlatformFile.h"
#include "ZipPlatformFileSettings.h"

#include <HAL/PlatformFilemanager.h>

UZipPlatformFileGameInstanceSubsystem::UZipPlatformFileGameInstanceSubsystem()
    : Super()
    , ZipPlatformFilePtr(nullptr)
{
    //
}

void UZipPlatformFileGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FPlatformFileManager& PlatformFileManagerRef = FPlatformFileManager::Get();

    ZipPlatformFilePtr = MakeUnique<FZipPlatformFile>();
    ZipPlatformFilePtr->Initialize(&PlatformFileManagerRef.GetPlatformFile(), nullptr);

    const UZipPlatformFileSettings* ZipPlatformFileSettingsPtr = GetDefault<UZipPlatformFileSettings>();
    check(ZipPlatformFileSettingsPtr);
    if (ZipPlatformFileSettingsPtr->bSetPlatformFile)
    {
        PlatformFileManagerRef.SetPlatformFile(*ZipPlatformFilePtr.Get());
    }
}

void UZipPlatformFileGameInstanceSubsystem::Deinitialize()
{
    FPlatformFileManager& PlatformFileManagerRef = FPlatformFileManager::Get();

    const UZipPlatformFileSettings* ZipPlatformFileSettingsPtr = GetDefault<UZipPlatformFileSettings>();
    check(ZipPlatformFileSettingsPtr);
    if (ZipPlatformFileSettingsPtr->bSetPlatformFile)
    {
        PlatformFileManagerRef.SetPlatformFile(*ZipPlatformFilePtr->GetLowerLevel());
    }
    ZipPlatformFilePtr = nullptr;

    Super::Deinitialize();
}
