#ifndef _BT_API_H_
#define _BT_API_H_

#include "bt_types.h"


extern BT_HANDLE BT_Open(const BT_i8 *name, const BT_i8 *mode, BT_ERROR *pError);
extern BT_ERROR BT_CloseHandle(BT_HANDLE h);

extern void *BT_kMalloc(BT_u32 size);
extern void BT_kFree(void *ptr);
extern void BT_kPrint(const char *fmt, ...);


extern BT_s32 BT_AllocFileDescriptor();
extern BT_ERROR BT_FreeFileDescriptor();
extern BT_ERROR BT_SetFileDescriptor(BT_u32 n, BT_HANDLE h);
extern BT_HANDLE BT_GetFileDescriptor(BT_u32 n, BT_ERROR *pError);
#endif
