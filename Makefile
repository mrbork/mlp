all: compile link

compile:
	g++ -g -Wall -I src/include -c main.cpp Network.cpp Perceptron.cpp
link:
	g++ main.o Network.o Perceptron.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system