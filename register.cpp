#include "register.hpp"
#include <iostream>

uint32_t MASK16 = 65535;
uint32_t MASK8 = 255;

RegisterBank::RegisterBank(){
    AH = new Register({"AH", 0, nullptr, nullptr});
    AL = new Register({"AL", 0, nullptr, nullptr});
    BH = new Register({"BH", 0, nullptr, nullptr});
    BL = new Register({"BL", 0, nullptr, nullptr});
    CH = new Register({"CH", 0, nullptr, nullptr});
    CL = new Register({"CL", 0, nullptr, nullptr});
    DH = new Register({"DH", 0, nullptr, nullptr});
    DL = new Register({"DL", 0, nullptr, nullptr});
    AX = new Register({"AX", 0, AH, AL});
    BX = new Register({"BX", 0, BH, BL});
    CX = new Register({"CX", 0, CH, CL});
    DX = new Register({"DX", 0, DH, DL});
    SI = new Register({"SI", 0, nullptr, nullptr});
    DI = new Register({"DI", 0, nullptr, nullptr});
    SP = new Register({"SP", 0, nullptr, nullptr});
    BP = new Register({"BP", 0, nullptr, nullptr});
    IP = new Register({"IP", 0, nullptr, nullptr});
    EAX = new Register({"EAX", 0, nullptr, AX});
    EBX = new Register({"EBX", 0, nullptr, BX});
    ECX = new Register({"ECX", 0, nullptr, CX});
    EDX = new Register({"EDX", 0, nullptr, DX});
    ESI = new Register({"ESI", 0, nullptr, SI});
    EDI = new Register({"EDI", 0, nullptr, DI});
    ESP = new Register({"ESP", 0, nullptr, SP});
    EBP = new Register({"EBP", 0, nullptr, BP});
    EIP = new Register({"EIP", 0, nullptr, IP});

    registers = {
        {"AH", AH}, {"AL", AL}, {"BH", BH}, {"BL", BL}, {"CH", CH}, {"CL", CL}, {"DH", DH}, {"DL", DL},
        {"AX", AX}, {"BX", BX}, {"CX", CX}, {"DX", DX},
        {"SI", SI}, {"DI", DI}, {"SP", SP}, {"BP", BP}, {"IP", IP},
        {"EAX", EAX}, {"EBX", EBX}, {"ECX", ECX}, {"EDX", EDX},
        {"ESI", ESI}, {"EDI", EDI}, {"ESP", ESP}, {"EBP", EBP}, {"EIP", EIP}
    };

    initializeRegisters();
}

void RegisterBank::set32(Register* reg, uint32_t value) {
    reg->value = value;
    Register* rightPtr = reg->right;
    if(rightPtr!=nullptr) {
        rightPtr->value  = (value & MASK16);
        Register* rightRightPtr = rightPtr->right;
        Register* leftRightPtr = rightPtr->left;
        if(rightRightPtr!=nullptr) {
            rightRightPtr->value  = (rightPtr->value & MASK8);
        }
        if(leftRightPtr!=nullptr) {
            leftRightPtr->value  = (rightPtr->value >> 8);
        }
    }
}

void RegisterBank::set16(Register* reg, Register* parent, uint32_t value) {
    reg->value = value;
    parent->value ^= ((parent->value ^ value) & MASK16);
    Register* rightPtr = reg->right;
    Register* leftPtr = reg->left;
    if(rightPtr!=nullptr) {
        rightPtr->value  = (value & MASK8);
    }
    if(leftPtr!=nullptr) {
        leftPtr->value = (value >> 8);
    }
}

void RegisterBank::set8(Register* reg, Register* parent, Register* grandparent, uint32_t value, position pos) {
    reg->value = value;
    uint32_t mask = (pos==RIGHT) ? MASK8 : MASK8 << 8;
    value = (pos==RIGHT) ? value : value << 8;
    parent->value ^= ((parent->value ^ value) & mask);
    grandparent->value ^= ((grandparent->value ^ value) & mask);
}

void RegisterBank::setRegister(string name, uint32_t value) {
    Register* reg = registers[name];
    Register* parent;
    Register* grandparent;
    if(name == "EAX") {
        set32(reg, value);
    } else if(name == "EBX") {
        set32(reg, value);
    } else if(name == "ECX") {
        set32(reg, value);
    } else if(name == "EDX") {
        set32(reg, value);
    } else if(name == "ESI") {
        set32(reg, value);
    } else if(name == "EDI") {
        set32(reg, value);
    } else if(name == "EBP") {
        set32(reg, value);
    } else if(name == "ESP") {
        set32(reg, value);
    } else if(name == "EIP") {
        set32(reg, value);
    } else if(name == "AX") {
        parent = registers["EAX"];
        set16(reg, parent, value);
    } else if(name == "BX") {
        parent = registers["EBX"];
        set16(reg, parent, value);
    } else if(name == "CX") {
        parent = registers["ECX"];
        set16(reg, parent, value);
    } else if(name == "DX") {
        parent = registers["EDX"];
        set16(reg, parent, value);
    } else if(name == "SI") {
        parent = registers["ESI"];
        set16(reg, parent, value);
    } else if(name == "DI") {
        parent = registers["EDI"];
        set16(reg, parent, value);
    } else if(name == "SP") {
        parent = registers["ESP"];
        set16(reg, parent, value);
    } else if(name == "BP") {
        parent = registers["EBP"];
        set16(reg, parent, value);
    } else if(name == "IP") {
        parent = registers["EIP"];
        set16(reg, parent, value);
    } else if(name == "AH") {
        parent = registers["AX"];
        grandparent = registers["EAX"];
        set8(reg, parent, grandparent, value, LEFT);
    } else if(name == "AL") {
        parent = registers["AX"];
        grandparent = registers["EAX"];
        set8(reg, parent, grandparent, value, RIGHT);
    } else if(name == "BH") {
        parent = registers["BX"];
        grandparent = registers["EBX"];
        set8(reg, parent, grandparent, value, LEFT);
    } else if(name == "BL") {
        parent = registers["BX"];
        grandparent = registers["EBX"];
        set8(reg, parent, grandparent, value, RIGHT);
    } else if(name == "CH") {
        parent = registers["CX"];
        grandparent = registers["ECX"];
        set8(reg, parent, grandparent, value, LEFT);
    } else if(name == "CL") {
        parent = registers["CX"];
        grandparent = registers["ECX"];
        set8(reg, parent, grandparent, value, RIGHT);
    } else if(name == "DH") {
        parent = registers["DX"];
        grandparent = registers["EDX"];
        set8(reg, parent, grandparent, value, LEFT);
    } else if(name == "DL") {
        parent = registers["DX"];
        grandparent = registers["EDX"];
        set8(reg, parent, grandparent, value, RIGHT);
    }
}

uint32_t RegisterBank::getRegister(string name) {
    if(registers.find(name) != registers.end()) {
        return registers[name]->value;
    }
    return 0;
}

void RegisterBank::initializeRegisters() {
    // eax 0xbf8db144
    // ecx 0x88c5cffb
    // edx 0x1
    // ebx 0xae5ff4
    // esp 0xbf8db0bc
    // ebp 0xbf8db118
    // esi 0x9a0ca0
    // edi 0x0

    // TODO
    // eip 0x8048354
    // eflags 0x246
    // cs 0x73
    // ss 0x7b
    // ds 0x7b
    // es 0x7b
    // fs 0x0
    // gs 0x33

    setRegister("EAX", hexToInt("0xbf8db144"));
    setRegister("EBX", hexToInt("0x00ae5ff4"));
    setRegister("ECX", hexToInt("0x88c5cffb"));
    setRegister("EDX", hexToInt("0x000000x1"));
    setRegister("ESP", hexToInt("0xbf8db0bc"));
    setRegister("EBP", hexToInt("0xbf8db118"));
    setRegister("ESI", hexToInt("0x009a0ca0"));
    setRegister("EDI", hexToInt("0x00000000"));
    setRegister("EIP", hexToInt("0x08048354"));
}
