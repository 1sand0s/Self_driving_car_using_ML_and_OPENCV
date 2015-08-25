#include <ulk_base_types.h>
#include <ulk.h>
#include "macros.h"
int main(void) PROGRAM_ENTRY;


int main()
{

	 ulk_proc_gpio_init();

	 ulk_proc_sys_pad_set_mux_mode (14, 4);

	 ulk_proc_gpio_set_dir ( 14, 1);

	 uint8 i=0;

	for (i = 0; i< 100; i++)
	{


	 ulk_proc_gpio_set_data_out (14 , 1);
	 ulk_proc_delay (5000000);
	 ulk_cpanel_printf("\n DONE %d",i);
	 ulk_proc_gpio_set_data_out (14,  0);
	 ulk_proc_delay (5000000);

	}

	 ulk_cpanel_printf("\n ALL DONE");
	 return 0;
}
