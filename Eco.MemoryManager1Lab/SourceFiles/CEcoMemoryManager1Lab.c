/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoMemoryManager1Lab_623E1838
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoMemoryManager1Lab_623E1838
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IdEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoMemoryManager1Lab.h"
#include "CEcoMemoryAllocator1Lab.h"
#include "CEcoVirtualMemory1Lab.h"

/* Выделяем память под один экземпляр */
CEcoMemoryManager1Lab_623E1838 g_xCEcoMemoryManager1Lab_623E1838 = {0};

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoMemoryManager1Lab
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoMemoryManager1Lab_623E1838_QueryInterface(/* in */ IEcoMemoryManager1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoMemoryManager1) ) {
        *ppv = &pCMe->m_pVTblIMgr;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoMemoryAllocator1) ) {
        *ppv = &pCMe->m_pVTblIMem;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoVirtualMemory1) ) {
        *ppv = &pCMe->m_pVTblIVirtual;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIMgr;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoMemoryManager1Lab
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoMemoryManager1Lab_623E1838_AddRef(/* in */ IEcoMemoryManager1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoMemoryManager1Lab
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoMemoryManager1Lab_623E1838_Release(/* in */ IEcoMemoryManager1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoMemoryManager1Lab_623E1838((IEcoMemoryManager1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoMemoryManager1Lab_623E1838_Init(/* in */ IEcoMemoryManager1Ptr_t me, /* in */ voidptr_t startAddress, /* in */ uint32_t size) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

	pCMe->reservedStart = (LabMemoryBlock *) startAddress;
	pCMe->heapStart = (char_t *) startAddress + pCMe->reservedBlockCount * sizeof(LabMemoryBlock);
	pCMe->heapEnd = (char_t *) startAddress + size;

    pCMe->m_pIMemMgr->pVTbl->Init(pCMe->m_pIMemMgr, startAddress, size);
    pCMe->m_pIMemMgr->pVTbl->QueryInterface(pCMe->m_pIMemMgr, &IID_IEcoMemoryAllocator1, (voidptr_t)&pCMe->m_pIMem);


    return 0;
}

/*
 *
 * <сводка>
 *   Функция get_Status
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
bool_t ECOCALLMETHOD CEcoMemoryManager1Lab_623E1838_get_Status(/* in */ IEcoMemoryManager1Ptr_t me, /* in | out */ ECOMEMORYMANAGER1STATUS* status) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)me;

    /* Проверка указателей */
    if (me == 0 || status == 0) {
        return 0;
    }

    status->lowAddr = (uint32_t)((uint64_t)pCMe->m_pHeapStart);
    status->highAddr = (uint32_t)((uint64_t)pCMe->m_pHeapStart >> 32);
    status->totalSize = pCMe->m_iHeapSize;
    status->freeSize = status->totalSize - pCMe->m_iAllocSize;
    status->usedBlocks = pCMe->m_iBlockNum;

    return 1;
}

/*
 *
 * <сводка>
 *   Функция get_UsedBlocks
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
bool_t ECOCALLMETHOD CEcoMemoryManager1Lab_623E1838_get_UsedBlocks(/* in */ IEcoMemoryManager1Ptr_t me, /* in | out */ ECOMEMORYMANAGER1BLOCK* blocks, /* in | out */ uint32_t* sizeInBlocks) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)me;*/

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoMemoryManager1Lab_623E1838(/*in*/ IEcoMemoryManager1Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    /* Инициализация данных */

	pCMe->reservedBlockCount = 1000;
	pCMe->listStart = NULL;
	pCMe->lastAllocated = NULL;

    return 0;
}

/* Create Virtual Table */
IEcoMemoryManager1VTbl g_x00000000000000000000B00000000101VTbl_623E1838 = {
    CEcoMemoryManager1Lab_623E1838_QueryInterface,
    CEcoMemoryManager1Lab_623E1838_AddRef,
    CEcoMemoryManager1Lab_623E1838_Release,
    CEcoMemoryManager1Lab_623E1838_Init,
    CEcoMemoryManager1Lab_623E1838_get_Status,
    CEcoMemoryManager1Lab_623E1838_get_UsedBlocks
};

/* Create Virtual Table */
IEcoMemoryAllocator1VTbl g_x00000000000000000000B00000000102VTbl_623E1838 = {
    CEcoMemoryAllocator1Lab_623E1838_QueryInterface,
    CEcoMemoryAllocator1Lab_623E1838_AddRef,
    CEcoMemoryAllocator1Lab_623E1838_Release,
    CEcoMemoryAllocator1Lab_623E1838_Alloc,
    CEcoMemoryAllocator1Lab_623E1838_Free,
    CEcoMemoryAllocator1Lab_623E1838_Realloc,
    CEcoMemoryAllocator1Lab_623E1838_Copy,
    CEcoMemoryAllocator1Lab_623E1838_Fill,
    CEcoMemoryAllocator1Lab_623E1838_Compare
};

/* Create Virtual Table */
IEcoVirtualMemory1VTbl g_x00000000000000000000B00000000103VTbl_623E1838 = {
    CEcoVirtualMemory1Lab_623E1838_QueryInterface,
    CEcoVirtualMemory1Lab_623E1838_AddRef,
    CEcoVirtualMemory1Lab_623E1838_Release,
    CEcoVirtualMemory1Lab_623E1838_Init,
    CEcoVirtualMemory1Lab_623E1838_Alloc,
    CEcoVirtualMemory1Lab_623E1838_Free
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoMemoryManager1Lab_623E1838(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoMemoryManager1Ptr_t* ppIMemMgr) {
    CEcoMemoryManager1Lab_623E1838* pCMe = 0;
    int16_t result = -1;
    IEcoInterfaceBus1* pIBus = 0;

    /* Проверка указателей */
    if (ppIMemMgr == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента управления памятью расположенной в области инициализированных данных */
    pCMe = &g_xCEcoMemoryManager1Lab_623E1838;

    /* Проверка счетчика ссылок на компонент */
    if (pCMe->m_cRef == 0 ) {
        /* Установка счетчика ссылок на компонент */
        pCMe->m_cRef = 1;

        /* Сохранение указателя на системный интерфейс */
        pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

        /* Создание таблицы функций интерфейса IEcoMemoryManager1 */
        pCMe->m_pVTblIMgr = &g_x00000000000000000000B00000000101VTbl_623E1838;

        /* Создание таблицы функций интерфейса IEcoMemoryAllocator1 */
        pCMe->m_pVTblIMem = &g_x00000000000000000000B00000000102VTbl_623E1838;

        /* Создание таблицы функций интерфейса IEcoMemoryAllocator1 */
        pCMe->m_pVTblIVirtual = &g_x00000000000000000000B00000000103VTbl_623E1838;

        /* Инициализация данных */
        pCMe->m_iBlockNum = 0;
        pCMe->m_iHeapSize = 0;
        pCMe->m_iAllocSize = 0;
        pCMe->m_pHeapStart = 0;
        pCMe->m_pHeapBreak = 0;
        pCMe->m_pHeapEnd = 0;
        pCMe->m_mutex = 0;

        /* Получение интерфейса управления памятью */
        pCMe->m_pIMemMgr= 0;
        pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (voidptr_t)&pIBus);
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryManager1, (void**) &pCMe->m_pIMemMgr);
        if (result != 0 || pCMe->m_pIMemMgr == 0) {
            /* Возврат в случае ошибки */
            return result;
        }
        /* Получение интерфейса для работы с прошивкой */
        pCMe->m_pIProperty = 0;
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoIPCCMailbox1, 0, &IID_IEcoIPCCMailbox1, (voidptr_t*) &pCMe->m_pIProperty);

    }
    else {
        pCMe->m_cRef++;
    }

    /* Возврат указателя на интерфейс */
    *ppIMemMgr = (IEcoMemoryManager1*)pCMe;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoMemoryManager1Lab_623E1838(/* in */ IEcoMemoryManager1* pIMemMgr) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)pIMemMgr;*/
}
