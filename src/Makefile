CC=g++
CPPFLAGS=-Wall -std=c++11
HEADERS=Greedy.h BuildGraph.h Parser.h tinyxml2.h Welsh.h ColorAlgorithm.h Random.h
OBJ=tinyxml2.o Parser.o BuildGraph.o Greedy.o Welsh.o main.o ColorAlgorithm.o Random.o

.PHONY: all
all: build

build: $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^

%.o: %.c %.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c %<

.PHONY: clean
clean:
	rm *.o build welsh.xml greedy.xml random.xml

.PHONY: run
run: build
	./build
