CXX ?= g++
TARGET_NAME := sts_cli
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

ifeq ($(OS),Windows_NT)
	EXE_EXT := .exe
	MKDIR = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
	CLEAN_BUILD = if exist "$(subst /,\,$(BUILD_DIR))" rmdir /S /Q "$(subst /,\,$(BUILD_DIR))"
	RUN_TARGET = $(subst /,\,$(TARGET))
else
	EXE_EXT :=
	MKDIR = mkdir -p "$1"
	CLEAN_BUILD = rm -rf "$(BUILD_DIR)"
	RUN_TARGET = ./$(TARGET)
endif

TARGET := $(BUILD_DIR)/$(TARGET_NAME)$(EXE_EXT)
CXXFLAGS ?= -std=c++17 -Wall -Wextra -I$(INC_DIR)

.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(call MKDIR,$(BUILD_DIR))
	$(CXX) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(call MKDIR,$(OBJ_DIR))
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	$(RUN_TARGET)

clean:
	$(CLEAN_BUILD)

rebuild: clean all
