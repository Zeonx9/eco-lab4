/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoMemoryManager1Lab
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoMemoryManager1Lab
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

#ifndef __ID_ECO_MEMORY_MANAGER_1_LAB_H__
#define __ID_ECO_MEMORY_MANAGER_1_LAB_H__

#include "IEcoBase1.h"
#include "IEcoMemoryManager1.h"

/* EcoMemoryManager1Lab CID = {81589BFE-D0B8-4B11-9452-4BEE623E1838} */
#ifndef __CID_EcoMemoryManager1Lab
static const UGUID CID_EcoMemoryManager1Lab = {0x01, 0x10, {0x81, 0x58, 0x9B, 0xFE, 0xD0, 0xB8, 0x4B, 0x11, 0x94, 0x52, 0x4B, 0xEE, 0x62, 0x3E, 0x18, 0x38} };
#endif /* __CID_EcoMemoryManager1Lab */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_81589BFED0B84B1194524BEE623E1838;
#endif

#endif /* __ID_ECO_MEMORY_MANAGER_1_LAB_H__ */
