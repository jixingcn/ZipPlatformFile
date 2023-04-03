#pragma once

#include "IZipPlatformFile.h"

class FZipPlatformFile : public IZipPlatformFile
{
public:
    FZipPlatformFile();
    virtual ~FZipPlatformFile();

public:
    virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CmdLine) override;
    virtual IPlatformFile* GetLowerLevel() override;
    virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override;
    virtual const TCHAR* GetName() const override;

public:
    using IPlatformFile::IterateDirectory;
    using IPlatformFile::IterateDirectoryRecursively;

public:
    virtual bool FileExists(const TCHAR* Filename) override;
    virtual int64 FileSize(const TCHAR* Filename) override;
    virtual bool DeleteFile(const TCHAR* Filename) override;
    virtual bool IsReadOnly(const TCHAR* Filename) override;
    virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override;
    virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;
    virtual FDateTime GetTimeStamp(const TCHAR* Filename) override;
    virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;
    virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override;
    virtual FString GetFilenameOnDisk(const TCHAR* Filename) override;
    virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;
    virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override;
    virtual bool DirectoryExists(const TCHAR* Directory) override;
    virtual bool CreateDirectory(const TCHAR* Directory) override;
    virtual bool DeleteDirectory(const TCHAR* Directory) override;
    virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;
    virtual void FindFiles(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension) override;
    virtual void FindFilesRecursively(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension) override;
    virtual bool IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor) override;
    virtual bool IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor) override;

public:
    virtual bool IsMounted(const TCHAR* Filename) const override;
    virtual bool Mount(const TCHAR* MountPoint, const TCHAR* Filename, const TCHAR* Password = nullptr) override;
    virtual bool Unmount(const TCHAR* Filename) override;

protected:
    TSharedPtr<class FZipFileHandle> GetZipFileHandle(const TCHAR* Filename, FString& OutZipFilename) const;
    void FindFilesInternal(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension, bool bRecursive) const;

private:
    IPlatformFile* LowerLevelPtr;
    TMap<FString, TSharedPtr<class FZipFileHandle>> ZipFileHandlePtrs;
};
