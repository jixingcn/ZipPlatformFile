#include "ZipPlatformFileBlueprintFunctionLibrary.h"

#include "ZipPlatformFileGameInstanceSubsystem.h"

namespace ZipPlatformFile
{
    IZipPlatformFile* GetZipPlatformFile(UObject* WorldContextObject)
    {
        checkSlow(WorldContextObject);
        if (!WorldContextObject)
            return nullptr;

        UWorld* WorldPtr = WorldContextObject->GetWorld();
        checkSlow(WorldPtr);
        if (!WorldPtr)
            return nullptr;

        UGameInstance* GameInstancePtr = WorldPtr->GetGameInstance();
        checkSlow(GameInstancePtr);
        if (!GameInstancePtr)
            return nullptr;

        UZipPlatformFileGameInstanceSubsystem* ZipPlatformFileGameInstanceSubsystemPtr = GameInstancePtr->GetSubsystem<UZipPlatformFileGameInstanceSubsystem>();
        checkSlow(ZipPlatformFileGameInstanceSubsystemPtr);
        if (!ZipPlatformFileGameInstanceSubsystemPtr)
            return nullptr;

        return ZipPlatformFileGameInstanceSubsystemPtr->GetZipPlatformFile();
    }
}

bool UZipPlatformFileBlueprintFunctionLibrary::IsMounted(UObject* WorldContextObject, const FString& Filename)
{
    IZipPlatformFile* ZipPlatformFilePtr = ZipPlatformFile::GetZipPlatformFile(WorldContextObject);
    checkSlow(ZipPlatformFilePtr);
    if (!ZipPlatformFilePtr)
        return false;

    return ZipPlatformFilePtr->IsMounted(*Filename);
}

bool UZipPlatformFileBlueprintFunctionLibrary::Mount(UObject* WorldContextObject, const FString& MountPoint, const FString& Filename, const FString& Password)
{
    IZipPlatformFile* ZipPlatformFilePtr = ZipPlatformFile::GetZipPlatformFile(WorldContextObject);
    checkSlow(ZipPlatformFilePtr);
    if (!ZipPlatformFilePtr)
        return false;

    return ZipPlatformFilePtr->Mount(*MountPoint, *Filename, Password.IsEmpty() ? nullptr : *Password);
}

bool UZipPlatformFileBlueprintFunctionLibrary::Unmount(UObject* WorldContextObject, const FString& Filename)
{
    IZipPlatformFile* ZipPlatformFilePtr = ZipPlatformFile::GetZipPlatformFile(WorldContextObject);
    checkSlow(ZipPlatformFilePtr);
    if (!ZipPlatformFilePtr)
        return false;

    return ZipPlatformFilePtr->Unmount(*Filename);
}

bool UZipPlatformFileBlueprintFunctionLibrary::FileExists(UObject* WorldContextObject, const FString& Filename)
{
    return FPaths::FileExists(Filename);
}

bool UZipPlatformFileBlueprintFunctionLibrary::DirectoryExists(UObject* WorldContextObject, const FString& Directory)
{
    return FPaths::DirectoryExists(Directory);
}

bool UZipPlatformFileBlueprintFunctionLibrary::GetFileStatData(UObject* WorldContextObject, const FString& FilenameOrDirectory, FFileStatData& OutFileStatData)
{
    IZipPlatformFile* ZipPlatformFilePtr = ZipPlatformFile::GetZipPlatformFile(WorldContextObject);
    checkSlow(ZipPlatformFilePtr);
    if (!ZipPlatformFilePtr)
        return false;
    if (!ZipPlatformFilePtr->FileExists(*FilenameOrDirectory) && !ZipPlatformFilePtr->DirectoryExists(*FilenameOrDirectory))
        return false;
    OutFileStatData = ZipPlatformFilePtr->GetStatData(*FilenameOrDirectory);
    return true;
}

bool UZipPlatformFileBlueprintFunctionLibrary::GetTimeStamp(UObject* WorldContextObject, const FString& FilenameOrDirectory, FDateTime& OutCreationTime, FDateTime& OutAccessTimeStamp)
{
    FFileStatData FileStatData;
    if (!UZipPlatformFileBlueprintFunctionLibrary::GetFileStatData(WorldContextObject, FilenameOrDirectory, FileStatData))
        return false;
    OutCreationTime = FileStatData.CreationTime;
    OutAccessTimeStamp = FileStatData.AccessTime;
    return true;
}

bool UZipPlatformFileBlueprintFunctionLibrary::LoadFileToArray(UObject* WorldContextObject, const FString& Filename, TArray<uint8>& Result)
{
    return FFileHelper::LoadFileToArray(Result, *Filename);
}

bool UZipPlatformFileBlueprintFunctionLibrary::LoadFileToString(UObject* WorldContextObject, const FString& Filename, FString& Result)
{
    return FFileHelper::LoadFileToString(Result, *Filename);
}

namespace ZipPlatformFile
{
    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileIsMounted(
        TEXT("ZipPlatformFile.IsMounted"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() != 1)
                return;
            UZipPlatformFileBlueprintFunctionLibrary::IsMounted(InWorld, InArgs[0]);
            }),
        ECVF_Cheat);

    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileMount(
        TEXT("ZipPlatformFile.Mount"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() < 2)
                return;
            const FString Password = InArgs.Num() > 2 ? InArgs[2] : TEXT("");
            UZipPlatformFileBlueprintFunctionLibrary::Mount(InWorld, InArgs[0], InArgs[1], Password);
            }),
        ECVF_Cheat);

    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileUnmount(
        TEXT("ZipPlatformFile.Unmount"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() != 1)
                return;
            UZipPlatformFileBlueprintFunctionLibrary::Unmount(InWorld, InArgs[0]);
            }),
        ECVF_Cheat);

    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileFileExists(
        TEXT("ZipPlatformFile.FileExists"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() < 1)
                return;
            UZipPlatformFileBlueprintFunctionLibrary::FileExists(InWorld, InArgs[0]);
            }),
        ECVF_Cheat);

    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileDirectoryExists(
        TEXT("ZipPlatformFile.DirectoryExists"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() < 1)
                return;
            UZipPlatformFileBlueprintFunctionLibrary::DirectoryExists(InWorld, InArgs[0]);
            }),
        ECVF_Cheat);

    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileLoadFileToArray(
        TEXT("ZipPlatformFile.LoadFileToArray"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() < 1)
                return;
            TArray<uint8> Result;
            UZipPlatformFileBlueprintFunctionLibrary::LoadFileToArray(InWorld, InArgs[0], Result);
            }),
        ECVF_Cheat);

    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileLoadFileToString(
        TEXT("ZipPlatformFile.LoadFileToString"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() < 1)
                return;
            FString Result;
            UZipPlatformFileBlueprintFunctionLibrary::LoadFileToString(InWorld, InArgs[0], Result);
            }),
        ECVF_Cheat);

    static FAutoConsoleCommandWithWorldAndArgs CZipPlatformFileGetTimeStampAndStatData(
        TEXT("ZipPlatformFile.GetFileStatData"),
        TEXT(""),
        FConsoleCommandWithWorldAndArgsDelegate::CreateLambda([](const TArray<FString>& InArgs, UWorld* InWorld) {
            if (InArgs.Num() < 1)
                return;

            FFileStatData FileStatData;
            UZipPlatformFileBlueprintFunctionLibrary::GetFileStatData(InWorld, *InArgs[0], FileStatData);
            }),
        ECVF_Cheat);
}
