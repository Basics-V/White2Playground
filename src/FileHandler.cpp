/*
    This file heavily references ds-pokemon-hacking/White2Upgrade.

    A huge thank you to the contributors of ds-pokemon-hacking
    for all of their hard work over the years!
*/
#include "nds/fs.h"

extern "C" {
    b32 ReadDataFromFile(const char* fileName, u32 bufferSize, u8* buffer, u32 offset) {
        FSFile file;
        b32 success;
        finit(&file);
        if (!romfs_fopen(&file, fileName))
            return false;
        if (offset + bufferSize > romfs_fgetsize(&file))
            return false;

        romfs_fseek(&file, offset, IO_SEEK_SET);
        success = romfs_fread(&file, buffer, bufferSize) == bufferSize;
        romfs_fclose(&file);
        return success;
    }

    u32 GetFileSize(const char* fileName) {
        FSFile file;
        finit(&file);
        if (!romfs_fopen(&file, fileName)) {
            return 0;
        }

        u32 size = romfs_fgetsize(&file);

        romfs_fclose(&file);
        return size;
    }
}
