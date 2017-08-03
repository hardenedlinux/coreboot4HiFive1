# 


ifeq ($(CONFIG_SOC_SIFIVE_E300),y)

bootblock-y += uart.c
bootblock-y += clock.c
bootblock-y += rom_media.c

romstage-y  += uart.c
romstage-y  += clock.c
romstage-y  += rom_media.c
romstage-y  += romstage.c

romstage-y  += cbmem.c


ramstage-y  += uart.c
ramstage-y  += clock.c
ramstage-y  += rom_media.c
ramstage-y  += cbmem.c

# CPPFLAGS_common += -Wa,-m32
CPPFLAGS_common += -Isrc/soc/sifive/e300/include
LDFLAGS_common += -m elf32lriscv

endif
