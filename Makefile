CXX=g++
CXXFLAGS=-Wall -std=c++11
HDRS=pheap.hpp node.hpp
OBJS=main.o pheap.o node.o

all: $(HDRS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o _main.out $(OBJS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -vf *.o *.out