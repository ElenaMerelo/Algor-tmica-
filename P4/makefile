SRC=./src
OBJ=./obj
BIN=./bin
CXX = g++
CPPFLAGS = -Wall -g -c

all: $(BIN)/main

$(BIN)/main: $(OBJ)/main.o $(OBJ)/matriz_de_conveniencia.o
	g++ -o $(BIN)/main $(OBJ)/main.o $(OBJ)/matriz_de_conveniencia.o

$(OBJ)/main.o: $(SRC)/main.cpp $(SRC)/matriz_de_conveniencia.cpp
	g++ $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/matriz_de_conveniencia.o: $(SRC)/matriz_de_conveniencia.cpp
	g++ $(CPPFLAGS) $(SRC)/matriz_de_conveniencia.cpp -o $(OBJ)/matriz_de_conveniencia.o
