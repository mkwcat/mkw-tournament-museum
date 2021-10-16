BIN := bin
MKWTM := mkwtm

DUMMY != mkdir -p $(BIN)

default:
	@$(MAKE) --no-print-directory -C loader
	cp loader/build/loader.bin $(BIN)/loader.bin
	@$(MAKE) --no-print-directory -C src
	cp src/build/$(MKWTM)_P.rel $(BIN)/$(MKWTM)_P.rel
	cp src/build/$(MKWTM)_E.rel $(BIN)/$(MKWTM)_E.rel
	cp src/build/$(MKWTM)_J.rel $(BIN)/$(MKWTM)_J.rel
	cp src/build/$(MKWTM)_K.rel $(BIN)/$(MKWTM)_K.rel

clean:
	rm -rf loader/build
	rm -rf src/build
	rm -rf $(BIN)