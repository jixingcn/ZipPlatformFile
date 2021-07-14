#include "ZipPlatformFile.h"

#include "ZipPlatformFileModule.h"
#include "ZipFileHandle.h"

FZipPlatformFile::FZipPlatformFile()
    : LowerLevelPtr(nullptr)
    , ZipFileHandlePtrs()
{
    //
}

FZipPlatformFile::~FZipPlatformFile()
{
    LowerLevelPtr = nullptr;
}

bool FZipPlatformFile::Initialize(IPlatformFile* Inner, const TCHAR* CmdLine)
{
    LowerLevelPtr = Inner;
    return true;
}

IPlatformFile* FZipPlatformFile::GetLowerLevel()
{
    return LowerLevelPtr;
}

void FZipPlatformFile::SetLowerLevel(IPlatformFile* NewLowerLevel)
{
    LowerLevelPtr = NewLowerLevel;
}

const TCHAR* FZipPlatformFile::GetName() const
{
    return TEXT("ZipPlatformFile");
}

bool FZipPlatformFile::FileExists(const TCHAR* Filename)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return FoundZipFileHandlePtr->FileExists(*ZipFilename);

    return (LowerLevelPtr ? LowerLevelPtr->FileExists(Filename) : false);
}

int64 FZipPlatformFile::FileSize(const TCHAR* Filename)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        FoundZipFileHandlePtr->FileSize(*ZipFilename);

    return (LowerLevelPtr ? LowerLevelPtr->FileSize(Filename) : 0);
}

bool FZipPlatformFile::DeleteFile(const TCHAR* Filename)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return false;

    return (LowerLevelPtr ? LowerLevelPtr->DeleteFile(Filename) : false);
}

bool FZipPlatformFile::IsReadOnly(const TCHAR* Filename)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return true;

    return (LowerLevelPtr ? LowerLevelPtr->IsReadOnly(Filename) : false);
}

bool FZipPlatformFile::MoveFile(const TCHAR* To, const TCHAR* From)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(To, ZipFilename))
        return false;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(From, ZipFilename))
        return false;

    return (LowerLevelPtr ? LowerLevelPtr->MoveFile(To, From) : false);
}

bool FZipPlatformFile::SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return false;

    return (LowerLevelPtr ? LowerLevelPtr->SetReadOnly(Filename, bNewReadOnlyValue) : false);
}

FDateTime FZipPlatformFile::GetTimeStamp(const TCHAR* Filename)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return FoundZipFileHandlePtr->GetTimeStamp(*ZipFilename);

    return (LowerLevelPtr ? LowerLevelPtr->GetTimeStamp(Filename) : FDateTime::MinValue());
}

void FZipPlatformFile::SetTimeStamp(const TCHAR* Filename, FDateTime DateTime)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return;

    if (LowerLevelPtr)
        LowerLevelPtr->SetTimeStamp(Filename, DateTime);
}

FDateTime FZipPlatformFile::GetAccessTimeStamp(const TCHAR* Filename)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return FoundZipFileHandlePtr->GetTimeStamp(*ZipFilename);

    return (LowerLevelPtr ? LowerLevelPtr->GetAccessTimeStamp(Filename) : FDateTime::MinValue());
}

FString FZipPlatformFile::GetFilenameOnDisk(const TCHAR* Filename)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return FString(Filename);

    return (LowerLevelPtr ? LowerLevelPtr->GetFilenameOnDisk(Filename) : TEXT(""));
}

IFileHandle* FZipPlatformFile::OpenRead(const TCHAR* Filename, bool bAllowWrite /*= false*/)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return FoundZipFileHandlePtr->OpenRead(*ZipFilename, bAllowWrite);

    return (LowerLevelPtr ? LowerLevelPtr->OpenRead(Filename, bAllowWrite) : nullptr);
}

IFileHandle* FZipPlatformFile::OpenWrite(const TCHAR* Filename, bool bAppend /*= false*/, bool bAllowRead /*= false*/)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Filename, ZipFilename))
        return false;

    return (LowerLevelPtr ? LowerLevelPtr->OpenWrite(Filename, bAppend, bAllowRead) : nullptr);
}

bool FZipPlatformFile::DirectoryExists(const TCHAR* Directory)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Directory, ZipFilename))
        return FoundZipFileHandlePtr->DirectoryExists(*ZipFilename);

    if (!LowerLevelPtr)
        return false;

    return (LowerLevelPtr ? LowerLevelPtr->DirectoryExists(Directory) : false);
}

bool FZipPlatformFile::CreateDirectory(const TCHAR* Directory)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Directory, ZipFilename))
        return false;

    return (LowerLevelPtr ? LowerLevelPtr->CreateDirectory(Directory) : false);
}

bool FZipPlatformFile::DeleteDirectory(const TCHAR* Directory)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Directory, ZipFilename))
        return false;

    return (LowerLevelPtr ? LowerLevelPtr->DeleteDirectory(Directory) : false);
}

FFileStatData FZipPlatformFile::GetStatData(const TCHAR* FilenameOrDirectory)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(FilenameOrDirectory, ZipFilename))
        return FoundZipFileHandlePtr->GetStatData(*ZipFilename);

    return (LowerLevelPtr ? LowerLevelPtr->GetStatData(FilenameOrDirectory) : FFileStatData());
}

bool FZipPlatformFile::IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Directory, ZipFilename))
        return FoundZipFileHandlePtr->IterateDirectory(*ZipFilename, Visitor);

    return (LowerLevelPtr ? LowerLevelPtr->IterateDirectory(Directory, Visitor) : false);
}

bool FZipPlatformFile::IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor)
{
    FString ZipFilename;
    if (TSharedPtr<FZipFileHandle> FoundZipFileHandlePtr = GetZipFileHandle(Directory, ZipFilename))
        return FoundZipFileHandlePtr->IterateDirectoryStat(*ZipFilename, Visitor);

    return (LowerLevelPtr ? LowerLevelPtr->IterateDirectoryStat(Directory, Visitor) : false);
}

bool FZipPlatformFile::IsMounted(const TCHAR* Filename) const
{
    FString TheFilename = Filename;
    FPaths::MakeStandardFilename(TheFilename);

    return ZipFileHandlePtrs.Contains(TheFilename);
}

bool FZipPlatformFile::Mount(const TCHAR* MountPoint, const TCHAR* Filename, const TCHAR* Password /*= nullptr*/)
{
    FString TheFilename = Filename;
    FPaths::MakeStandardFilename(TheFilename);

    if (IsMounted(*TheFilename))
        return false;

    TSharedPtr<FZipFileHandle> ZipFileHandlePtr = MakeShared<FZipFileHandle>(LowerLevelPtr, MountPoint, *TheFilename, Password);
    if (!ZipFileHandlePtr->IsValid())
        return false;

    ZipFileHandlePtrs.Add(TheFilename, ZipFileHandlePtr);
    return true;
}

bool FZipPlatformFile::Unmount(const TCHAR* Filename)
{
    FString TheFilename = Filename;
    FPaths::MakeStandardFilename(TheFilename);

    if (!IsMounted(*TheFilename))
        return false;

    ZipFileHandlePtrs.Remove(TheFilename);
    return true;
}

TSharedPtr<FZipFileHandle> FZipPlatformFile::GetZipFileHandle(const TCHAR* Filename, FString& OutZipFilename) const
{
    for (const TPair<FString, TSharedPtr<FZipFileHandle>>& ZipFileHandlePtr : ZipFileHandlePtrs)
    {
        if (!ZipFileHandlePtr.Value->GetFilename(Filename, OutZipFilename))
            continue;
        return ZipFileHandlePtr.Value;
    }
    return nullptr;
}
