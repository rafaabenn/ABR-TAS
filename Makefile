# Compilation : make        Execution : make demo / make bench
CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall
ifeq ($(OS),Windows_NT)
  EXE = .exe
  MKDIR = if not exist bin mkdir bin
  RM = if exist bin rmdir /s /q bin
else
  EXE =
  MKDIR = mkdir -p bin
  RM = rm -rf bin
endif
PROGS = DemoABR DemoTas BenchmarkABR BenchmarkTas
BINS = $(addprefix bin/,$(addsuffix $(EXE),$(PROGS)))
HEADERS = src/ArbreBinaireRecherche.h src/TasMax.h src/TasMin.h

all: $(BINS)

bin/%$(EXE): src/%.cpp $(HEADERS)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

demo: all
	./bin/DemoABR$(EXE)
	./bin/DemoTas$(EXE)

bench: all
	./bin/BenchmarkABR$(EXE)
	./bin/BenchmarkTas$(EXE)

clean:
	$(RM)

.PHONY: all demo bench clean
