SRC_DIR := src
INC_DIR := include
TARGET_DIR := target

SERVER_EXE := $(TARGET_DIR)/server
CLIENT_EXE := $(TARGET_DIR)/client

INC := $(wildcard $(INC_DIR)/*.h)
SRC := $(wildcard $(SRC_DIR)/*.cpp)

SERVER_OBJ := $(TARGET_DIR)/server.o
CLIENT_OBJ := $(TARGET_DIR)/client.o

CPPC := g++
CPPFLAGS := -Wall

.PHONY: all run_server run_client clean

all: $(SERVER_EXE) $(CLIENT_EXE)

run_server: $(SERVER_EXE)
	@echo "Running a server.."
	@./$<


run_client: $(CLIENT_EXE)
	@echo "Running a client.."
	@./$<

$(SERVER_EXE): $(SERVER_OBJ) | $(TARGET_DIR)
	@echo "Building the server.."
	@$(CPPC) $^ -o $@

$(CLIENT_EXE): $(CLIENT_OBJ) | $(TARGET_DIR)
	@echo "Building the client.."
	@$(CPPC) $^ -o $@

$(TARGET_DIR)/server.o: $(SRC_DIR)/server.cpp $(INC) | $(TARGET_DIR)
	@echo "Building the server object.."
	@$(CPPC) $(CPPFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(TARGET_DIR)/client.o: $(SRC_DIR)/client.cpp $(INC) | $(TARGET_DIR)
	@echo "Building the client object.."
	@$(CPPC) $(CPPFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(TARGET_DIR):
	@echo "Create target dir.."
	@mkdir -p $@

clean:
	@echo "Cleaning up.."
	@$(RM) -rv $(TARGET_DIR)
