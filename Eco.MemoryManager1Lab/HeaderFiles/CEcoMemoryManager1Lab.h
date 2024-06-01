/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoMemoryManager1Lab
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoMemoryManager1Lab
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_MEMORY_MANAGER_1_LAB_H__
#define __C_ECO_MEMORY_MANAGER_1_LAB_H__

#include "IEcoMemoryManager1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoVirtualMemory1.h"

#include "IdEcoIPCCMailbox1.h"
#include "IEcoIPCCMailbox1BCM283x.h"

typedef struct memory_block_struct {
	char_t *startPtr;
    char_t *endPtr;
    bool_t allocated;
	struct memory_block_struct *next;
	struct memory_block_struct *prev;
} LabMemoryBlock;

typedef struct CEcoMemoryManager1Lab_623E1838 {

    /* Таблица функций интерфейса IEcoMemoryManager1 */
    IEcoMemoryManager1VTbl* m_pVTblIMgr;

    /* Таблица функций интерфейса IEcoMemoryAllocator1 */
    IEcoMemoryAllocator1VTbl* m_pVTblIMem;

    /* Таблица функций интерфейса IEcoVirtualMemory1 */
    IEcoVirtualMemory1VTbl* m_pVTblIVirtual;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Обработчик страничного нарушения PageFault */
    void (*DataAbortHandler)(void);

    /* Интерфейс для работы с зарезервированной памятью */
    IEcoMemoryAllocator1* m_pIBusMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Включаемый интерфейс */
    IEcoMemoryManager1* m_pIMemMgr;
    IEcoMemoryAllocator1* m_pIMem;

    IEcoIPCCMailbox1* m_pIProperty;

    /* Данные экземпляра */
    uint32_t m_iBlockNum;
    uint32_t m_iHeapSize;
    uint32_t m_iAllocSize;
    char_t* m_pHeapStart;
    char_t* m_pHeapBreak;
    char_t* m_pHeapEnd;
    uint8_t m_mutex;

	char_t* heapStart;
	char_t* heapEnd;
	LabMemoryBlock *listStart;
	LabMemoryBlock *lastAllocated;
	LabMemoryBlock *reservedStart;
	size_t reservedBlockCount;

} CEcoMemoryManager1Lab_623E1838, *CEcoMemoryManager1Lab_623E1838Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoMemoryManager1Lab_623E1838(/*in*/ IEcoMemoryManager1Ptr_t me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoMemoryManager1Lab_623E1838(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoMemoryManager1Ptr_t* ppIMemMgr);
/* Удаление */
void ECOCALLMETHOD deleteCEcoMemoryManager1Lab_623E1838(/* in */ IEcoMemoryManager1Ptr_t pIMemMgr);

#endif /* __C_ECO_MEMORY_MANAGER_1_LAB_H__ */
