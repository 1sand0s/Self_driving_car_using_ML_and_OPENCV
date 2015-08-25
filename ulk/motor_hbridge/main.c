#include <ulk_base_types.h>
#include <ulk.h>
#include "macros.h"
int main(void) PROGRAM_ENTRY;


int main()
{

	 ulk_proc_gpio_init();

	 ulk_proc_sys_pad_set_mux_mode (140, 4);
	 ulk_proc_sys_pad_set_mux_mode (141, 4);
	 ulk_proc_sys_pad_set_mux_mode (142, 4);
	 ulk_proc_sys_pad_set_mux_mode (143, 4);
	 ulk_proc_sys_pad_set_mux_mode (158, 4);
	 ulk_proc_sys_pad_set_mux_mode (162, 4);
	 ulk_proc_sys_pad_set_mux_mode (161, 4);
	 ulk_proc_sys_pad_set_mux_mode (159, 4);
	 ulk_proc_sys_pad_set_mux_mode (156, 4);
	 ulk_proc_sys_pad_set_mux_mode (157, 4);
	 ulk_proc_sys_pad_set_mux_mode (12, 4);
	 ulk_proc_sys_pad_set_mux_mode (13, 4);
	 ulk_proc_sys_pad_set_mux_mode (14, 4);
	 ulk_proc_sys_pad_set_mux_mode (17, 4);
	 ulk_proc_sys_pad_set_mux_mode (18, 4);
	 ulk_proc_sys_pad_set_mux_mode (19, 4);
	 ulk_proc_sys_pad_set_mux_mode (20, 4);
	 ulk_proc_sys_pad_set_mux_mode (22, 4);
	 ulk_proc_sys_pad_set_mux_mode (23, 4);

	 ulk_proc_gpio_set_dir ( 140, 0);
	 ulk_proc_gpio_set_dir ( 141, 0);
	 ulk_proc_gpio_set_dir ( 142, 0);
	 ulk_proc_gpio_set_dir ( 143, 0);
	 ulk_proc_gpio_set_dir ( 158, 0);
	 ulk_proc_gpio_set_dir ( 162, 0);
	 ulk_proc_gpio_set_dir ( 161, 0);
	 ulk_proc_gpio_set_dir ( 159, 0);
	 ulk_proc_gpio_set_dir ( 156, 0);
	 ulk_proc_gpio_set_dir ( 157, 0);
	 ulk_proc_gpio_set_dir ( 12, 0);
	 ulk_proc_gpio_set_dir ( 13, 0);
	 ulk_proc_gpio_set_dir ( 14, 0);
	 ulk_proc_gpio_set_dir ( 17, 0);
	 ulk_proc_gpio_set_dir ( 18, 0);
	 ulk_proc_gpio_set_dir ( 19, 0);
	 ulk_proc_gpio_set_dir ( 20, 0);
	 ulk_proc_gpio_set_dir ( 22, 0);
	 ulk_proc_gpio_set_dir ( 23, 0);



	 uint8 i=0;

	for (i = 0; i< 100; i++)
	{


	 ulk_proc_gpio_set_data_out (140 , 1);
	 ulk_proc_gpio_set_data_out (141 , 0);


	 ulk_proc_delay(ULK_SEC(5));


	 ulk_cpanel_printf("\n DONE %d",i);
	 ulk_proc_gpio_set_data_out (140,  0);
	 ulk_proc_gpio_set_data_out (141,  1);



	 ulk_proc_delay(ULK_SEC(5));

	}

	 ulk_cpanel_printf("\n ALL DONE");
	 return 0;
}
