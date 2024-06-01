/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoVirtualMemory1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoVirtualMemory1
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

#ifndef __I_ECO_VIRTUAL_MEMORY_1_H__
#define __I_ECO_VIRTUAL_MEMORY_1_H__

#include "IEcoBase1.h"

/* IEcoVirtualMemory1 IID = {00000000-0000-0000-0000-B00000000103} */
#ifndef __IID_IEcoVirtualMemory1
static const UGUID IID_IEcoVirtualMemory1 = { 0x01, 0x10, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x01, 0x03} };
#endif /* __IID_IEcoVirtualMemory1 */

typedef struct IEcoVirtualMemory1* IEcoVirtualMemory1Ptr_t;

typedef struct IEcoVirtualMemory1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoVirtualMemory1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoVirtualMemory1Ptr_t me);

    /* IEcoVirtualMemory1 */
    int16_t (ECOCALLMETHOD *Init)(/* in */ IEcoVirtualMemory1Ptr_t me);
    voidptr_t (ECOCALLMETHOD *Alloc)(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrVirtual, /* in */ uint32_t size);
    void (ECOCALLMETHOD *Free)(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ voidptr_t pv);

} IEcoVirtualMemory1VTbl, *IEcoVirtualMemory1VTblPtr;

interface IEcoVirtualMemory1 {
    struct IEcoVirtualMemory1VTbl *pVTbl;
} IEcoVirtualMemory1;


#endif /* __I_ECO_VIRTUAL_MEMORY_1_H__ */
