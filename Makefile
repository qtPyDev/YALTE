CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -I src/lib
LDFLAGS = `pkg-config --libs gtk+-3.0`

# define platform and output type
PLATFORM = linux
OUT_TYPE = $(if $(findstring windows,$(PLATFORM)),exe,out)

# define directories
SRC_DIR = src
BUILD_DIR = build
DIST_DIR = dist

# define source files
# SRC_FILEIO = $(SRC_DIR)/fileio.c
# SRC_WINDOW = $(SRC_DIR)/window.c

# define object files
OBJ_FILEIO = $(BUILD_DIR)/fileio.o
OBJ_CMD = $(BUILD_DIR)/cmd.o
OBJ_WINDOW = $(BUILD_DIR)/window.o

# define targets
TARGET = $(DIST_DIR)/YALTE.$(OUT_TYPE)



all: $(TARGET)

$(TARGET): $(OBJ_WINDOW) $(OBJ_FILEIO) $(OBJ_CMD)
	@mkdir -p $(BUILD_DIR)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	rm -rf $(BUILD_DIR)/* $(DIST_DIR)/*
