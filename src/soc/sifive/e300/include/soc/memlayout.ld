/*
 * This file is part of the coreboot project.
 *
 * Copyright 2014 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <soc/memlayout.h>

#include <arch/header.ld>

#define RAM_START   0x80000000
#define FLASH_START 0x20400000

SECTIONS
{
    BOOTBLOCK(       FLASH_START, 64K)
    ROMSTAGE ( FLASH_START + 64K, 64K)
    RAMSTAGE (FLASH_START + 128K, 64K)

    SRAM_START          (RAM_START)
    STACK               (RAM_START + 4K, 4K)
    PAGETABLES          (RAM_START + 8K, 4K)
    PRERAM_CBMEM_CONSOLE(RAM_START + 12K, 4K)
    SRAM_END            (RAM_START + 16k)

}
