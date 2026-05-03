CXX := g++
CXXFLAGS := -O3 -march=native -std=c++17 -Wall -Wextra

SRC_DIR := src
BUILD_DIR := build

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TARGETS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%,$(SOURCES))

all: $(BUILD_DIR) $(TARGETS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	for t in $(TARGETS); do echo "Running $$t"; ./$$t; done

perf: all
	for t in $(TARGETS); do echo "Perf $$t"; perf stat ./$$t || true; done

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run perf clean