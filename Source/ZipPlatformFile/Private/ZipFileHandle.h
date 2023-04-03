#pragma once

#include "minizip/zip.h"
#include "minizip/unzip.h"
#include <GenericPlatform/GenericPlatformFile.h>

class FZipFileHandle
{
    class FFileHandle : public IFileHandle
    {
        friend FZipFileHandle;

    public:
        explicit FFileHandle();
        virtual ~FFileHandle();

    public:
        virtual int64 Tell() override;
        virtual bool Seek(int64 NewPosition) override;
        virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd = 0) override;
        virtual bool Read(uint8* Destination, int64 BytesToRead) override;
        virtual bool Write(const uint8* Source, int64 BytesToWrite) override;
        virtual bool Flush(const bool bFullFlush = false) override;
        virtual bool Truncate(int64 NewSize) override;

    private:
        TArray64<uint8> UncompressedData;
        int64 CurrentPos;
    };

public:
    explicit FZipFileHandle(IPlatformFile* PlatformFilePtr, const TCHAR* MountPoint, const TCHAR* Filename, const TCHAR* Password = nullptr);
    virtual ~FZipFileHandle();

public:
    FORCEINLINE const FString& GetMountPoint() { return TheMountPoint; }
    FORCEINLINE const FString& GetFilename() { return TheFilename; }
    FORCEINLINE bool IsValid() const { return (ZLibHandle != 0); }
    bool GetFilename(const TCHAR* Filename, FString& OutFilename) const;
    bool GetRelativePath(const TCHAR* Directory, FString& OutRelativePath) const;

public:
    bool FileExists(const TCHAR* Filename) const;
    bool DirectoryExists(const TCHAR* Directory) const;
    int64 FileSize(const TCHAR* Filename) const;
    FDateTime GetTimeStamp(const TCHAR* Filename) const;
    IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false);
    FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) const;
    void FindFiles(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension, bool bRecursive) const;
    bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor);
    bool IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor);

private:
    FString TheMountPoint;
    FString TheFilename;
    FString ThePassword;
    IFileHandle* FileHandlePtr;
    unzFile ZLibHandle;
    struct FZLibFileInfo
    {
        unz_file_info Info;
        unz_file_pos Pos;
        FString ParentDir;
        bool IsDirectory;
        FDateTime GetDateTime() const;
    };
    TMap<FString, FZLibFileInfo> ZLibFileInfoMap;

public:
    static bool GetParentDir(FString& ParentDir, FString FilenameOrDirectory);
    static FString FormatAsDirectoryPath(const TCHAR* Filename);
};
