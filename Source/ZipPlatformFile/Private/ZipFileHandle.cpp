#include "ZipFileHandle.h"

FZipFileHandle::FZipFileHandle()
{
    //
}

FZipFileHandle::~FZipFileHandle()
{
    //
}

int64 FZipFileHandle::Tell()
{
    return 0;
}

bool FZipFileHandle::Seek(int64 NewPosition)
{
    return false;
}

bool FZipFileHandle::SeekFromEnd(int64 NewPositionRelativeToEnd /*= 0*/)
{
    return false;
}

bool FZipFileHandle::Read(uint8* Destination, int64 BytesToRead)
{
    return false;
}

bool FZipFileHandle::Write(const uint8* Source, int64 BytesToWrite)
{
    return false;
}

bool FZipFileHandle::Flush(const bool bFullFlush /*= false*/)
{
    return false;
}

bool FZipFileHandle::Truncate(int64 NewSize)
{
    return false;
}

