CC   := gcc
SRC  := $(shell dir /S /B .\src\*.c ..\common\*.c)
EXE  := ./bin/main.exe

LIBS := -lws2_32
INC  := -I../common/src -I../common/vendor
DBG  := -g
OPS  := # -O2

$(EXE): $(SRC)
	@echo Compiling.
	@$(CC) $^ -o $@ $(LIBS) $(INC) $(DBG) $(OPS)
	@echo Compiled.

.PHONY: clean
clean:
	@echo Cleaning.
	@del /S /Q .\bin\*
	@echo Cleaned.

.PHONY: run
run: $(EXE)
	@$(EXE) $(ARGS)

.PHONY: debug
debug: $(EXE)
	@gdb --args $(EXE) $(ARGS)