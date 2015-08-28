#include<ulk.h>
#include"macros.h"
#include <ulk_base_types.h>
#include <ulk_fpga_uart.h>
#include<ulk_fpga_char_lcd.h>
int main(void) PROGRAM_ENTRY;

int main()
{
	ulk_proc_gpio_init();

		 ulk_proc_sys_pad_set_mux_mode (140, 4);
		 ulk_proc_sys_pad_set_mux_mode (141, 4);
		 ulk_proc_sys_pad_set_mux_mode (142, 4);
		 ulk_proc_sys_pad_set_mux_mode (143, 4);
		 ulk_proc_sys_pad_set_mux_mode (158, 4);

		 ulk_proc_gpio_set_dir ( 140, 0);
	 	 ulk_proc_gpio_set_dir ( 141, 0);
	 	 ulk_proc_gpio_set_dir ( 142, 0);
	 	 ulk_proc_gpio_set_dir ( 143, 0);
	 	 ulk_proc_gpio_set_dir ( 158, 0);

	 	 ulk_proc_gpio_set_data_out (158,  0);
	
    //	initialzing FPGA UART
	ulk_fpga_uart_init(9600,3);
	//ulk_proc_uart_init(9600,3);

	ulk_cpanel_printf("\n");

    // 	initializing LCD 
	ulk_fpga_clcd_init ();
	ulk_fpga_clcd_display_on();
   	ulk_fpga_clcd_display_clear();
	ulk_fpga_clcd_display_string("Choose Mode: a/m/t");

    //	prepping uart for read	
	int cnt =0;
	char direction='x';
	char mode='x';

	ulk_cpanel_printf("Reading...");
	ulk_cpanel_printf("Initial Values: %c; %c \n", (char)mode, (char)direction);


	while(1)
	{

        mode=ulk_fpga_uart_getc(3);
		direction=ulk_fpga_uart_getc(3);
        //direction=ulk_proc_uart_getc(3);
        

	    //ulk_cpanel_printf("Loop No: %d\t", cnt++);
		ulk_cpanel_printf("Values read: %c; %c \n", (char)mode, (char)direction);
		ulk_proc_gpio_set_data_out (158,  1);

		if (direction == 's')
		{
    		// lcd panel print
            if(mode == 't')
            {   ulk_fpga_clcd_display_clear();
	            ulk_fpga_clcd_display_string("test - straight");
            }            

            else if(mode == 'a')
            {   ulk_fpga_clcd_display_clear();
	            ulk_fpga_clcd_display_string("auto - straight");
            }            


            // motor action
			ulk_proc_gpio_set_data_out (140,  0);
			ulk_proc_gpio_set_data_out (141,  0);
			ulk_proc_gpio_set_data_out (142 , 1);
			ulk_proc_gpio_set_data_out (143 , 0);
			ulk_proc_delay(ULK_SEC(0.1));


			ulk_proc_gpio_set_data_out (140,  0);
			ulk_proc_gpio_set_data_out (141,  0);
			ulk_proc_gpio_set_data_out (142 , 0);
			ulk_proc_gpio_set_data_out (143 , 0);
			ulk_proc_delay(ULK_SEC(0.3));

		}

		else if(direction == 'l')
		{
            // lcd panel print
            if(mode == 't')
            {   ulk_fpga_clcd_display_clear();
	            ulk_fpga_clcd_display_string("test - left");
            }            

            else if(mode == 'a')
            {   ulk_fpga_clcd_display_clear();
	            ulk_fpga_clcd_display_string("auto - left");
            }            

            // motor action
			ulk_proc_gpio_set_data_out (140 , 1);
			ulk_proc_gpio_set_data_out (141 , 0);
			ulk_proc_gpio_set_data_out (142 , 1);
			ulk_proc_gpio_set_data_out (143 , 0);
			ulk_proc_delay(ULK_SEC(0.1));

			ulk_proc_gpio_set_data_out (140 , 1);
			ulk_proc_gpio_set_data_out (141 , 0);
			ulk_proc_gpio_set_data_out (142 , 0);
			ulk_proc_gpio_set_data_out (143 , 0);
			ulk_proc_delay(ULK_SEC(0.3));

		}
		else if (direction == 'r')
		{
            // lcd panel print
            if(mode == 't')
            {   ulk_fpga_clcd_display_clear();
	            ulk_fpga_clcd_display_string("test - right");
            }            

            else if(mode == 'a')
            {   ulk_fpga_clcd_display_clear();
	            ulk_fpga_clcd_display_string("auto - right");
            }            

            // motor action
			ulk_proc_gpio_set_data_out (140,  0);
			ulk_proc_gpio_set_data_out (141,  1);
			ulk_proc_gpio_set_data_out (142 , 1);
			ulk_proc_gpio_set_data_out (143 , 0);
			ulk_proc_delay(ULK_SEC(0.1));

			ulk_proc_gpio_set_data_out (140,  0);
			ulk_proc_gpio_set_data_out (141,  1);
			ulk_proc_gpio_set_data_out (142 , 0);
			ulk_proc_gpio_set_data_out (143 , 0);
			ulk_proc_delay(ULK_SEC(0.3));

		}

		else if(direction == 'n')
		{
			 if(mode == 'm')
			{   ulk_fpga_clcd_display_clear();
				ulk_fpga_clcd_display_string("man - ***");
			}
		}

	 /* else
		{
			ulk_cpanel_printf("nothing");
		ulk_proc_gpio_set_data_out (140,  0);
		ulk_proc_gpio_set_data_out (141,  0);

		ulk_proc_gpio_set_data_out (142 , 0);
		ulk_proc_gpio_set_data_out (143 , 0);

		ulk_proc_gpio_set_data_out (158,  1);

		}*/

		ulk_proc_gpio_set_data_out (158,  0);

        //confirm all actuation is complete
		ulk_fpga_uart_putc('c');    // if not detected on PC, due to timing mismatch of execution time, then place a small delay before this line. 

	}// end of while

}



