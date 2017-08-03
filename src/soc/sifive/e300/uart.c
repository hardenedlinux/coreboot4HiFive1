#include <stdlib.h>
#include <arch/encoding.h>
#include <soc/platform.h>



void uart_init(int idx){
    size_t baud_rate = 115200;

    GPIO_REG(GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
    GPIO_REG(GPIO_IOF_EN) |= IOF0_UART0_MASK;
    UART0_REG(UART_REG_DIV) = get_cpu_freq() / baud_rate - 1;
    UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
}

uint8_t uart_rx_byte(int idx){
    volatile uint32_t * uart_rx = (uint32_t *)(UART0_CTRL_ADDR + UART_REG_RXFIFO);
    volatile uint8_t  * uart_rx_cnt = (uint8_t *)(UART0_CTRL_ADDR + UART_REG_RXCTRL + 2);
    while(*uart_rx_cnt == 0);
    return *uart_rx;
}

void uart_tx_byte(int idx,unsigned char data){
    while(UART0_REG(UART_REG_TXFIFO) & 0x80000000);
    UART0_REG(UART_REG_TXFIFO) = data;
}

void uart_tx_flush(int idx){
  while(UART0_REG(UART_REG_TXFIFO) & 0x80000000);
}

void uart_fill_lb(void *data){
}
