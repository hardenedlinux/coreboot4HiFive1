    .global _romstage_start
    .section .text
_romstage_start:
    .incbin "romstage.bin"
