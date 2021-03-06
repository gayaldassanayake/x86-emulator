#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <map>
#include "utility_functions.hpp"

enum position { LEFT, RIGHT };

struct Register {
    string name;
    uint32_t value;
    Register* left;
    Register* right;
};

class RegisterBank {

    private:
        struct Register *AH;
        struct Register *AL;
        struct Register *BH;
        struct Register *BL;
        struct Register *CH;
        struct Register *CL;
        struct Register *DH;
        struct Register *DL;
        struct Register *AX;
        struct Register *BX;
        struct Register *CX;
        struct Register *DX;
        struct Register *SI;
        struct Register *DI;
        struct Register *SP;
        struct Register *BP;
        struct Register *IP;
        struct Register *CS;
        struct Register *SS;
        struct Register *DS;
        struct Register *ES;
        struct Register *FS;
        struct Register *GS;
        struct Register *EAX;
        struct Register *EBX;
        struct Register *ECX;
        struct Register *EDX;
        struct Register *ESI;
        struct Register *EDI;
        struct Register *ESP;
        struct Register *EBP;
        struct Register *EIP;
        struct Register *EFLAGS;

        std::map<string, Register*> registers;
        std::map<string, int> flags;

        void set32(Register* reg, uint32_t value);
        void set16(Register* reg, Register* parent, uint32_t value);
        void set8(Register* reg, Register* parent, Register* grandparent, uint32_t value, position pos);
        void initializeRegisters();

    public:
        RegisterBank();
        void setRegister(string name, uint8_t value);
        void setRegister(string name, uint16_t value);
        void setRegister(string name, uint32_t value);
        uint32_t getRegister(string name);
        void setFlag(string name, int value);
        int getFlag(string name);
        void getRegisterDump();
};

#endif