    .global _ramstage_start
    .section .text
_ramstage_start:
    .incbin "ramstage.bin"
