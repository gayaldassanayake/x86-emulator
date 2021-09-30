CC = g++
CPPFLAGS = -Wall
CXXFLAGS = -std=c++11

main: main.o modmr.o
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o decode.out main.o modmr.o

main.o: main.cpp modmr.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c main.cpp


test_modmr: test_modmr.o modmr.o
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o test_modmr.out test_modmr.o modmr.o

test_modmr.o: test_modmr.cpp modmr.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c test_modmr.cpp

modmr.o: modmr.hpp modmr.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c modmr.cpp

