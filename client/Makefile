CC   := gcc
SRC  := $(shell dir /S /B .\src\*.c ..\common\*.c)
EXE  := ./bin/main.exe
LIBS := # -lws2_32
INC  := -I../common/src -I../common/vendor
ARGS := getserver
OPS  := # -O2

$(EXE): $(SRC)
	@$(CC) $^ -o $@ $(LIBS) $(INC) $(OPS)
	@echo Compiled.

.PHONY: clean
clean:
	@del /S /Q .\bin\*
	@echo Cleaned.

.PHONY: run
run: $(EXE)
	@$(EXE) $(ARGS)