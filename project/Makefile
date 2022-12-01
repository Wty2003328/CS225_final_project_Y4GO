CC=gcc
CXX=g++


#CXXFLAGS= -O3 -mtune=native -march=native -I ./src -I ./lib -I ./entry -I ./tests
CXXFLAGS= -O0 -g -I ./src -I ./lib -I ./entry -I ./tests

LDFLAGS= -lstdc++ -lm

TARGET= project

SOURCES=$(wildcard */*.cpp)
OBJ= $(patsubst %.cpp, %.o, $(SOURCES))

%.o : %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

all :   $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)
	#-rm -f $(OBJ)

clean :
	-rm -f $(OBJ)
	-rm -f $(TARGET)
