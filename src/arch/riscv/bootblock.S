/*
 * Early initialization code for RISC-V
 *
 * Copyright 2013 Google Inc.
 * Copyright 2016 Jonathan Neuschäfer <j.neuschaefer@gmx.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 */

#include <arch/encoding.h>
#include <mcall.h>
#include <bits.h>

.section ".text._start", "ax", %progbits

.globl _stack
.global _estack
.globl _start
_start:



	# N.B. This only works on low 4G of the address space
	# and the stack must be page-aligned.
	la sp, _estack

	# poison the stack
	la t1, _stack
	li t0, 0xdeadbeef
	STORE t0, 0(t1)


  la a0,_etext
  la a1,_data
  la a2,_edata
  bgeu a1,a2,2f
1:
  lw t0,(a0)
  sw t0,(a1)
  addi a0,a0,4
  addi a1,a1,4
  bltu a1,a2,1b
2:

  la a0,_bss
  la a1,_ebss
  bgeu a0,a1,2f
1:
  sw zero,(a0)
  addi a0,a0,4
  bltu a0,a1,1b
2:

  call bootblock_soc_early_init

	# make room for HLS and initialize it
	addi sp, sp, -HLS_SIZE

	// Once again, the docs and toolchain disagree.
	// Rather than get fancy I'll just lock this down
	// until it all stabilizes.
	//csrr a0, mhartid
	csrr a0, 0xf14
	call hls_init

	la t0, trap_entry
	csrw mtvec, t0

	# clear any pending interrupts
	csrwi mip, 0

	# set up the mstatus register for VM
	call mstatus_init
	tail main
