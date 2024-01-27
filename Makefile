export N64_INST ?= /opt/libdragon/
# V			= 1 
SOURCE_DIR 	= src
BUILD_DIR	= build

include $(N64_INST)/include/n64.mk

all: chess.z64
.PHONY: all

OBJS = $(BUILD_DIR)/main.o \
	$(BUILD_DIR)/debug.o \
	$(BUILD_DIR)/Board.o

chess.z64: N64_ROM_TITLE="Chess on n64"
chess.z64: $(BUILD_DIR)/chess.dfs

$(BUILD_DIR)/chess.dfs: $(wildcard filesystem/*)
$(BUILD_DIR)/chess.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)
