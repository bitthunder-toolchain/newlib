#ifndef _BITTHUNDER_H_
#define _BITTHUNDER_H_

#include <bt_types.h>

#define BT_FS_MODE_READ				0x01
#define	BT_FS_MODE_WRITE			0x02
#define BT_FS_MODE_APPEND			0x04
#define	BT_FS_MODE_CREATE			0x08
#define BT_FS_MODE_TRUNCATE			0x10

BT_ERROR BT_CloseHandle(BT_HANDLE h);

BT_HANDLE BT_Open(const BT_i8 *name, BT_u32 mode, BT_ERROR *pError);
BT_u32 BT_Read(BT_HANDLE hFile, BT_u32 ulFlags, BT_u32 ulSize, void *pBuffer, BT_ERROR *pError);
BT_u32 BT_Write(BT_HANDLE hFile, BT_u32 ulFlags, BT_u32 ulSize, const void *pBuffer, BT_ERROR *pError);
BT_ERROR BT_Seek(BT_HANDLE hFile, BT_s64 ulOffset, BT_u32 whence);

void *BT_kMalloc(BT_u32 size);
void BT_kFree(void *ptr);
void BT_kPrint(const char *fmt);


BT_s32 BT_AllocFileDescriptor();
BT_ERROR BT_FreeFileDescriptor();
BT_ERROR BT_SetFileDescriptor(BT_u32 n, BT_HANDLE h);
BT_HANDLE BT_GetFileDescriptor(BT_u32 n, BT_ERROR *pError);

BT_s32 BT_GetProcessID(void);

#endif

