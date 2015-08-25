/* Use PROGRAM_ENTRY to make the entry function (first function to be executed)
 * to come in "entry" section. The "entry" section is mapped to the initial
 * section of lds file
 * .text :
 *  {
 *    __text_start = .;
 *    *.o(entry)
 *    *.o(.text)
 *
 */

#define PROGRAM_ENTRY __attribute__ ((section("entry")))
#define DEBUG_BREAK { \
	__asm (" STMFD   sp!, {r14}  "); \
	__asm (" swi #0x10 "); \
	__asm (" LDMFD   sp!, {r14} "); \
}

#define DEBUG_BREAK_INTR { \
	__asm (" swi #0x10 "); \
}
#if 1
void raise()
{
        return 0;
}
#endif
