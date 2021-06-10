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
    virtual bool IterateDirectory(const TCHAR* Directory, FDirectoryVisitor& Visitor) override;
    virtual bool IterateDirectoryStat(const TCHAR* Directory, FDirectoryStatVisitor& Visitor) override;

public:
    virtual bool IsMounted(const TCHAR* Filename) const override;
    virtual bool Mount(const TCHAR* Filename, const TCHAR* Password) override;
    virtual bool Unmount(const TCHAR* Filename) override;
};