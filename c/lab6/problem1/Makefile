CXX = g++
CCFLAGS = -g -std=c++17

# this is a "Suffix Rule" - how to create a .o from a .cc file
.cpp.o:
	$(CXX) $(CCFLAGS) -c $<

highest: highest.o
	$(CXX) -o highest highest.o

all: source.wc highest

%.wc: %.txt
	wc $< > $@

clean:
	rm -f *.o
	rm -f *.wc
