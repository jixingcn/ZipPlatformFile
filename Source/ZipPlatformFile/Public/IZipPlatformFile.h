#pragma once

#include <GenericPlatform/GenericPlatformFile.h>

class ZIPPLATFORMFILE_API IZipPlatformFile : public IPlatformFile
{
public:
    virtual bool IsMounted(const TCHAR* Filename) const = 0;
    virtual bool Mount(const TCHAR* Filename, const TCHAR* Password) = 0;
    virtual bool Unmount(const TCHAR* Filename) = 0;
};
