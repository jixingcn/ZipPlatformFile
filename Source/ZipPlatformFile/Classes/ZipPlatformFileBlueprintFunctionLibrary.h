#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>
#include "ZipPlatformFileBlueprintFunctionLibrary.generated.h"

UCLASS()
class ZIPPLATFORMFILE_API UZipPlatformFileBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /// Check the mount status of a file
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool IsMounted(UObject* WorldContextObject, const FString& Filename);

    /// Mount a file, you need pass the password if the file was encrypt
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool Mount(UObject* WorldContextObject, const FString& MountPoint, const FString& Filename, const FString& Password);
    
    /// Unmount the file and free the memory
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool Unmount(UObject* WorldContextObject, const FString& Filename);

    /// Check the status of a file in your zip files
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool FileExists(UObject* WorldContextObject, const FString& Filename);

    /// Check the status of a directory in your zip files
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool DirectoryExists(UObject* WorldContextObject, const FString& Directory);

    /// Find all files by `IZipPlatformFile`
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static void FindFiles(UObject* WorldContextObject, TArray<FString>& FoundFiles, FString Directory, FString FileExtension, bool bRecursive = true);

    /// Find all directories by `IZipPlatformFile`
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static void FindDirectories(UObject* WorldContextObject, TArray<FString>& FoundDirectories, FString Directory);

    /// Get the status of file or directory
    static bool GetFileStatData(UObject* WorldContextObject, const FString& FilenameOrDirectory, struct FFileStatData& OutFileStatData);
    
    /// Get the creation and access times of file or directory
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool GetTimeStamp(UObject* WorldContextObject, const FString& FilenameOrDirectory, FDateTime& OutCreationTime, FDateTime& OutAccessTimeStamp);

    /// Load a file to array from your zip files
    static bool LoadFileToArray(UObject* WorldContextObject, const FString& Filename, TArray<uint8>& Result);

    /// Load a file to string from your zip files
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool LoadFileToString(UObject* WorldContextObject, const FString& Filename, FString& Result);
};
