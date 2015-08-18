CXX = clang++
CFLAGS = -g -Wall -std=c++11
OBJ = image.o image-scrambler.o
EXE = image

all: $(OBJ)
	$(CXX) $(CLAGS) $(OBJ) -o $(EXE)

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXE)
