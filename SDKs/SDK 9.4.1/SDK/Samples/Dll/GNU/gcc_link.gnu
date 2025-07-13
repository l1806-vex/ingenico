/* Output format */
OUTPUT_FORMAT("elf32-littlearm")

/* Point d'entr�e */
ENTRY(_start)

/* Mapping m�moire */
MEMORY {
	rom : org = 0xE0034000, l = 1M
	ram : org = 0xE003B000, l = 1M
}

/* sections : qui va o� ? */
SECTIONS {
	/* code */
	.text : {
		__text_start = . ;
		*(.first)
		*(.text)
		*(.strings)
		*(.strings.*)
		*(.rodata)
		*(.rodata.*)
		*(.glue_7)
		*(.glue_7t)
		__text_end   = . ;
	} > rom
	/* variables initalis�es : valeurs initiales */
	.init : AT(__text_end) {
		__data_start = . ;
		*(.data)
		__data_end   = . ;
	} > ram
	/* variables non initialis�es */
	.bss : {
		__bss_start = . ;
		*(.bss)
		*(COMMON)
		__bss_end   = . ;
		end = . ;
	} > ram
}

