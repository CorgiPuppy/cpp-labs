SRC_DIR := src
BIN_DIR := bin

EXE := $(BIN_DIR)/main
SRC := $(wildcard $(SRC_DIR)/*.cpp)

CPPC=g++
CPPFLAGS=-Wall

.PHONY: all

all: run clean

run: $(EXE)
	@echo "Running.."
	@./$<

$(EXE): $(SRC_DIR)/*.cpp | $(BIN_DIR)
	@echo "Building.."
	@$(CPPC) $^ -o $@

$(BIN_DIR):
	@echo "Create bin dir.."	
	@mkdir -p $@

clean:
	@echo "Cleaning up.."
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
