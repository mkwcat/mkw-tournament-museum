


SECTIONS {
	.text : {
		*(.text)
	}
	.rodata : {
		*(.rodata)
	}
	.data : {
		*(.data)
	}
	.bss : {
		*(.bss)
	}
	
	.ctors : {
		_ctors = .;
		*(.ctors)
		_ctors_end = .;
	}
}