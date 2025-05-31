# I am working on macOS so i will use this approach to work comfortable and in correct way with 2 working spaces
GTEST_INC_DIR ?= /usr/local/include
GTEST_LIB_DIR ?= /usr/local/lib

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Iinclude -I$(GTEST_INC_DIR)
LDFLAGS = -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -pthread 
TARGET = test_skip_list

all: $(TARGET)

$(TARGET): test/skip_list_test.cpp include/skip_list.h
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) 

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)