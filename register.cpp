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

    CS = new Register({"CS", 0, nullptr, nullptr});
    SS = new Register({"SS", 0, nullptr, nullptr});
    DS = new Register({"DS", 0, nullptr, nullptr});
    ES = new Register({"ES", 0, nullptr, nullptr});
    FS = new Register({"FS", 0, nullptr, nullptr});
    GS = new Register({"GS", 0, nullptr, nullptr});

    EAX = new Register({"EAX", 0, nullptr, AX});
    EBX = new Register({"EBX", 0, nullptr, BX});
    ECX = new Register({"ECX", 0, nullptr, CX});
    EDX = new Register({"EDX", 0, nullptr, DX});
    ESI = new Register({"ESI", 0, nullptr, SI});
    EDI = new Register({"EDI", 0, nullptr, DI});
    ESP = new Register({"ESP", 0, nullptr, SP});
    EBP = new Register({"EBP", 0, nullptr, BP});
    EIP = new Register({"EIP", 0, nullptr, IP});

    EFLAGS = new Register({"EFLAGS", 0, nullptr, nullptr});

    registers = {
        {"AH", AH}, {"AL", AL}, {"BH", BH}, {"BL", BL}, {"CH", CH}, {"CL", CL}, {"DH", DH}, {"DL", DL},
        {"AX", AX}, {"BX", BX}, {"CX", CX}, {"DX", DX},
        {"SI", SI}, {"DI", DI}, {"SP", SP}, {"BP", BP}, {"IP", IP},
        {"CS", CS}, {"SS", SS}, {"DS", DS}, {"ES", ES}, {"FS", FS}, {"GS", GS},
        {"EAX", EAX}, {"EBX", EBX}, {"ECX", ECX}, {"EDX", EDX},
        {"ESI", ESI}, {"EDI", EDI}, {"ESP", ESP}, {"EBP", EBP}, {"EIP", EIP}, {"EFLAGS", EFLAGS}
    };

    flags = {
        {"CF",0}, {"PF",2}, {"AF",4}, {"ZF",6}, 
        {"SF",7}, {"TF",8}, {"IF",9}, {"DF",10}, 
        {"OF",11}, {"NT",14}, {"RF",16}, {"VM",17}, 
        {"AC",18}, {"VIF",19}, {"VIP",20}, {"ID",21}
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
    if(parent!=nullptr) {
        parent->value ^= ((parent->value ^ value) & MASK16);
    }
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
    if(parent!=nullptr) {
        parent->value ^= ((parent->value ^ value) & mask);
    }
    if(grandparent!=nullptr) {
        grandparent->value ^= ((grandparent->value ^ value) & mask);
    }
}

void RegisterBank::setRegister(string name, uint32_t value) {
    Register* reg = registers[name];
    Register* parent = nullptr;
    Register* grandparent = nullptr;
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
    } else if(name == "EFLAGS") {
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
    } else if(name == "CS") {
        set16(reg, parent, value);
    } else if(name == "SS") {
        set16(reg, parent, value);
    } else if(name == "DS") {
        set16(reg, parent, value);
    } else if(name == "ES") {
        set16(reg, parent, value);
    } else if(name == "FS") {
        set16(reg, parent, value);
    } else if(name == "GS") {
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

void RegisterBank::setFlag(string name, int value){
    int index = flags[name];
    if(value == 0) {
        registers["EFLAGS"]->value &= ~(1UL<<index);
    } else {
        registers["EFLAGS"]->value |= 1UL<<index;
    }
}

int RegisterBank::getFlag(string name){
    int index = flags[name];
    return (registers["EFLAGS"]->value & 1UL<<index)>>index;
}

void RegisterBank::initializeRegisters() {
    // TODO: Arrange memory to assign the commented values

    // setRegister("EAX", hexToInt("0xbf8db144"));
    // setRegister("EBX", hexToInt("0x00ae5ff4"));
    // setRegister("ECX", hexToInt("0x88c5cffb"));
    // setRegister("EDX", hexToInt("0x000000x1"));
    // setRegister("ESP", hexToInt("0xbf8db0bc"));
    // setRegister("EBP", hexToInt("0xbf8db118"));
    // setRegister("ESI", hexToInt("0x009a0ca0"));
    // setRegister("EDI", hexToInt("0x00000000"));
    // setRegister("EIP", hexToInt("0x08048354"));
    // setRegister("CS",  hexToInt("0x00000073"));
    // setRegister("SS",  hexToInt("0x0000007b"));
    // setRegister("DS",  hexToInt("0x0000007b"));
    // setRegister("ES",  hexToInt("0x0000007b"));
    // setRegister("FS",  hexToInt("0x00000000"));
    // setRegister("GS",  hexToInt("0x00000033"));
    // setRegister("EFLAGS", hexToInt("0x00000246"));
    
    setRegister("EAX", hexToInt("0x00000000"));
    setRegister("EBX", hexToInt("0x00000020"));
    setRegister("ECX", hexToInt("0x00000040"));
    setRegister("EDX", hexToInt("0x00000060"));
    setRegister("ESP", hexToInt("0x00000080"));
    setRegister("EBP", hexToInt("0x00000100"));
    setRegister("ESI", hexToInt("0x00000120"));
    setRegister("EDI", hexToInt("0x00000140"));
    setRegister("EIP", hexToInt("0x00000160"));
    setRegister("CS",  hexToInt("0x00000180"));
    setRegister("SS",  hexToInt("0x00000200"));
    setRegister("DS",  hexToInt("0x00000220"));
    setRegister("ES",  hexToInt("0x00000280"));
    setRegister("FS",  hexToInt("0x00000300"));
    setRegister("GS",  hexToInt("0x00000320"));
    setRegister("EFLAGS", hexToInt("0x00000246"));
}
