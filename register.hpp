#include <string>
#include <map>

using namespace std;

uint32_t MASK16 = 65535;
uint32_t MASK8 = 255;

enum position { LEFT, RIGHT };

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

    void set32(Register* reg, uint32_t value);
    void set16(Register* reg, Register* parent, uint32_t value);
    void set8(Register* reg, Register* parent, Register* grandparent, uint32_t value, position pos);

    public:
    void setRegister(string name, uint32_t value);
    uint32_t getRegister(string name);
};
