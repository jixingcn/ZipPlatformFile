#pragma once

#include <GenericPlatform/GenericPlatformFile.h>

class FZipFileHandle : public IFileHandle
{
public:
    FZipFileHandle();
    virtual ~FZipFileHandle();

public:
    virtual int64 Tell() override;
    virtual bool Seek(int64 NewPosition) override;
    virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd = 0) override;
    virtual bool Read(uint8* Destination, int64 BytesToRead) override;
    virtual bool Write(const uint8* Source, int64 BytesToWrite) override;
    virtual bool Flush(const bool bFullFlush = false) override;
    virtual bool Truncate(int64 NewSize) override;
};
