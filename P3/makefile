SRC=./src
INC=./include
OBJ=./obj
BIN=./bin
CXX = g++
CPPFLAGS = -Wall -g -c

all: $(BIN)/main

$(BIN)/main: $(OBJ)/main.o $(OBJ)/matriz_de_adyacencia.o
	g++ -o $(BIN)/main $(OBJ)/main.o $(OBJ)/matriz_de_adyacencia.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/matriz_de_adyacencia.h
	g++ $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/matriz_de_adyacencia.o: $(SRC)/matriz_de_adyacencia.cpp $(INC)/matriz_de_adyacencia.h
	g++ $(CPPFLAGS) $(SRC)/matriz_de_adyacencia.cpp -o $(OBJ)/matriz_de_adyacencia.o -I$(INC)
