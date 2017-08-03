ENTRY(_start)
SECTIONS
{
    .text 0x20400000 :
    {
        . = 0x00000;
        bootblock-raw.o(.text)
        . = 0x10000;
        romstage-raw.o(.text)
        . = 0x20000;
        ramstage-raw.o(.text)
        . = 0x30000;
        hello-raw.o(.text)
    }
}

