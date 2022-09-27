


SECTIONS {
	.text : {
		*(.text*)
	}
	.rodata : {
		*(.rodata*)
	}
	.data : {
		*(.data)
		*(.sdata)
		*(.sdata2)
	}
	.bss : {
		*(.bss*)
		*(.sbss*)
	}
	
	.ctors : {
		_ctors = .;
		*(.ctors)
		*(.init_array)
		_ctors_end = .;
	}
}