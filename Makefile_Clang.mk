# Project directory
BUILD := build
TARGET := mkwtm
SYMBOLS_SRC := symbols.tsv
SYMBOLS_OUT := $(TARGET)_P.rel.lst $(TARGET)_E.rel.lst $(TARGET)_J.rel.lst $(TARGET)_K.rel.lst

# Compiler definitions
CLANG := clang
CC := $(CLANG)
LD := $(DEVKITPPC)/bin/powerpc-eabi-ld
LSTGEN := lstgen.py
ELF2REL := ../elf2rel/elf2rel.exe

CFILES := $(wildcard *.c)
CPPFILES := $(wildcard *.cpp)
INCLUDE := ../include

OFILES		:=	$(CPPFILES:.cpp=_cpp.o) $(CFILES:.c=_c.o)
OFILES		:= $(addprefix $(BUILD)/, $(OFILES))

DUMMY != mkdir -p $(BUILD)

CFLAGS := --target=powerpc-gekko-ibm-kuribo-eabi -Os -fno-rtti -fno-short-enums -fshort-wchar -fdeclspec -fno-exceptions -nodefaultlibs -ffreestanding


default: $(BUILD)/$(TARGET)_P.rel $(BUILD)/$(TARGET)_E.rel \
         $(BUILD)/$(TARGET)_J.rel $(BUILD)/$(TARGET)_K.rel

clean:
	@echo cleaning...
	@rm -rf $(BUILD)
	
$(BUILD)/%_c.o: %.c
	@echo $<
	@$(CC) $(CFLAGS) -I../include -c -o $@ $<

$(BUILD)/%_cpp.o: %.cpp
	@echo $<
	@$(CC) $(CFLAGS) -I../include -c -o $@ $<

$(BUILD)/$(TARGET).elf: $(OFILES)
	@echo linking ... $(TARGET).elf
	@$(LD) -Tlink.ld -r $(OFILES) -o $@

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
