#include "ZipPlatformFile.h"

#include "ZipPlatformFileModule.h"

#include <Misc/FileHelper.h>

FZipPlatformFile::FZipPlatformFile()
{
    //
}

FZipPlatformFile::~FZipPlatformFile()
{
    //
}

bool FZipPlatformFile::Initialize(IPlatformFile* Inner, const TCHAR* CmdLine)
{
    //
    return false;
}

IPlatformFile* FZipPlatformFile::GetLowerLevel()
{
    return nullptr;
}

void FZipPlatformFile::SetLowerLevel(IPlatformFile* NewLowerLevel)
{
    //
}

const TCHAR* FZipPlatformFile::GetName() const
{
    return TEXT("ZipPlatformFile");
}


bool FZipPlatformFile::FileExists(const TCHAR* Filename)
{
    return false;
}

int64 FZipPlatformFile::FileSize(const TCHAR* Filename)
{
    return 0;
}

bool FZipPlatformFile::DeleteFile(const TCHAR* Filename)
{
    return false;
}

bool FZipPlatformFile::IsReadOnly(const TCHAR* Filename)
{
    return true;
}

bool FZipPlatformFile::MoveFile(const TCHAR* To, const TCHAR* From)
{
    return false;
}

bool FZipPlatformFile::SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue)
{
    return false;
}

FDateTime FZipPlatformFile::GetTimeStamp(const TCHAR* Filename)
{
    return FDateTime::MinValue();
}

void FZipPlatformFile::SetTimeStamp(const TCHAR* Filename, FDateTime DateTime)
{
    //
}

FDateTime FZipPlatformFile::GetAccessTimeStamp(const TCHAR* Filename)
{
    return FDateTime::MinValue();
}

FString FZipPlatformFile::GetFilenameOnDisk(const TCHAR* Filename)
{
    return TEXT("");
}

IFileHandle* FZipPlatformFile::OpenRead(const TCHAR* Filename, bool bAllowWrite /*= false*/)
{
    return nullptr;
}

IFileHandle* FZipPlatformFile::OpenWrite(const TCHAR* Filename, bool bAppend /*= false*/, bool bAllowRead /*= false*/)
{
    return nullptr;
}

bool FZipPlatformFile::DirectoryExists(const TCHAR* Directory)
{
    return false;
}

bool FZipPlatformFile::CreateDirectory(const TCHAR* Directory)
{
    return false;
}

bool FZipPlatformFile::DeleteDirectory(const TCHAR* Directory)
{
    return false;
}

FFileStatData FZipPlatformFile::GetStatData(const TCHAR* FilenameOrDirectory)
{
    return FFileStatData();
}

bool FZipPlatformFile::IterateDirectory(const TCHAR* Directory, FDirectoryVisitor& Visitor)
{
    return false;
}

bool FZipPlatformFile::IterateDirectoryStat(const TCHAR* Directory, FDirectoryStatVisitor& Visitor)
{
    return false;
}

bool FZipPlatformFile::IsMounted(const TCHAR* Filename) const
{
    return false;
}

bool FZipPlatformFile::Mount(const TCHAR* Filename, const TCHAR* Password)
{
    return false;
}

bool FZipPlatformFile::Unmount(const TCHAR* Filename)
{
    return false;
}
