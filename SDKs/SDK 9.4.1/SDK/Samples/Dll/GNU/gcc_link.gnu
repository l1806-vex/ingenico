/* Output format */
OUTPUT_FORMAT("elf32-littlearm")

/* Point d'entrée */
ENTRY(_start)

/* Mapping mémoire */
MEMORY {
	rom : org = 0xE0034000, l = 1M
	ram : org = 0xE003B000, l = 1M
}

/* sections : qui va où ? */
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
	/* variables initalisées : valeurs initiales */
	.init : AT(__text_end) {
		__data_start = . ;
		*(.data)
		__data_end   = . ;
	} > ram
	/* variables non initialisées */
	.bss : {
		__bss_start = . ;
		*(.bss)
		*(COMMON)
		__bss_end   = . ;
		end = . ;
	} > ram
}

