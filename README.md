# ZipPlatformFile

## About

Allow to mount the zip file in memory.
Reference [PakPlatformFile](https://docs.unrealengine.com/en-US/API/Runtime/PakFile/FPakPlatformFile/Mount/index.html).

The plugin use [zlib](https://z-lib.org/) to mount the zip file.

* You must use **UE4 API about file** when you operate the file.
* The plugin **only unzip** the file in memory.
* Support run in blueprint.

## Instruction

```cpp
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

    /// Load a file to array from your zip files
    static bool LoadFileToArray(UObject* WorldContextObject, const FString& Filename, TArray<uint8>& Result);

    /// Load a file to string from your zip files
    UFUNCTION(BlueprintCallable, Category = "ZipPlatformFile", meta = (WorldContext = "WorldContextObject"))
    static bool LoadFileToString(UObject* WorldContextObject, const FString& Filename, FString& Result);
};
```
