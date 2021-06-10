#include "ZipPlatformFileGameInstanceSubsystem.h"

#include "ZipPlatformFile.h"

UZipPlatformFileGameInstanceSubsystem::UZipPlatformFileGameInstanceSubsystem()
    : Super()
    , ZipPlatformFilePtr(nullptr)
{
    //
}

void UZipPlatformFileGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    ZipPlatformFilePtr = MakeUnique<FZipPlatformFile>();
}

void UZipPlatformFileGameInstanceSubsystem::Deinitialize()
{
    //
    ZipPlatformFilePtr = nullptr;

    Super::Deinitialize();
}
