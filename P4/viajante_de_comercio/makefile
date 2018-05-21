SRC=./src
INC=./inc
OBJ=./obj
BIN=./bin
CXX = g++
CPPFLAGS = -Wall -g -c

all: $(BIN)/main

$(BIN)/main: $(OBJ)/main.o $(OBJ)/tsp.o
	g++ -o $(BIN)/main $(OBJ)/main.o $(OBJ)/tsp.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/tsp.h
	g++ $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/tsp.o: $(SRC)/tsp.cpp $(INC)/tsp.h
	g++ $(CPPFLAGS) $(SRC)/tsp.cpp -o $(OBJ)/tsp.o -I$(INC)
