#include "ZipFileHandle.h"

#include <vector>

namespace ZipPlatformFile
{
    voidpf zlib_open_file(voidpf opaque, const char* filename, int mode)
    {
        if (!opaque)
            return opaque;

        IFileHandle* FileHandlePtr = (IFileHandle*)opaque;
        return FileHandlePtr;
    }

    uLong zlib_read_file(voidpf opaque, voidpf stream, void* buf, uLong size)
    {
        if (!stream)
            return 0;

        IFileHandle* FileHandlePtr = (IFileHandle*)stream;
        const int64 RemainSize = FileHandlePtr->Size() - FileHandlePtr->Tell();
        if (RemainSize <= 0)
            return 0;

        if (size > (uLong)RemainSize)
            size = (uLong)RemainSize;

        if (!FileHandlePtr->Read((uint8*)buf, size))
            return 0;

        return size;
    }

    uLong zlib_write_file(voidpf opaque, voidpf stream, const void* buf, uLong size)
    {
        if (!stream)
            return 0;

        IFileHandle* FileHandlePtr = (IFileHandle*)stream;

        return 0;
    }

    long zlib_tell_file(voidpf opaque, voidpf stream)
    {
        if (!stream)
            return 0;

        IFileHandle* FileHandlePtr = (IFileHandle*)stream;
        return FileHandlePtr->Tell();
    }

    long zlib_seek_file(voidpf opaque, voidpf stream, uLong offset, int origin)
    {
        if (!stream)
            return -1;

        IFileHandle* FileHandlePtr = (IFileHandle*)stream;
        switch (origin)
        {
        case ZLIB_FILEFUNC_SEEK_CUR:
            FileHandlePtr->Seek(FileHandlePtr->Tell() + (int64)offset);
            break;

        case ZLIB_FILEFUNC_SEEK_END:
            FileHandlePtr->SeekFromEnd((int64)offset);
            break;

        case ZLIB_FILEFUNC_SEEK_SET:
            FileHandlePtr->Seek((int64)offset);
            break;
        }

        return 0;
    }

    int zlib_close_file(voidpf opaque, voidpf stream)
    {
        //
        return 0;
    }

    int zlib_testerror_file(voidpf opaque, voidpf stream)
    {
        return 0;
    }
}

FZipFileHandle::FFileHandle::FFileHandle()
    : UncompressedData()
    , CurrentPos(0)
{
    //
}

FZipFileHandle::FFileHandle::~FFileHandle()
{
    //
}

int64 FZipFileHandle::FFileHandle::Tell()
{
    return CurrentPos;
}

bool FZipFileHandle::FFileHandle::Seek(int64 NewPosition)
{
    if (NewPosition < 0 || NewPosition > UncompressedData.Num())
        return false;

    CurrentPos = NewPosition;
    return true;
}

bool FZipFileHandle::FFileHandle::SeekFromEnd(int64 NewPositionRelativeToEnd /*= 0*/)
{
    if (NewPositionRelativeToEnd < 0 || NewPositionRelativeToEnd > UncompressedData.Num())
        return false;

    CurrentPos = UncompressedData.Num() - NewPositionRelativeToEnd;
    return true;
}

bool FZipFileHandle::FFileHandle::Read(uint8* Destination, int64 BytesToRead)
{
    if (BytesToRead <= 0 || (CurrentPos + BytesToRead) > UncompressedData.Num())
        return false;

    FMemory::Memcpy(Destination, &UncompressedData[CurrentPos], BytesToRead);
    CurrentPos += BytesToRead;
    return true;
}

bool FZipFileHandle::FFileHandle::Write(const uint8* Source, int64 BytesToWrite)
{
    /// not support
    return false;
}

bool FZipFileHandle::FFileHandle::Flush(const bool bFullFlush /*= false*/)
{
    /// not support
    return false;
}

bool FZipFileHandle::FFileHandle::Truncate(int64 NewSize)
{
    /// not support
    return false;
}

FZipFileHandle::FZipFileHandle(IPlatformFile* PlatformFilePtr, const TCHAR* MountPoint, const TCHAR* Filename, const TCHAR* Password /*= nullptr*/)
    : TheMountPoint(MountPoint)
    , TheFilename(Filename)
    , ThePassword(Password ? Password : TEXT(""))
    , FileHandlePtr(nullptr)
    , ZLibHandle(0)
    , ZLibFileInfoMap()
{
    if (!PlatformFilePtr)
        return;

    if (!PlatformFilePtr->FileExists(Filename))
        return;

    FileHandlePtr = PlatformFilePtr->OpenRead(Filename);
    if (!FileHandlePtr)
        return;

    if (!TheMountPoint.EndsWith(TEXT("/")))
        TheMountPoint.AppendChar('/');

    zlib_filefunc_def ZLibFileFunc;
    ZLibFileFunc.zopen_file = &ZipPlatformFile::zlib_open_file;
    ZLibFileFunc.zread_file = &ZipPlatformFile::zlib_read_file;
    ZLibFileFunc.zwrite_file = &ZipPlatformFile::zlib_write_file;
    ZLibFileFunc.ztell_file = &ZipPlatformFile::zlib_tell_file;
    ZLibFileFunc.zseek_file = &ZipPlatformFile::zlib_seek_file;
    ZLibFileFunc.zclose_file = &ZipPlatformFile::zlib_close_file;
    ZLibFileFunc.zerror_file = &ZipPlatformFile::zlib_testerror_file;
    ZLibFileFunc.opaque = FileHandlePtr;
    ZLibHandle = unzOpen2(TCHAR_TO_UTF8(Filename), &ZLibFileFunc);
    if (!ZLibHandle)
        return;

    /// scan the zip file
    int32 ZLibRes = unzGoToFirstFile(ZLibHandle);
    while (ZLibRes == UNZ_OK)
    {
        FZLibFileInfo ZLibFileInfo;
        ZLibRes = unzGetCurrentFileInfo(ZLibHandle, &ZLibFileInfo.Info, nullptr, 0, nullptr, 0, nullptr, 0);
        if (ZLibRes != UNZ_OK)
            break;
        if (ZLibFileInfo.Info.size_filename <= 0)
            break;

        std::vector<char> ZLibFilenameTemp;
        ZLibFilenameTemp.resize(ZLibFileInfo.Info.size_filename + 1);
        ZLibFilenameTemp[ZLibFileInfo.Info.size_filename] = '\0';

        ZLibRes = unzGetCurrentFileInfo(ZLibHandle, &ZLibFileInfo.Info, &ZLibFilenameTemp[0], ZLibFileInfo.Info.size_filename, nullptr, 0, nullptr, 0);
        if (ZLibRes != UNZ_OK)
            break;

        ZLibRes = unzGetFilePos(ZLibHandle, &ZLibFileInfo.Pos);
        if (ZLibRes != UNZ_OK)
            break;

        const FString ZLibFilename = UTF8_TO_TCHAR(&ZLibFilenameTemp[0]);
        ZLibFileInfo.IsDirectory = ZLibFilename.EndsWith(TEXT("/"));
        ZLibFileInfoMap.Add(ZLibFilename, ZLibFileInfo);

        ZLibRes = unzGoToNextFile(ZLibHandle);
    }
}

FZipFileHandle::~FZipFileHandle()
{
    if (ZLibHandle)
    {
        unzClose(ZLibHandle);
        ZLibHandle = 0;
    }

    if (FileHandlePtr)
    {
        delete FileHandlePtr;
        FileHandlePtr = nullptr;
    }
}

bool FZipFileHandle::GetFilename(const TCHAR* Filename, FString& OutFilename) const
{
    const FString InputFilename = Filename;
    if (!InputFilename.StartsWith(TheMountPoint, ESearchCase::CaseSensitive))
        return false;

    OutFilename = InputFilename.Mid(TheMountPoint.Len());
    return true;
}

bool FZipFileHandle::FileExists(const TCHAR* Filename) const
{
    return ZLibFileInfoMap.Contains(Filename);
}

bool FZipFileHandle::DirectoryExists(const TCHAR* Directory) const
{
    FString TheDirectory = Directory;
    TheDirectory.ReplaceCharInline('\\', '/', ESearchCase::CaseSensitive);
    if (!TheDirectory.EndsWith(TEXT("/")))
        TheDirectory.Append(TEXT("/"));

    return ZLibFileInfoMap.Contains(Directory);
}

int64 FZipFileHandle::FileSize(const TCHAR* Filename) const
{
    const FZLibFileInfo* ZLibFileInfoPtr = ZLibFileInfoMap.Find(Filename);
    return ZLibFileInfoPtr ? (int64)ZLibFileInfoPtr->Info.uncompressed_size : 0;
}

FDateTime FZipFileHandle::GetTimeStamp(const TCHAR* Filename) const
{
    const FZLibFileInfo* ZLibFileInfoPtr = ZLibFileInfoMap.Find(Filename);
    return ZLibFileInfoPtr ? ZLibFileInfoPtr->GetDateTime() : FDateTime::MinValue();
}

IFileHandle* FZipFileHandle::OpenRead(const TCHAR* Filename, bool bAllowWrite /*= false*/)
{
    const FZLibFileInfo* ZLibFileInfoPtr = ZLibFileInfoMap.Find(Filename);
    if (!ZLibFileInfoPtr)
        return nullptr;

    unz_file_pos TargetPos = ZLibFileInfoPtr->Pos;
    if (unzGoToFilePos(ZLibHandle, &TargetPos) != UNZ_OK)
        return nullptr;

    if ((ThePassword.IsEmpty() && unzOpenCurrentFile(ZLibHandle) != UNZ_OK) ||
        (!ThePassword.IsEmpty() && unzOpenCurrentFilePassword(ZLibHandle, TCHAR_TO_UTF8(*ThePassword)) != UNZ_OK))
        return nullptr;

    FFileHandle* OpenFileHandlePtr = new FFileHandle();
    OpenFileHandlePtr->UncompressedData.SetNumUninitialized((int64)ZLibFileInfoPtr->Info.uncompressed_size);
    if (unzReadCurrentFile(ZLibHandle, &OpenFileHandlePtr->UncompressedData[0], ZLibFileInfoPtr->Info.uncompressed_size) != ZLibFileInfoPtr->Info.uncompressed_size)
    {
        delete OpenFileHandlePtr;
        OpenFileHandlePtr = nullptr;
    }
    unzCloseCurrentFile(ZLibHandle);
    return OpenFileHandlePtr;
}

FFileStatData FZipFileHandle::GetStatData(const TCHAR* FilenameOrDirectory)
{
    const FZLibFileInfo* ZLibFileInfoPtr = ZLibFileInfoMap.Find(FilenameOrDirectory);
    if (!ZLibFileInfoPtr)
        return FFileStatData();

    const FDateTime FileDateTime = ZLibFileInfoPtr->GetDateTime();
    return FFileStatData(FileDateTime, FileDateTime, FileDateTime, (int64)ZLibFileInfoPtr->Info.uncompressed_size, ZLibFileInfoPtr->IsDirectory, true);
}

bool FZipFileHandle::IterateDirectory(const TCHAR* Directory, IPlatformFile::FDirectoryVisitor& Visitor)
{
    //TODO:
    return false;
}

bool FZipFileHandle::IterateDirectoryStat(const TCHAR* Directory, IPlatformFile::FDirectoryStatVisitor& Visitor)
{
    //TODO:
    return false;
}

FDateTime FZipFileHandle::FZLibFileInfo::GetDateTime() const
{
    return FDateTime(
        (int32)Info.tmu_date.tm_year,
        (int32)Info.tmu_date.tm_mon + 1,
        (int32)Info.tmu_date.tm_mday,
        (int32)Info.tmu_date.tm_hour,
        (int32)Info.tmu_date.tm_min,
        (int32)Info.tmu_date.tm_sec
    );
}
