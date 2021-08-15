CC   := gcc
SRC  := $(shell dir /S /B .\src\*.c)
EXE  := ./bin/main.exe
LIBS := -lws2_32
ARGS := setserver 1 1

$(EXE): $(SRC)
	@$(CC) $^ -o $@ $(LIBS)
	@echo Compiled.

.PHONY: clean
clean:
	@del /S /Q .\bin\*
	@echo Cleaned.

.PHONY: run
run: $(EXE)
	@$(EXE) $(ARGS)