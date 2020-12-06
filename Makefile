all: clean build

BUILD_DIR = build

clean:
	rm -rf $(BUILD_DIR)
.PHONY: clean

build:
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	cd $(BUILD_DIR) && cmake .. && $(MAKE)
.PHONY: build
