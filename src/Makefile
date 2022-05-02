# Project directory
BUILD := build
TARGET := mkwtm
SYMBOLS_SRC := symbols.tsv
SYMBOLS_OUT := $(TARGET)_P.rel.lst $(TARGET)_E.rel.lst $(TARGET)_J.rel.lst $(TARGET)_K.rel.lst

# Compiler definitions
CC := mwcceppc
LD := $(DEVKITPPC)/bin/powerpc-eabi-ld
LSTGEN := lstgen.py
ELF2REL := ../elf2rel/elf2rel.exe

SOURCES := $(wildcard *.c)
SOURCES := $(wildcard *.cpp)
INCLUDE := ../include

DUMMY != mkdir -p $(BUILD)

CFLAGS := -O4,p -pragma "cpp1x on" -gccext on -enum int -Cpp_exceptions off -RTTI off -fp hard \
          -use_lmw_stmw on -sdata 0 -sdata2 0 -func_align 4 -gccinc -partial -ipa file -main _prolog

default: $(BUILD)/$(TARGET)_P.rel $(BUILD)/$(TARGET)_E.rel \
         $(BUILD)/$(TARGET)_J.rel $(BUILD)/$(TARGET)_K.rel

clean:
	@echo cleaning...
	@rm -rf $(BUILD)

$(BUILD)/$(TARGET).plf: $(SOURCES)
	@echo building ... $(TARGET).plf
	$(CC) $(CFLAGS) -o $(BUILD)/$(TARGET).plf -I$(INCLUDE) $(SOURCES)

$(BUILD)/$(TARGET).elf: $(BUILD)/$(TARGET).plf
	@echo linking ... $(TARGET).elf
	$(LD) -Tlink.ld -r $< -o $@

$(BUILD)/$(TARGET)_P.rel.lst: $(SYMBOLS_SRC)
	@python $(LSTGEN) $(SYMBOLS_SRC) $@ 0
$(BUILD)/$(TARGET)_E.rel.lst: $(SYMBOLS_SRC)
	@python $(LSTGEN) $(SYMBOLS_SRC) $@ 1
$(BUILD)/$(TARGET)_J.rel.lst: $(SYMBOLS_SRC)
	@python $(LSTGEN) $(SYMBOLS_SRC) $@ 2
$(BUILD)/$(TARGET)_K.rel.lst: $(SYMBOLS_SRC)
	@python $(LSTGEN) $(SYMBOLS_SRC) $@ 3

$(BUILD)/$(TARGET)_%.rel: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET)_%.rel.lst
	@echo output ... $@
	$(ELF2REL) -i $(BUILD)/$(TARGET).elf -s $@.lst -o $@
