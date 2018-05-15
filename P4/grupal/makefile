SRC=./src
INC=./inc
OBJ=./obj
BIN=./bin
CXX = g++
CPPFLAGS = -Wall -g -c

all: $(BIN)/main

$(BIN)/main: $(OBJ)/main.o $(OBJ)/travelling_salesman_problem.o
	g++ -o $(BIN)/main $(OBJ)/main.o $(OBJ)/travelling_salesman_problem.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/travelling_salesman_problem.h
	g++ $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/travelling_salesman_problem.o: $(SRC)/travelling_salesman_problem.cpp $(INC)/travelling_salesman_problem.h
	g++ $(CPPFLAGS) $(SRC)/travelling_salesman_problem.cpp -o $(OBJ)/travelling_salesman_problem.o -I$(INC)
