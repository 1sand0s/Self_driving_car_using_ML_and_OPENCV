OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(main)

MEMORY
{
	ram      : o = 0x82000000, l = 30k
	usrstack : o = 0x82007800, l = 20k	
 
}

SECTIONS
{
  
  /* Code and Constants */
  .text :
    {
    . = 0x00;

      __text_start = .;
      
     *.o(entry)
      *.o(.text)
      *.o(.strings)
      *.o(.rodata)
      *.o(.rodata.*)
      *.o(.comment)
      *.o(.debug*)
      *(.rodata.*)
      *(.rodata)
       *(.eh_frame)
       . = ALIGN(32);
      __text_end = .;
    } > ram

  /* Initialized data */
  .init : 
    {
     . = ALIGN(32);
      __data_start = .;
       . = ALIGN(32);
    /*  nk.o(.data)*/
      *(.data)
      *(.glue_7)
      *(.glue_7t)
      . = ALIGN(32);
      __data_end = .;
      . = ALIGN(32);
    } > ram
    
  .bss : 
    {
      __bss_start = .;
      *(.bss)
      *(COMMON)
      . = ALIGN(32);
      __bss_end = .;
    } > ram


  /* Application stack */
  .stack :
    {
      __stack_start = .;
      *(.stack)
      __stack_end = .;
      . = ALIGN(32);
    } > usrstack


}
