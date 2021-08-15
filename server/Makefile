CC   := gcc
SRC  := $(shell dir /S /B .\src\*.c)
EXE  := ./bin/main.exe
LIBS :=
ARGS :=

$(EXE): $(SRC)
	@$(CC) $^ -o $@ $(LIBS)
	@echo Compiled.

.PHONY: clean
clean:
	@del /S /Q .\bin\*
	@echo Cleaned.

.PHONY: run
run: $(EXE)
	@$(EXE)