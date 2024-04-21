CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Werror -pedantic
LDFLAGS=-lm
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=demo
TEST_EXECUTABLE=test

.PHONY: all clean run test valgrind

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_EXECUTABLE): $(OBJECTS) TestCounter.o Test.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	./$(TEST_EXECUTABLE)

valgrind: $(EXECUTABLE) $(TEST_EXECUTABLE)
	valgrind $(VALGRIND_FLAGS) ./$(EXECUTABLE)
	valgrind $(VALGRIND_FLAGS) ./$(TEST_EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE) $(TEST_EXECUTABLE)
