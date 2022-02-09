all: compile link

compile:
	g++ -g -Wall -I src/include -c main.cpp Network.cpp
link:
	g++ -g main.o Network.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system