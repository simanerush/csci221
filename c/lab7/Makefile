CXX = g++
CCFLAGS = -fsanitize=address -g -std=c++17 

# this is a "Suffix Rule" - how to create a .o from a .cc file
.cpp.o:
	$(CXX) $(CCFLAGS) -c $<

buggy: student_list.cc
	$(CXX) $(CCFLAGS) -o $@ $<

all: buggy

%.wc: %.txt
	wc $< > $@

clean:
	rm -f *.o
	rm -f *.wc
