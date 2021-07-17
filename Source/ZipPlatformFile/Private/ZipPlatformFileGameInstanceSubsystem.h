#pragma once

#include "IZipPlatformFile.h"

#include <Subsystems/GameInstanceSubsystem.h>
#include "ZipPlatformFileGameInstanceSubsystem.generated.h"

UCLASS()
class UZipPlatformFileGameInstanceSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UZipPlatformFileGameInstanceSubsystem();

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

public:
    FORCEINLINE IZipPlatformFile* GetZipPlatformFile() const
    {
        return ZipPlatformFilePtr.Get();
    }

private:
    TUniquePtr<IZipPlatformFile> ZipPlatformFilePtr;
};
