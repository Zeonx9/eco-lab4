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
 *   Данный исходный код описывает реализацию интерфейсов IEcoMemoryAllocator1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "CEcoMemoryManager1Lab.h"

LabMemoryBlock * firstNotAllocated(LabMemoryBlock * reservedStart, size_t count) {
    LabMemoryBlock *ptr = reservedStart;
    int i;
    for (i = 0; i < count; i++) {
        if (ptr->allocated == 0) {
            return ptr;
        }
        ptr++;
    }
    return NULL;
}

void configureBlock(LabMemoryBlock *block, char_t *start, size_t size, LabMemoryBlock *prev, LabMemoryBlock *next) {
    block->allocated = 1;
    block->startPtr = start;
    block->endPtr = start + size;
    block->prev = prev;
    block->next = next;
}

void * allocBlock(
        size_t size,
        LabMemoryBlock **lastPtr,
        LabMemoryBlock **listStartPtr,
        LabMemoryBlock *reserved,
        size_t blockCount,
        char *heapStart,
        const char *heapEnd
) {
    LabMemoryBlock *listStart = *listStartPtr;
    LabMemoryBlock *current = *lastPtr; // must be not null if list is not empty
    LabMemoryBlock *newBlock;
    char startedAgain = 0;

    if (listStart == NULL) { // list is empty
        if (heapEnd - heapStart > size) { // can allocate
            newBlock = firstNotAllocated(reserved, blockCount);
            if (newBlock == NULL) {
                return NULL;
            }
            configureBlock(newBlock, heapStart, size, NULL, NULL);

            *listStartPtr = newBlock;
            *lastPtr = newBlock;
            return newBlock->startPtr;
        }
        return NULL;
    }

    while (startedAgain == 0 || current != *lastPtr) {
        if (current->next != NULL) { // insertion in the middle
            if (current->next->startPtr - current->endPtr > size) { // can allocate between already allocated
                newBlock = firstNotAllocated(reserved, blockCount);
                if (newBlock == NULL) {
                    return NULL;
                }
                configureBlock(newBlock, current->endPtr, size, current, current->next);
                current->next->prev = newBlock;
                current->next = newBlock;

                *lastPtr = newBlock;
                return newBlock->startPtr;
            } else { // need to go to the next block
                current = current->next;
                continue;
            }
        }

        // at the end of the list
        if (heapEnd - current->endPtr > size) { // can allocate at the end of the list
            newBlock = firstNotAllocated(reserved, blockCount);
            if (newBlock == NULL) {
                return NULL;
            }
            configureBlock(newBlock, current->endPtr, size, current, NULL);
            current->next = newBlock;

            *lastPtr = newBlock;
            return newBlock->startPtr;
        }

        // need to go to the list start
        startedAgain = 1;
        current = listStart; // must not be null
        if (current->startPtr - heapStart > size) { // can allocate before first block
            newBlock = firstNotAllocated(reserved, blockCount);
            if (newBlock == NULL) {
                return NULL;
            }
            configureBlock(newBlock, heapStart, size, NULL, current);
            current->prev = newBlock;

            *lastPtr = newBlock;
            *listStartPtr = newBlock;
            return newBlock->startPtr;
        }
    }
    return NULL;
}

void freeBlock(const char *ptr, LabMemoryBlock **listStartPtr) {
    LabMemoryBlock *memPtr = *listStartPtr;
    if (memPtr->startPtr == ptr) { // freeing first block
        memPtr->allocated = 0;
        if (memPtr->next != NULL) {
            memPtr->next->prev = NULL;
            *listStartPtr = memPtr->next;
        } else {
            *listStartPtr = NULL;
        }
        return;
    }

    while (memPtr != NULL) {
        if (memPtr->startPtr == ptr) {
            memPtr->allocated = 0;
            if (memPtr->next != NULL) {
                memPtr->next->prev = memPtr->prev;
            }
            if (memPtr->prev != NULL) {
                memPtr->prev->next = memPtr->next;
            }
            break;
        }
        memPtr = memPtr->next;
    }
}



/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoMemoryAllocator1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_QueryInterface(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));

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
 *   Функция AddRef для интерфейса IEcoMemoryAllocator1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_AddRef(/* in */ IEcoMemoryAllocator1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));

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
 *   Функция Release для интерфейса IEcoMemoryAllocator1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Release(/* in */ IEcoMemoryAllocator1Ptr_t me) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));

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
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Alloc(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ uint32_t size) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));

	return allocBlock(size, &(pCMe->lastAllocated), &(pCMe->listStart), pCMe->reservedStart, pCMe->reservedBlockCount, pCMe->heapStart, pCMe->heapEnd);
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
void ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Free(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv) {
    CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));
    
	freeBlock((char_t *) pv, &(pCMe->listStart));
}

/*
 *
 * <сводка>
 *   Функция Realloc
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Realloc(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Copy
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Copy(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pvDst, /* in */ voidptr_t pvSrc, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Fill
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void* ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Fill(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pvDst, /* in */ char_t Fill, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Compare
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoMemoryAllocator1Lab_623E1838_Compare(/* in */ IEcoMemoryAllocator1Ptr_t me, /* in */ voidptr_t pv1, /* in */ voidptr_t pv2, /* in */ uint32_t size) {
    /*CEcoMemoryManager1Lab_623E1838* pCMe = (CEcoMemoryManager1Lab_623E1838*)((uint64_t)me - sizeof(voidptr_t));*/

    return 0;
}
