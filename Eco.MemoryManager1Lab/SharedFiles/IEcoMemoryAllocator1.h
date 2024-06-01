/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoMemoryAllocator1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейсов IEcoMemoryAllocator1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_MEMORY_ALLOCATOR_1_H__
#define __I_ECO_MEMORY_ALLOCATOR_1_H__

#include "IEcoBase1.h"

/* IEcoMemoryAllocator1 IID = {00000000-0000-0000-0000-B00000000102} */
#ifndef __IID_IEcoMemoryAllocator1
static const UGUID IID_IEcoMemoryAllocator1 = { 0x01, 0x10, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x01, 0x02} };
#endif /* __IID_IEcoMemoryAllocator1 */

typedef struct IEcoMemoryAllocator1* IEcoMemoryAllocator1Ptr_t;

typedef struct IEcoMemoryAllocator1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ IEcoMemoryAllocator1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ IEcoMemoryAllocator1Ptr_t me);

    /* IEcoMemoryAllocator */
    voidptr_t (ECOCALLMETHOD *Alloc)(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ uint32_t size);
    void (ECOCALLMETHOD *Free)(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv);
    voidptr_t (ECOCALLMETHOD *Realloc)(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv, /* in */ uint32_t size);
    voidptr_t (ECOCALLMETHOD *Copy)(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pvDst, /* in */ voidptr_t pvSrc, /* in */ uint32_t size);
    voidptr_t (ECOCALLMETHOD *Fill)(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pvDst, /* in */ char_t Fill, /* in */ uint32_t size);
    int16_t (ECOCALLMETHOD *Compare)(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv1, /* in */ voidptr_t pv2, /* in */ uint32_t size);
    uint32_t (ECOCALLMETHOD *RetrieveSize)(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv);

} IEcoMemoryAllocator1VTbl, *IEcoMemoryAllocator1VTblPtr;

interface IEcoMemoryAllocator1 {
    struct IEcoMemoryAllocator1VTbl *pVTbl;
} IEcoMemoryAllocator1;

#endif /* __I_ECO_MEMORY_ALLOCATOR_1_H__ */
