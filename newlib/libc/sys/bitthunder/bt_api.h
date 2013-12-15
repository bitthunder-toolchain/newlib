#ifndef _BT_API_H_
#define _BT_API_H_

#include "bt_types.h"


BT_HANDLE BT_Open(const BT_i8 *name, const BT_i8 *mode, BT_ERROR *pError);
BT_ERROR BT_CloseHandle(BT_HANDLE h);

void *BT_kMalloc(BT_u32 size);
void BT_kFree(void *ptr);
void BT_kPrint(const char *fmt, ...);

BT_ERROR BT_SetFileDescriptor(BT_u32 n, BT_HANDLE h);
BT_HANDLE BT_GetFileDescriptor(BT_u32 n, BT_ERROR *pError);

#endif
