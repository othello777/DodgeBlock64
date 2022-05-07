N64_INST = ../../../../n64/toolchain
all: dodgeblock.z64
.PHONY: all

BUILD_DIR = build
include $(N64_INST)/include/n64.mk

SRC = dodgeblock.c
OBJS = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRC:%.c=$(BUILD_DIR)/%.d)

dodgeblock.z64: N64_ROM_TITLE = "DodgeBlock"
dodgeblock.z64: $(BUILD_DIR)/dodgeblock.dfs

$(BUILD_DIR)/dodgeblock.dfs: $(wildcard filesystem/*)
	$(N64_INST)/bin/mksprite 32 16 8 filesystem/libdragon-font.png filesystem/libdragon-font.sprite
	$(N64_MKDFS) $@ filesystem

$(BUILD_DIR)/dodgeblock.elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR) *.z64
.PHONY: clean

-include $(DEPS)
