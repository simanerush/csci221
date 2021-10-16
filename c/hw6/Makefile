CXX = clang++
CCFLAGS = -g -Wall -Wextra -pedantic -Werror -std=c++17
HEADERS = tree.hh
OBJECTS = test_tree.o tree.o

.PHONY: all

all: test_tree

%.o: %.cc $(HEADERS)
	$(CXX) $(CCFLAGS) -c $<

test_tree: $(OBJECTS)
	$(CXX) $(CCFLAGS) -o test_tree $(OBJECTS)

tree: tree.o
	$(CXX) $(CFLAGS) -o tree tree.o
