# I am working on macOS so i will use this approach to work comfortable and in correct way with 2 working spaces
GTEST_INC_DIR ?= /usr/local/include
GTEST_LIB_DIR ?= /usr/local/lib

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Iinclude -I$(GTEST_INC_DIR) -fsanitize=address
LDFLAGS = -L$(GTEST_LIB_DIR) -lgtest_main -lgtest -pthread -fsanitize=address

TARGET = test_skip_list

SRC_DIR = src
TEST_SRC_DIR = test

TEST_SOURCES = $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst %.cpp,%.o,$(TEST_SOURCES))

all: $(TARGET)

$(TARGET): $(TEST_OBJECTS) 
	$(CXX) $(LDFLAGS) $^ -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_OBJECTS) 