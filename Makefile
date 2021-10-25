CC = g++
CPPFLAGS = -g -Wall
CXXFLAGS = -std=c++11

main: main.o opcode_extension.o modmr.o reader.o memory.o register.o opcodes/add.o opcodes/mov.o opcodes/and.o opcodes/or.o opcodes/inc.o opcodes/dec.o opcodes/sub.o sib.o utility_functions.o push_pop.o test.o cmp.o xchg.o utility_flag_set.o
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o decode.out main.o opcode_extension.o modmr.o reader.o memory.o register.o opcodes/add.o opcodes/mov.o opcodes/and.o opcodes/or.o opcodes/inc.o opcodes/dec.o opcodes/sub.o sib.o utility_functions.o push_pop.o test.o xchg.o cmp.o utility_flag_set.o

main.o: main.cpp opcode_extension.hpp modmr.hpp reader.hpp memory.hpp register.hpp opcodes/add.hpp opcodes/mov.hpp opcodes/and.hpp opcodes/or.hpp opcodes/inc.hpp opcodes/dec.hpp opcodes/sub.hpp sib.hpp utility_functions.hpp opcodes/push_pop.hpp opcodes/test.hpp opcodes/cmp.hpp opcodes/xchg.hpp utility_flag_set.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c main.cpp

opcode_extension.o: opcode_extension.hpp opcode_extension.cpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcode_extension.cpp

modmr.o: modmr.hpp modmr.cpp sib.hpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c modmr.cpp

sib.o: sib.hpp sib.cpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c sib.cpp

memory.o: memory.hpp memory.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c memory.cpp

register.o: register.hpp register.cpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c register.cpp

utility_functions.o: utility_functions.hpp utility_functions.cpp reader.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c utility_functions.cpp

reader.o: reader.hpp reader.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c reader.cpp

utility_flag_set.o: utility_flag_set.hpp utility_flag_set.cpp register.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c utility_flag_set.cpp

add.o: opcodes/add.hpp opcodes/add.cpp ../utility_functions.hpp utility_flag_set.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/add.cpp

mov.o: opcodes/mov.hpp opcodes/mov.cpp ../utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/mov.cpp

and.o: opcodes/and.hpp opcodes/and.cpp ../utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/and.cpp

or.o: opcodes/or.hpp opcodes/or.cpp ../utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/or.cpp

inc.o: opcodes/inc.hpp opcodes/inc.cpp ../utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/inc.cpp

dec.o: opcodes/dec.hpp opcodes/dec.cpp ../utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/dec.cpp

sub.o: opcodes/sub.hpp opcodes/sub.cpp ../utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/sub.cpp

push_pop.o: opcodes/push_pop.hpp opcodes/push_pop.cpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/push_pop.cpp

test.o: opcodes/test.hpp opcodes/test.cpp utility_functions.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/test.cpp

cmp.o: opcodes/cmp.hpp opcodes/cmp.cpp utility_functions.hpp utility_flag_set.hpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/cmp.cpp

xchg.o: opcodes/xchg.hpp opcodes/xchg.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c opcodes/xchg.cpp

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