CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Iinclude -I/usr/local/include 
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -pthread 
TARGET = test_skip_list

all: $(TARGET)

$(TARGET): test/test_skip_list.cpp include/skip_list.hpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) # Добавляем LDFLAGS сюда

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)