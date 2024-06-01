/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoMemoryManager1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoMemoryManager1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_MEMORY_MANAGER_1_H__
#define __I_ECO_MEMORY_MANAGER_1_H__

#include "IEcoBase1.h"
#include "IEcoMemoryAllocator1.h"

typedef struct ECOMEMORYMANAGER1BLOCK {
    uint32_t lowAddr;
    uint32_t highAddr;
    uint32_t size;
} ECOMEMORYMANAGER1BLOCK;

typedef struct ECOMEMORYMANAGER1STATUS {
    uint32_t lowAddr;
    uint32_t highAddr;
    uint32_t totalSize;
    uint32_t freeSize;
    uint32_t usedBlocks;
} ECOMEMORYMANAGER1STATUS;

/* IEcoMemoryManager1 IID = {00000000-0000-0000-0000-B00000000101} */
#ifndef __IID_IEcoMemoryManager1
static const UGUID IID_IEcoMemoryManager1 = { 0x01, 0x10, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x01, 0x01}};
#endif /* __IID_IEcoMemoryManager1 */

typedef struct IEcoMemoryManager1* IEcoMemoryManager1Ptr_t;

interface IEcoMemoryManager1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoMemoryManager1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoMemoryManager1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoMemoryManager1Ptr_t me);

    /* IEcoMemoryManager1 */
    int16_t (ECOCALLMETHOD *Init)(/* in */ IEcoMemoryManager1Ptr_t me, /* in */ voidptr_t startAddress, /* in */ uint32_t size);
    bool_t (ECOCALLMETHOD *get_Status)(/* in */ IEcoMemoryManager1Ptr_t me, /* in | out */ ECOMEMORYMANAGER1STATUS* status);
    bool_t (ECOCALLMETHOD *get_UsedBlocks)(/* in */ IEcoMemoryManager1Ptr_t me, /* in | out */ ECOMEMORYMANAGER1BLOCK* blocks, /* in | out */ uint32_t* sizeInBlocks);

} IEcoMemoryManager1VTbl, *IEcoMemoryManager1VTblPtr;

typedef struct IEcoMemoryManager1 {
    struct IEcoMemoryManager1VTbl *pVTbl;
} IEcoMemoryManager1;

#endif /* __I_ECO_MEMORY_MANAGER_1_H__ */

