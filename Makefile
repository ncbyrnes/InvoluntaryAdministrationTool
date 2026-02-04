BUILD_DIR = build
BIN_DIR = bin
.PHONY: all kernel-mod clean

all: kernel-mod

kernel-mod:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..
	@$(MAKE) -C $(BUILD_DIR) kernel-mod

clean:
	rm -rf $(BUILD_DIR)
	rm -rf bin

