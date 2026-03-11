# Simple developer convenience commands for the project
# CMake remains the authoritative build system.

BUILD_DIR := build/debug
TARGET := pathfinding_sandbox
SRC_DIR := src

CPP_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
HEADER_FILES := $(shell find $(SRC_DIR) \( -name '*.hpp' -o -name '*.h' \))

UNAME_S := $(shell uname -s)

# On macOS, export SDKROOT during CMake configure so compile_commands.json
# contains the proper -isysroot flag for clang-tidy.
ifeq ($(UNAME_S),Darwin)
SDKROOT := $(shell xcrun --sdk macosx --show-sdk-path)
CONFIGURE_ENV := SDKROOT="$(SDKROOT)"
else
CONFIGURE_ENV :=
endif

.PHONY: help configure build run test clean format lint

help:
	@echo "Available commands:"
	@echo "  make configure   Configure the CMake project"
	@echo "  make build       Build the project"
	@echo "  make run         Run the executable"
	@echo "  make test        Run tests via CTest"
	@echo "  make clean       Remove build artifacts"
	@echo "  make format      Format code with clang-format"
	@echo "  make lint        Run clang-tidy on source files"

configure:
	$(CONFIGURE_ENV) cmake --preset debug

build:
	cmake --build --preset debug

run:
	./$(BUILD_DIR)/$(TARGET)

test:
	ctest --test-dir $(BUILD_DIR) --output-on-failure

clean:
	rm -rf build

format:
	clang-format -i $(CPP_FILES) $(HEADER_FILES)

lint:
	@if [ ! -f "$(BUILD_DIR)/compile_commands.json" ]; then \
		echo "compile_commands.json missing — running configure"; \
		$(MAKE) configure; \
	fi
	clang-tidy $(CPP_FILES) -p $(BUILD_DIR)
