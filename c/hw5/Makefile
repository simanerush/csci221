CXX = clang++
CCFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic 

# this is a "Suffix Rule" - how to create a .o from a .cc file
.cpp.o:
	$(CXX) $(CCFLAGS) -c $<

griddlepie: griddlepie.o
	$(CXX) -o griddlepie griddlepie.o

