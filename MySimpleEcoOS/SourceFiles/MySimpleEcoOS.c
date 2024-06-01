/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoVFB1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoMemoryManager1Lab.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IdEcoIPCCMailbox1.h"
#include "IdEcoVFB1.h"

/*
#include "IEcoCGI1.h"
#include "IEcoCGI1VirtualDevice.h"
#include "IEcoCGI1OneWayOutput.h"
*/

/* Начало свободного участка памяти */
extern char_t __heap_start__;

IEcoVFB1* g_pIVFB = 0;

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoMemoryManager1* pIMemMgr = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    /* Указатель на интерфейс для работы c буфером кадров видеоустройства */
    IEcoVFB1* pIVFB = 0;

/*
    IEcoCGI1* pIEcoCGI1 = 0;
    IEcoCGI1VirtualDevice* pIVD = 0;
    IEcoCGI1OneWayOutput* pIOutput = 0;
    ECO_CGI_1_VIEWPORT_POINT_t corner1 = {0};
    ECO_CGI_1_VIEWPORT_POINT_t corner2 = {0};
    ECO_CGI_1_POINT_t point1 = {0};
    ECO_CGI_1_POINT_t line[5] = { {10,10}, {100,100}, {50, 100}, {50,10}, {10,10}};
    ECO_CGI_1_POINT_LIST_t lineList = {5, line};
*/
    uint16_t offset = 0;
    uint16_t x1 = 0;
    uint16_t y1 = 32;
    uint16_t x2 = 70;
    byte_t color = 170; /* 3-3-2 bit RGB */
	char_t* memory;
	char_t* memory2;

    /* Создание экземпляра интерфейсной шины */
    result = GetIEcoComponentFactoryPtr_00000000000000000000000042757331->pVTbl->Alloc(GetIEcoComponentFactoryPtr_00000000000000000000000042757331, 0, 0, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    /* Проверка */
    if (result != 0 && pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с памятью */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMemoryManager1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_0000000000000000000000004D656D31);
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMemoryManager1Lab, (IEcoUnknown*)GetIEcoComponentFactoryPtr_81589BFED0B84B1194524BEE623E1838);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с ящиком прошивки */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIPCCMailbox1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_F10BC39A4F2143CF8A1E104650A2C302);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Запрос расширения интерфейсной шины */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        /* Установка расширения менаджера памяти */
        //pIMemExt->pVTbl->set_Manager(pIMemExt, &CID_EcoMemoryManager1);
        pIMemExt->pVTbl->set_Manager(pIMemExt, &CID_EcoMemoryManager1Lab);
        /* Установка разрешения расширения пула */
        pIMemExt->pVTbl->set_ExpandPool(pIMemExt, 1);
    }

    /* Получение интерфейса управления памятью */
    //pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryManager1, (void**) &pIMemMgr);
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1Lab, 0, &IID_IEcoMemoryManager1, (void**) &pIMemMgr);
    if (result != 0 || pIMemMgr == 0) {
        /* Возврат в случае ошибки */
        return result;
    }

    /* Выделение области памяти 512 КБ */
    pIMemMgr->pVTbl->Init(pIMemMgr, &__heap_start__, 0x080000);


    /* Регистрация статического компонента для работы с VBF */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoVFB1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_939B1DCDB6404F7D9C072291AF252188);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы с видео сервисами VBF */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoVFB1, 0, &IID_IEcoVFB1, (void**) &pIVFB);
    /* Проверка */
    if (result != 0 || pIVFB == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Вывод 1 строки "Эко ОС!!!" - кодовая страница 1251 */
    pIVFB->pVTbl->WriteString(pIVFB, 0, 0, 0, 1, CHARACTER_ATTRIBUTE_FORE_COLOR_YELLOW, "\xdd\xea\xee\x20\xce\xd1\x21\x21\x21", 9);

    /* Рисуем линию - подчеркивание */
    for (offset = x1; offset <= x2; offset++) {
        pIVFB->pVTbl->set_ColorPixel(pIVFB, color, offset, y1);
    }

	result = pIMemMgr->pVTbl->QueryInterface(pIMemMgr, &IID_IEcoMemoryAllocator1, (void **) &pIMem);
	if (result != 0 || pIMem == 0) {
		goto Release;
	}

	memory = (char_t *) pIMem->pVTbl->Alloc(pIMem, 100);
	if (memory != NULL) {
		pIVFB->pVTbl->WriteString(pIVFB, 0, 0, 0, 4, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "first allocation", 16);
	}

	memory2 = (char_t *) pIMem->pVTbl->Alloc(pIMem, 100);
	if (memory2 != NULL) {
		pIVFB->pVTbl->WriteString(pIVFB, 0, 0, 0, 5, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "second allocation", 17);
	}
	if (memory != NULL) {
		pIMem->pVTbl->Free(pIMem, memory);
		pIVFB->pVTbl->WriteString(pIVFB, 0, 0, 0, 6, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "freed first", 12);
	}

	memory = (char_t *) pIMem->pVTbl->Alloc(pIMem, 100);
	if (memory != NULL) {
		pIVFB->pVTbl->WriteString(pIVFB, 0, 0, 0, 7, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "third allocation", 16);
	}

	if (memory > memory2) {
		pIVFB->pVTbl->WriteString(pIVFB, 0, 0, 0, 8, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "third greater than second", 25);
	} else {
		pIVFB->pVTbl->WriteString(pIVFB, 0, 0, 0, 8, CHARACTER_ATTRIBUTE_FORE_COLOR_GREEN, "third less than sencond", 23);
	}
	

    g_pIVFB = pIVFB;

    while(1) {
        asm volatile ("NOP\n\t" ::: "memory");
    }

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение интерфейса VFB */
    if (pIVFB != 0) {
        pIVFB->pVTbl->Release(pIVFB);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

