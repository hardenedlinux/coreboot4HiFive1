/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <program_loading.h>
#include <commonlib/configstring.h>

void main(void)
{
	//uintptr_t base;
	//size_t size;

	console_init();
	//query_mem(configstring(), &base, &size);
	//printk(BIOS_SPEW, "0x%zx bytes of memory at 0x%llx\n", size, base);
	#if CONFIG_SOC_SIFIVE_E300
		((void (*)(void))0x20420000)();
	#else
		run_ramstage();
	#endif
}
