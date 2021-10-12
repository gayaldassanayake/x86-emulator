#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

uint32_t MASK16 = 65535;
uint16_t MASK8 = 255;

enum position { LEFT, RIGHT};
class Register16;
class Register32;

class Register {
    public:

};

class Register8 : public virtual Register {
    private:
    uint8_t buffer;
    Register16 *mainRegister;
    position alignment;

    public:
    void set(uint8_t bf);

    Register8(uint8_t bf) {
        buffer = bf;
    }

    void assignMainRegister(Register16* mainRegPtr, position al) {
        mainRegister = mainRegPtr;
        alignment = al;
    }

    uint8_t fetch() {
        return buffer;
    }

    void setFromMain(uint8_t bf) {
        buffer = bf;
    }
};

class Register16: public virtual Register {
    private:
    uint16_t buffer;
    Register32 *mainRegister;
    Register8 *leastSigSubRegister;
    Register8 *mostSigSubRegister;

    uint16_t generateRightSubRegValue() {
        return (uint8_t) (buffer & MASK8);
    }

    uint16_t generateLeftSubRegValue() {
        return (uint8_t) (buffer>>8);
    }

    public:
    void set(uint16_t bf);
    void setLeastSig8(uint8_t bf8);
    void setMostSig8(uint8_t bf8);

    Register16(uint16_t bf) {
        buffer = bf;
    }

    Register16(uint16_t bf, Register8* mssreg, Register8* lssreg) {
        buffer = bf;

        mostSigSubRegister = mssreg;
        mostSigSubRegister->assignMainRegister(this, LEFT);
        mostSigSubRegister->setFromMain(generateLeftSubRegValue());

        leastSigSubRegister = lssreg;
        leastSigSubRegister->assignMainRegister(this, RIGHT);
        leastSigSubRegister->setFromMain(generateRightSubRegValue());
    }

    void assignMainRegister(Register32* mainRegPtr) {
        mainRegister = mainRegPtr;
    }

    uint16_t fetch() {
        return buffer;
    }

    void setFromMain(uint16_t bf) {
        buffer = bf;
        mostSigSubRegister->setFromMain(generateLeftSubRegValue());
        leastSigSubRegister->setFromMain(generateRightSubRegValue());
    }
};

void Register8::set(uint8_t bf) {
        buffer = bf;
        if(alignment == RIGHT)
            mainRegister->setLeastSig8(bf);
        else if(alignment == LEFT)
            mainRegister->setMostSig8(bf);
}

class Register32 : public virtual Register {
    private:
    uint32_t buffer;
    Register16 *leastSigSubRegister;

    uint16_t generateSubRegValue() {
        return (uint16_t) (buffer & MASK16);
    }

    public:
    Register32(uint32_t bf) {
        buffer = bf;
    }

    Register32(uint32_t bf, Register16* lssreg) {
        buffer = bf;
        leastSigSubRegister = lssreg;
        leastSigSubRegister->assignMainRegister(this);
        leastSigSubRegister->setFromMain(generateSubRegValue());
    }

    uint32_t fetch() {
        return buffer;
    }

    void set(uint32_t bf) {
        buffer = bf;
        leastSigSubRegister->setFromMain(generateSubRegValue());
    }

    void setLeastSig16(uint16_t bf16) {
        buffer ^= ((buffer ^ bf16) & MASK16);
    }
};

void Register16::set(uint16_t bf) {
        buffer = bf;
        mainRegister->setLeastSig16(bf);
        mostSigSubRegister->setFromMain(generateLeftSubRegValue());
        leastSigSubRegister->setFromMain(generateRightSubRegValue());
}

void Register16::setLeastSig8(uint8_t bf8) {
    buffer ^= ((buffer ^ bf8) &MASK8);
    mainRegister->setLeastSig16(buffer);
}

void Register16::setMostSig8(uint8_t bf8) {
    buffer ^= ((buffer ^ (bf8<<8)) &(MASK8<<8));
    mainRegister->setLeastSig16(buffer);
}

class RegisterBank {
    // private:
    // map<string, Register> registers = {};

    public:
    map<string, Register> registers = {};
    RegisterBank() {
        uint8_t zero8 = 0;
        uint16_t zero16 = 0;
        uint32_t zero32 = 0;

        Register8 AH = Register8(zero8);
        Register8 AL = Register8(zero8);
        Register16 AX = Register16(zero16, &AH, &AL);
        Register32 EAX = Register32(zero32, &AX);

        Register8 BH = Register8(zero8);
        Register8 BL = Register8(zero8);
        Register16 BX = Register16(zero16, &BH, &BL);
        Register32 EBX = Register32(zero32, &BX);

        Register8 CH = Register8(zero8);
        Register8 CL = Register8(zero8);
        Register16 CX = Register16(zero16, &CH, &CL);
        Register32 ECX = Register32(zero32, &CX);

        Register8 DH = Register8(zero8);
        Register8 DL = Register8(zero8);
        Register16 DX = Register16(zero16, &DH, &DL);
        Register32 EDX = Register32(zero32, &DX);

        Register32 ESI = Register32(zero32);        
        Register32 EDI = Register32(zero32);
        Register32 ESP = Register32(zero32);
        Register32 EBP = Register32(zero32);

        registers.insert({"AH", AH});
        registers.insert({"AL", AL});
        registers.insert({"AX", AX});
        registers.insert({"EAX", EAX});

        registers.insert({"BH", BH});
        registers.insert({"BL", BL});
        registers.insert({"BX", BX});
        registers.insert({"EBX", EBX});

        registers.insert({"CH", CH});
        registers.insert({"CL", CL});
        registers.insert({"CX", CX});
        registers.insert({"ECX", ECX});

        registers.insert({"DH", DH});
        registers.insert({"DL", DL});
        registers.insert({"DX", DX});
        registers.insert({"EDX", EDX});

        registers.insert({"ESI", ESI});
        registers.insert({"EDI", EDI});
        registers.insert({"ESP", ESP});
        registers.insert({"EBP", EBP});
    }
};

int main() {
    // RegisterBank rb = RegisterBank();
    // rb.registers["EAX"].set(0x12345678);
    // uint8_t bf8 = 245;
    // Register8 AH = Register8(bf8);
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl;
    // AH.set(145);
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl<<endl;

    // Register8 AL = Register8(bf8);
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl;
    // AL.set(145);
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl<<endl;

    // // max 65535
    // uint16_t bf16 = 25535;
    // Register16 AX = Register16(bf16, &AH, &AL);
    // cout<<"AX :"<<AX.fetch()<<endl;
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl;
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl<<endl;

    // // max 4294967295
    // uint32_t bf32 = 3609378592;
    // Register32 EAX = Register32(bf32, &AX);
    // cout<<"EAX:"<<EAX.fetch()<<endl;
    // cout<<"AX :"<<AX.fetch()<<endl;
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl;
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl<<endl;

    // EAX.set(1609378592);
    // cout<<"EAX:"<<EAX.fetch()<<endl;
    // cout<<"AX :"<<AX.fetch()<<endl;
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl;
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl<<endl;

    // AX.set(25535);
    // cout<<"EAX:"<<EAX.fetch()<<endl;
    // cout<<"AX :"<<AX.fetch()<<endl<<endl;
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl;
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl<<endl;

    // // 8 bit reg does not update 32 bit reg.
    // AH.set(145);
    // cout<<"EAX:"<<EAX.fetch()<<endl;
    // cout<<"AX :"<<AX.fetch()<<endl;
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl;
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl<<endl;

    // AL.set(123);
    // cout<<"EAX:"<<EAX.fetch()<<endl;
    // cout<<"AX :"<<AX.fetch()<<endl;
    // cout<<"AH :"<<unsigned(AH.fetch())<<endl;
    // cout<<"AL :"<<unsigned(AL.fetch())<<endl<<endl;
    return 0;
}