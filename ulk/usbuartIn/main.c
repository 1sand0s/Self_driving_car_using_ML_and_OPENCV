#include<ulk.h>
#include"macros.h"
#include <ulk_base_types.h>
#include <ulk_fpga_uart.h>
#include<ulk_fpga_char_lcd.h>
int main(void) PROGRAM_ENTRY;

int main()
{
	ulk_proc_gpio_init();

    //initialzing FPGA UART
	ulk_fpga_uart_init(9600,3); ////Can the input be given at any time?
	//ulk_proc_uart_init(9600,3);

	ulk_cpanel_printf("\n");

    //prepping uart for read
	int cnt =0;
	//char output={'a', 'b', 'c', 'd', 'e'};
	char output = 'a';

	ulk_cpanel_printf("writing...");
	int i =0 ;
	for (i=0; i<10000; i++)
	{
		ulk_cpanel_printf("char output%d: %c \n", i, output);
		ulk_fpga_uart_putc(output);
	}


}

