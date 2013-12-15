#include <stdlib.h>
#include "bt_types.h"

#define WEAK	__attribute__((weak))


BT_HANDLE BT_Open(const BT_i8 *name, const BT_i8 *mode, BT_ERROR *pError) WEAK;
BT_HANDLE BT_Open(const BT_i8 *name, const BT_i8 *mode, BT_ERROR *pError) {
	return NULL;
}

BT_ERROR BT_CloseHandle(BT_HANDLE h) WEAK;
BT_ERROR BT_CloseHandle(BT_HANDLE h) {
	return 0;
}

void *BT_kMalloc(BT_u32 size) WEAK;
void *BT_kMalloc(BT_u32 size) {
	return NULL;
}

void BT_kFree(void *ptr) WEAK;
void BT_kFree(void *ptr) {
	return;
}

void BT_kPrint(const char *fmt) WEAK;
void BT_kPrint(const char *fmt) {
#ifndef __thumb__
	__asm ("svc 2");
#endif
}

BT_ERROR BT_SetFileDescriptor(BT_u32 n, BT_HANDLE h) WEAK;
BT_ERROR BT_SetFileDescriptor(BT_u32 n, BT_HANDLE h) {
	return 0;
}

BT_HANDLE BT_GetFileDescriptor(BT_u32 n, BT_ERROR *pError) WEAK;
BT_HANDLE BT_GetFileDescriptor(BT_u32 n, BT_ERROR *pError) {
	return NULL;
}


BT_u32 BT_Read(BT_HANDLE hFile, BT_u32 ulFlags, BT_u32 ulSize, void *pBuffer, BT_ERROR *pError) WEAK;
BT_u32 BT_Read(BT_HANDLE hFile, BT_u32 ulFlags, BT_u32 ulSize, void *pBuffer, BT_ERROR *pError) {
	return 0;
}


BT_u32 BT_Write(BT_HANDLE hFile, BT_u32 ulFlags, BT_u32 ulSize, const void *pBuffer, BT_ERROR *pError) WEAK;
BT_u32 BT_Write(BT_HANDLE hFile, BT_u32 ulFlags, BT_u32 ulSize, const void *pBuffer, BT_ERROR *pError) {
	return 0;
}

BT_ERROR BT_ThreadSleep(BT_u32 ticks) WEAK;
BT_ERROR BT_ThreadSleep(BT_u32 ticks) {
#ifndef __thumb__
	__asm ("svc 3");
#endif
}
