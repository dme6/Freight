CC   := gcc
SRC  := $(shell dir /S /B .\src\*.c ..\common\*.c)
EXE  := ./bin/main.exe
LIBS :=
INC  := -I../common
ARGS :=

$(EXE): $(SRC)
	@$(CC) $^ -o $@ $(LIBS) $(INC)
	@echo Compiled.

.PHONY: clean
clean:
	@del /S /Q .\bin\*
	@echo Cleaned.

.PHONY: run
run: $(EXE)
	@$(EXE)