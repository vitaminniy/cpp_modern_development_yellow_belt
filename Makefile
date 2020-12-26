all: build

BUILD_DIR = build

clean:
	rm -rf $(BUILD_DIR)
.PHONY: clean

build:
	cmake -B $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake --build .
.PHONY: build

test: build
	cd $(BUILD_DIR) && ctest --output-on-failure
.PHONY: test
