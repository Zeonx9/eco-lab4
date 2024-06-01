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
 *   Данный исходный код описывает реализацию интерфейсов IEcoVirtualMemory1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "CEcoMemoryManager1Lab.h"


/* Начальный адрес виртуальной памяти  */
#define ECO_MMU_VA_START        0xffff000000000000
/* Размер страницы */
#define ECO_MMU_PAGE_SHIFT      12
#define ECO_MMU_PAGE_SIZE       (1 << ECO_MMU_PAGE_SHIFT)
#define ECO_MMU_PAGE_MASK       0xfffffffffffff000
/* Размер секции */
#define ECO_MMU_TABLE_SHIFT     9
#define ECO_MMU_SECTION_SHIFT   (ECO_MMU_PAGE_SHIFT + ECO_MMU_TABLE_SHIFT)
#define ECO_MMU_SECTION_SIZE    (1 << ECO_MMU_SECTION_SHIFT)
/* Память */
#define ECO_MMU_LOW_MEMORY      (2 * ECO_MMU_SECTION_SIZE)
#define ECO_MMU_HIGH_MEMORY     0x3F000000
#define ECO_MMU_PAGING_MEMORY   (ECO_MMU_HIGH_MEMORY - ECO_MMU_LOW_MEMORY)
/* Количество страниц = память / размер страницы */
#define ECO_MMU_PAGING_PAGES    (ECO_MMU_PAGING_MEMORY/ECO_MMU_PAGE_SIZE)
/* Карта пямяти свободных/занятых страниц */
static uint16_t EcoVirtualMemory1Lab_623E1838_MemoryMap [ ECO_MMU_PAGING_PAGES ] = {0,};

extern CEcoMemoryManager1Lab_623E1838 g_xCEcoMemoryManager1Lab_623E1838;

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoVirtualMemory1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_QueryInterface(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2);

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
 *   Функция AddRef для интерфейса IEcoVirtualMemory1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_AddRef(/* in */ IEcoVirtualMemory1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2);

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
 *   Функция Release для интерфейса IEcoVirtualMemory1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Release(/* in */ IEcoVirtualMemory1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2);

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
int16_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Init(/* in */ IEcoVirtualMemory1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2);
    uint32_t buffer[5] = { 0 };

    /* Получение размера памяти  */
    pCMe->m_pIProperty->pVTbl->ProcessingByArgs(pCMe->m_pIProperty, MB_CHANNEL_ARM_PROPERTY_ARM, &buffer[0], 5, MB_CHANNEL_PROPERTY_ARM_GET_VC_MEMORY, 8, 8, 0, 0) ;

    asm volatile (
        "mov x0, 1\n"
        "msr sctlr_el1, x0\n"
        ::: "memory");

    return 0;
}


/*
 *
 * <сводка>
 *   Функция AllocPage
 * </сводка>
 *
 * <описание>
 *   Функция возвращает адрес страницы
 * </описание>
 *
 */
uint64_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_AllocPage(/* in */ IEcoVirtualMemory1Ptr_t me) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2); */
    uint64_t addrPage = 0;
    int16_t index = 0;
    /* Поиск свободных страниц в карте мямяти страниц */
    for (index = 0; index < ECO_MMU_PAGING_PAGES; index++){
        /* Проверка свободной страницы по индексу страницы */
        if (EcoVirtualMemory1Lab_623E1838_MemoryMap[index] == 0){
            /* Выставлем значение 1 - занятая страница */
            EcoVirtualMemory1Lab_623E1838_MemoryMap[index] = 1;
            /* Вычисляем адрес страницы по индексу и размеру страниц */
            addrPage = ECO_MMU_LOW_MEMORY + index*ECO_MMU_PAGE_SIZE;
            /* Заполняем страницу нулями */
            /*pCMe->m_pIMem->pVTbl->Fill(pCMe->m_pIMem, (void*)(addrPage + ECO_MMU_VA_START), 0, ECO_MMU_PAGE_SIZE);*/
            return addrPage;
        }
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция FreePage
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_FreePage(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrPage) {
    /* CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2); */
    /* Вычисляем индекс страницы в карте памяти страниц и выставлем значение 0 - свободная страница */
    EcoVirtualMemory1Lab_623E1838_MemoryMap[(addrPage - ECO_MMU_LOW_MEMORY) / ECO_MMU_PAGE_SIZE] = 0;
}

/*
 *
 * <сводка>
 *   Функция MapTable
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_MapTable(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrVirtual) {
    /* CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2); */
    /* To DO */
}

/*
 *
 * <сводка>
 *   Функция MapPage
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_MapPage(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrVirtual, /* in */ uint64_t addrPage) {
    /* CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2); */
    /* To DO */
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция возвращает адрес страницы
 * </описание>
 *
 */
uint64_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Alloc(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrVirtual) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2); */
    uint64_t addrPage = 0;
    /* Поиск свободных страниц в карте мямяти страниц */
    addrPage = CEcoVirtualMemory1Lab_623E1838_AllocPage(me);
    if (addrPage == 0) {
        return 0;
    }
    /* отображение виртуального адреса на физический */
    CEcoVirtualMemory1Lab_623E1838_MapPage(me, addrVirtual, addrPage);
    return addrPage + ECO_MMU_VA_START;
}

/*
 *
 * <сводка>
 *   Функция Free
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Free(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrPage) {
    /* CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t)*2); */

}

/*
 *
 * <сводка>
 *   Функция PageFault
 * </сводка>
 *
 * <описание>
 *   Функция Обработчик страничного прерывания
 * </описание>
 *
 */
int16_t CEcoVirtualMemory1Lab_623E1838_PageFault(uint64_t addr, uint64_t esr) {
    uint64_t dfs = (esr & 0b111111);
    /* Проверка причины прерывания */
    if ((dfs & 0b111100) == 0b100) {
        uint64_t page = CEcoVirtualMemory1Lab_623E1838_AllocPage((IEcoVirtualMemory1Ptr_t)g_xCEcoMemoryManager1Lab_623E1838.m_pVTblIVirtual);
        if (page == 0) {
            return -1;
        }
        CEcoVirtualMemory1Lab_623E1838_MapPage((IEcoVirtualMemory1Ptr_t)g_xCEcoMemoryManager1Lab_623E1838.m_pVTblIVirtual, addr & ECO_MMU_PAGE_MASK, page);
        return 0;
    }
    return -1;
}