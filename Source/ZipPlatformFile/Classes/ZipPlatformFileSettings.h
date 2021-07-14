#pragma once

#include <UObject/Object.h>
#include "ZipPlatformFileSettings.generated.h"

UCLASS(config = ZipPlatformFileSettings, defaultconfig)
class ZIPPLATFORMFILE_API UZipPlatformFileSettings : public UObject
{
    GENERATED_BODY()

public:
    UZipPlatformFileSettings();

public:
    UPROPERTY(EditAnywhere, Category = "ZipPlatformFile")
    bool bSetPlatformFile;
};
