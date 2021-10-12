#include "register.hpp"
#include <iostream>

using namespace std;

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
    EAX = new Register({"EAX", 0, nullptr, AX});
    EBX = new Register({"EBX", 0, nullptr, BX});
    ECX = new Register({"ECX", 0, nullptr, CX});
    EDX = new Register({"EDX", 0, nullptr, DX});
    ESI = new Register({"ESI", 0, nullptr, nullptr});
    EDI = new Register({"EDI", 0, nullptr, nullptr});
    ESP = new Register({"ESP", 0, nullptr, nullptr});
    EBP = new Register({"EBP", 0, nullptr, nullptr});

    registers = {
        {"AH", AH}, {"AL", AL}, {"BH", BH}, {"BL", BL}, {"CH", CH}, {"CL", CL}, {"DH", DH}, {"DL", DL},
        {"AX", AX}, {"BX", BX}, {"CX", CX}, {"DX", DX}, 
        {"EAX", EAX}, {"EBX", EBX}, {"ECX", ECX}, {"EDX", EDX},
        {"ESI", ESI}, {"EDI", EDI}, {"ESP", ESP}, {"EBP", EBP}
    };
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

// int main() {
//     RegisterBank rb = RegisterBank();
//     rb.setRegister("EAX", 222335);
//     cout<<"EAX "<<rb.getRegister("EAX")<<endl;
//     cout<<"AX "<<rb.getRegister("AX")<<endl;
//     cout<<"AH "<<rb.getRegister("AH")<<endl;
//     cout<<"AL "<<rb.getRegister("AL")<<endl<<endl;
//     rb.setRegister("AH", 34);
//     rb.setRegister("AL", 35);
//     cout<<"AH "<<rb.getRegister("AH")<<endl;
//     cout<<"AL "<<rb.getRegister("AL")<<endl;
//     cout<<"AX "<<rb.getRegister("AX")<<endl;
//     cout<<"EAX "<<rb.getRegister("EAX")<<endl<<endl;  

//     rb.setRegister("AX", 15721);
//     cout<<"AX "<<rb.getRegister("AX")<<endl;
//     cout<<"AH "<<rb.getRegister("AH")<<endl;
//     cout<<"AL "<<rb.getRegister("AL")<<endl;
//     cout<<"EAX "<<rb.getRegister("EAX")<<endl<<endl;  

//     rb.setRegister("ESI", 34234);
//     cout<<"ESI "<<rb.getRegister("ESI")<<endl<<endl;
//     return 0;
// }
