CXX=g++
CXXFLAGS=-std=c++11
DEPS=pheap.h pheap.tcc node.h node.tcc
OBJS=main.o
TARGET=_main.out

all: $(DEPS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# node: node.h
# 	$(CXX) $(CXXFLAGS) -c -o node.o node.h

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -vf $(OBJS) $(TARGET) 
