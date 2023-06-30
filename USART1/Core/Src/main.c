#include "stm32f4xx.h"
#include <stdint.h>

#define    GPIOAEN     (1U<<0)
#define    PA9MOD      (2U<<18)
#define    PA9AF       (7U<<4)
#define    PA10MOD     (2U<<20)
#define    PA10AF      (7U<<8)
#define    APB2EN      (1U<<4)
#define    USART1_RX   (1U<<2)
#define    USART1EN    (1U<<13)
#define    USART1_TX   (1U<<3)

#define    SR_RXNE     (1U<<5)
#define    SR_TXE      (1U<<7)

#define SYS_FREQ        16000000
#define APB2_CLK        SYS_FREQ

#define UART_BAUDRATE   9600

char c[1000];

void uart1_init(void);
char uart1_read(void);
void uart1_write(int);
void uart_str_wr(char *str);


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void cmd1(void)
{

	 uart_str_wr("AT\n\r");
	 //c = uart1_read();

}

void cmd2(void)
{

	uart_str_wr("AT+CMGF=1\n\r");
	//c = uart1_read();
}

void cmd3(void)
{

	uart_str_wr("AT+CMGL=\"ALL\"\n\r");
	//c = uart1_read();
}


int main()
{
	uart1_init();
	cmd1();
	for (int i = 0; i < 1000000; i++)
				; // Delay for a short period
	cmd2();
	for (int i = 0; i < 1000000; i++)
				; // Delay for a short period
	cmd3();
//        if(int i =0; str[i]!='\0';i++)
//        {
//            c[i] = uart1_read();
//        }

    return 0;
}



void uart1_init(void)
{

    /**Configure uart gpio pin***/
        /*Enable clock access to gpioa */
        RCC->AHB1ENR |= GPIOAEN;

        //Set PA9 mode to alternate function mode/
        GPIOA->MODER  |= PA9MOD;

        //Set PA10 mode to alternate function mode/
        GPIOA->MODER  |= PA10MOD;

        //Set PA9 alternate function type to UART_TX (AF07)/
        GPIOA->AFR[1] |= PA9AF;

        //Set PA10 alternate function type to UART_RX (AF07)/
        GPIOA->AFR[1] |= PA10AF;

        /**Configure uart module ***/
        /*Enable clock access to uart1 */
         RCC->APB2ENR |= APB2EN;

        //Configure baudrate/
        uart_set_baudrate(USART1,APB2_CLK,UART_BAUDRATE);

        //Configure the transfer direction/
        USART1->CR1 |= USART1_TX;

        //Configure the transfer direction/
        USART1->CR1 |= USART1_RX;

        //Enable uart module/
        USART1->CR1 |= USART1EN;

}




static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
    USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}




char uart1_read(void)
{
  //Make sure the transmit data register is empty/
	while(!(USART1->SR & SR_RXNE)){}

  //read to receive data register/
	return USART1->DR;
}



void uart1_write(int ch)
{
  //Make sure the transmit data register is empty/
	while(!(USART1->SR & SR_TXE)){}

  //Write to transmit data register/
	USART1->DR	=  (ch & 0xFF);

	while (1)
	{
		 int i=0;
		 // Check if there is data available to read
		  if (USART1->SR & USART_SR_RXNE)
		  c[i] = USART1->DR & 0xFF; 	    // Read the data

		  // Check if we've reached the end of the buffer
		  if (c[i] == '\0')  // Null-terminate the string
		  {
		      return;
		  }

		 // Increment the buffer index
		 i++;
	}
}

void uart_str_wr(char *str)
{
	for(int i =0; str[i]!='\0';i++)
	{
		uart1_write(str[i]);
	}
}
