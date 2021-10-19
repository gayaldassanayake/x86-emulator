CC = g++
CPPFLAGS = -g -Wall
CXXFLAGS = -std=c++11

main: main.o modmr.o reader.o memory.o register.o opcodes/add.o opcodes/mov.o sib.o utility_functions.o
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o decode.out main.o modmr.o reader.o memory.o register.o opcodes/add.o opcodes/mov.o sib.o utility_functions.o

main.o: main.cpp modmr.hpp reader.hpp memory.hpp register.hpp opcodes/add.hpp opcodes/mov.hpp sib.hpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c main.cpp

modmr.o: modmr.hpp modmr.cpp sib.hpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c modmr.cpp

sib.o: sib.hpp sib.cpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c sib.cpp

memory.o: memory.hpp memory.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c memory.cpp

utility_functions.o: utility_functions.hpp utility_functions.cpp reader.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c utility_functions.cpp

reader.o: reader.hpp reader.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c reader.cpp

register.o: register.hpp register.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c register.cpp

add.o: opcodes/add.hpp opcodes/add.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/add.cpp

mov.o: opcodes/mov.hpp opcodes/mov.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/mov.cpp

clean: 
	$(RM) decode.out *.o

# test_modmr: test_modmr.o modmr.o
# 	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o test_modmr.out test_modmr.o modmr.o

# test_modmr.o: test_modmr.cpp modmr.hpp
# 	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c test_modmr.cpp

# test_memory: test_memory.o memory.o
# 	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o test_memory.out test_memory.o memory.o

# test_memory.o: test_memory.cpp memory.hpp
# 	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c test_memory.cpp