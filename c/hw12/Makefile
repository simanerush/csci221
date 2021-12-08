CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -O3 -DDEBUG -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  tsp

tsp: tsp.o chromosome.o deme.o tournament_deme.o climb_chromosome.o cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh HEADER
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o tsp
