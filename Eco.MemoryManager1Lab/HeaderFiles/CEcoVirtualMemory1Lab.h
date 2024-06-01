/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoVirtualMemory1Lab
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoVirtualMemory1Lab
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_VIRTUAL_MEMORY_1_LAB_H__
#define __C_ECO_VIRTUAL_MEMORY_1_LAB_H__

#include "IEcoBase1.h"

int16_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_QueryInterface(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
uint32_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_AddRef(/* in */ IEcoVirtualMemory1Ptr_t me);
uint32_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Release(/* in */ IEcoVirtualMemory1Ptr_t me);
int16_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Init(/* in */ IEcoVirtualMemory1Ptr_t me);
voidptr_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Alloc(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrVirtual, /* in */ uint32_t size);
void ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Free(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ voidptr_t pv);

#endif /* __C_ECO_VIRTUAL_MEMORY_1_LAB_H__ */
