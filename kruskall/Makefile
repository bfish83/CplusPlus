# File: makefile
# Author: CS315 JWJ-CS-UK and edited by Barret Fisher
# Task: pa2 - cs315s15 handout
# Description: makefile for building program "pa2"

pa2: main.o graph.o edge.o unionfind.o
	g++ -std=gnu++11 -o pa2 main.o graph.o edge.o unionfind.o

main.o:	main.cpp
	g++ -std=gnu++11 -c -Wall main.cpp

graph.o: graph.h graph.cpp
	g++ -std=gnu++11 -c -Wall graph.cpp

edge.o:	edge.h edge.cpp
	g++ -std=gnu++11 -c -Wall edge.cpp

unionfind.o: unionfind.h unionfind.cpp
	g++ -std=gnu++11 -c -Wall unionfind.cpp


clean:
	rm pa2
	rm *.o
