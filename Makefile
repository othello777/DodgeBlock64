BUILD_DIR = build
include $(N64_INST)/include/n64.mk

OBJS = $(BUILD_DIR)/*.o

assets = $(wildcard assets/*.wav)
assets_conv = $(addprefix filesystem/,$(notdir $(assets:%.wav=%.wav64)))

all: dodgeblock.z64

# Run audioconv on all WAV files under assets/
# We do this file by file, but we could even do it just once for the whole
# directory, because audioconv64 supports directory walking.
filesystem/%.wav64: assets/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) -o filesystem $<

$(BUILD_DIR)/dodgeblock.dfs: $(assets_conv) #$(wildcard filesystem/*)
	$(N64_INST)/bin/mksprite 32 16 8 filesystem/libdragon-font.png filesystem/libdragon-font.sprite
	$(N64_MKDFS) $@ filesystem

$(BUILD_DIR)/dodgeblock.elf: $(OBJS)

dodgeblock.z64: N64_ROM_TITLE = "DodgeBlock"
dodgeblock.z64: $(BUILD_DIR)/dodgeblock.dfs

clean:
	rm -rf $(BUILD_DIR) *.z64 $(assets_conv)

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
