#include <set>
#include "push_pop.hpp"
#include "../utility_functions.hpp"

string register_name_array[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };

void push50_57(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // decode
    uint32_t index = ins_arg->opcode-(uint32_t)0x50;
    string register_name = register_name_array[index];

    printf("push\t%%%s\n",register_name.c_str());

    // execute
    uint32_t stack_pointer = rb->getRegister("ESP");
    stack_pointer-= 4;

    uint32_t value = rb->getRegister(register_name);
    memory->store(stack_pointer, value);

    rb->setRegister("ESP", stack_pointer);

}

void push_segment_register(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // decode
    string register_name;
    switch (ins_arg->opcode)
    {
    case 0x0e:
        register_name = "CS";
        break;
    case 0x16:
        register_name = "SS";
        break;
    case 0x1e:
        register_name = "DS";
        break;
    case 0x06:
        register_name = "ES";
        break;
    default:
        break;
    }

    printf("push\t%%%s\n",register_name.c_str());

    // execute
    uint32_t stack_pointer = rb->getRegister("ESP");
    stack_pointer -= 2;

    uint16_t value = rb->getRegister(register_name);
    memory->store(stack_pointer, value);

    rb->setRegister("ESP", stack_pointer);

}

void push68(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // decode
    uint32_t immediate_value = readDispalcement(reader, 4);

    printf("push\t%s\n",intToHexStr(immediate_value).c_str());

    // execute
    uint32_t stack_pointer = rb->getRegister("ESP");
    stack_pointer -= 4;

    memory->store(stack_pointer, immediate_value);

    rb->setRegister("ESP", stack_pointer);

}

void push(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    std::set<uint32_t, std::greater<uint32_t> > seg_register_op_set = { 0x0e, 0x16, 0x1e, 0x06 };

    if(ins_arg->opcode >= 0x50 && ins_arg->opcode <= 0x57){
        push50_57(ins_arg, reader, rb, memory);
    }
    else if(seg_register_op_set.count(ins_arg->opcode)){
        push_segment_register(ins_arg, reader, rb, memory);
    }
    else if(ins_arg->opcode == 0x68){
        push68(ins_arg, reader, rb, memory);   
    }
    else{
        printf("Unsupported push operand\n");
    }
}


void pop58_5f(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // decode
    uint32_t index = ins_arg->opcode-(uint32_t)0x58;
    string register_name = register_name_array[index];

    printf("pop\t%%%s\n",register_name.c_str());

    // execute
    uint32_t stack_pointer = rb->getRegister("ESP");
   
    uint32_t value;
    memory->read(stack_pointer, &value);
    rb->setRegister(register_name, value);

    stack_pointer += 4;
    if(register_name != "ESP"){
        rb->setRegister("ESP", stack_pointer);
    }    

}

void pop_segment_register(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // decode
    string register_name;
    switch (ins_arg->opcode)
    {
    case 0x1f:
        register_name = "DS";
        break;
    case 0x07:
        register_name = "ES";
        break;
    case 0x17:
        register_name = "SS";
        break;
    default:
        break;
    }

    printf("pop\t%%%s\n",register_name.c_str());

    // execute
    uint32_t stack_pointer = rb->getRegister("ESP");
   
    uint16_t value;
    memory->read(stack_pointer, &value);
    rb->setRegister(register_name, value);

    stack_pointer += 2;
    rb->setRegister("ESP", stack_pointer);
}


void pop(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    std::set<uint32_t, std::greater<uint32_t> > seg_register_op_set = { 0x1f, 0x07, 0x17 };
    
    if(ins_arg->opcode >= 0x58 && ins_arg->opcode <= 0x5f){
        pop58_5f(ins_arg, reader, rb, memory);
    }
    else if(seg_register_op_set.count(ins_arg->opcode)){
        pop_segment_register(ins_arg, reader, rb, memory);
    }
    else{
        printf("Unsupported pop operand\n");
    }
}