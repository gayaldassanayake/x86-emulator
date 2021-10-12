#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

uint32_t MASK16 = 65535;
uint32_t MASK8 = 255;

enum position { LEFT, RIGHT};

struct Register {
    string name;
    uint32_t value = 0;
    Register* left;
    Register* right;
};

class RegisterBank {

    private:
    Register AH = {"AH", 0, nullptr, nullptr};
    Register AL = {"AL", 0, nullptr, nullptr};
    Register BH = {"BH", 0, nullptr, nullptr};
    Register BL = {"BL", 0, nullptr, nullptr};
    Register CH = {"CH", 0, nullptr, nullptr};
    Register CL = {"CL", 0, nullptr, nullptr};
    Register DH = {"DH", 0, nullptr, nullptr};
    Register DL = {"DL", 0, nullptr, nullptr};
    Register AX = {"AX", 0, &AH, &AL};
    Register BX = {"BX", 0, &BH, &BL};
    Register CX = {"CX", 0, &CH, &CL};
    Register DX = {"DX", 0, &DH, &DL};
    Register EAX = {"EAX", 0, nullptr, &AX};
    Register EBX = {"EBX", 0, nullptr, &BX};
    Register ECX = {"ECX", 0, nullptr, &CX};
    Register EDX = {"EDX", 0, nullptr, &DX};
    Register ESI = {"ESI", 0, nullptr, nullptr};
    Register EDI = {"EDI", 0, nullptr, nullptr};
    Register ESP = {"ESP", 0, nullptr, nullptr};
    Register EBP = {"EBP", 0, nullptr, nullptr};

    map<string, Register*> registers = {
        {"AH", &AH}, {"AL", &AL}, {"BH", &BH}, {"BL", &BL}, {"CH", &CH}, {"CL", &CL}, {"DH", &DH}, {"DL", &DL},
        {"AX", &AX}, {"BX", &BX}, {"CX", &CX}, {"DX", &DX}, 
        {"EAX", &EAX}, {"EBX", &EBX}, {"ECX", &ECX}, {"EDX", &EDX},
        {"ESI", &ESI}, {"EDI", &EDI}, {"ESP", &ESP}, {"EBP", &EBP}
    };

    void set32(Register* reg, uint32_t value) {
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

    void set16(Register* reg, Register* parent, uint32_t value) {
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

    void set8(Register* reg, Register* parent, Register* grandparent, uint32_t value, position pos) {
        reg->value = value;
        uint32_t mask = (pos==RIGHT) ? MASK8 : MASK8 << 8;
        value = (pos==RIGHT) ? value : value << 8;
        parent->value ^= ((parent->value ^ value) & mask);
        grandparent->value ^= ((grandparent->value ^ value) & mask);
    }

    public:
    void setRegister(string name, uint32_t value) {
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

    uint32_t getRegister(string name) {
        if(registers.find(name) != registers.end()) {
            return registers[name]->value;
        }
        return 0;
    }
};

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
