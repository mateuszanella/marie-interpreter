#include <string>
#include <iostream>

using namespace std;

#define MEMORY_SIZE 20

string decToHex(int n)
{
    char hexaDeciNum[100];

    int i = 0;
    while (n != 0)
    {
        int temp = 0;

        temp = n % 16;

        if (temp < 10)
        {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else
        {
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        n = n / 16;
    }

    string hexa = "";
    for (int j = i - 1; j >= 0; j--)
        hexa += hexaDeciNum[j];

    // Make sure the hex value has 6 digits and begins with 0x

    while (hexa.length() < 4)
    {
        hexa = "0" + hexa;
    }

    hexa = "0x" + hexa;
    
    return hexa;
}



int hexToDec(string hexVal)
{
    int len = hexVal.length();

    int base = 1;

    int dec_val = 0;

    for (int i=len-1; i>=0; i--)
    {
        if (hexVal[i]>='0' && hexVal[i]<='9')
        {
            dec_val += (hexVal[i] - 48)*base;

            base = base * 16;
        }

        else if (hexVal[i]>='A' && hexVal[i]<='F')
        {
            dec_val += (hexVal[i] - 55)*base;

            base = base*16;
        }
    }
    
    return dec_val;
}


int main(){

    int     PC = 0,             //Program Counter
            AC = 0,             //Acumulator
            OUT = 0,            //Output
            IN = 0,             //Input
            MAR = 0,            //Memory Address Register
            MBR = 0;            //Memory Buffer Register
    string  IR = "";            //Instruction Register

    bool Halted = false;        //Halt flag

    string M[MEMORY_SIZE] = {"0x5000", "0x8400", "0x9006", "0x9004", "0x6000",
	                         "0x7000", "0x1009", "0x6000", "0x7000", "0x0001"};


    //Fill the memory with 0x0000

    for (int i = 10; i < MEMORY_SIZE; i++){
        M[i] = "0x0000";
    }


    while(!Halted){

        if (PC >= MEMORY_SIZE){
            PC = 0;
        }


        //  Instruction Cycle
        //      MAR <- PC
		//		MBR <- M[MAR]
		//		IR <- MBR
		//		PC <- PC+1

        MAR = PC;
        MBR = hexToDec(M[MAR]);
        IR = decToHex(MBR);
        PC++;

        //  Execution Cycle

        string opCode = IR.substr(2, 1);
        string skipValue = IR.substr(3, 1);
        int operand = hexToDec(IR.substr(3, 3));
        int currentOp = hexToDec(opCode);

        switch (currentOp)
        {
        case 0:
        //JnS
            // MBR = PC;
            // MAR = operand;
            // M[MAR] = decToHex(MBR);
            // MBR = operand;
            // AC = 1;
            // AC += MBR;
            // PC = AC;
            // break;
            break;
        case 1:
        //Load
            MAR = operand;
            MBR = hexToDec(M[MAR]);
            AC = MBR;
            break;
        case 2:
        //Store
            MAR = operand;
            MBR = AC;
            M[MAR] = decToHex(MBR);
            break;
        case 3:
        //Add
            MAR = operand;
            MBR = hexToDec(M[MAR]);
            AC += MBR;
            break;
        case 4:
        //Subt
            MAR = operand;
            MBR = hexToDec(M[MAR]);
            AC -= MBR;
            break;
        case 5:
        //Input
            cout << "Digite um valor: ";
            cin >> IN;
            AC = IN;
            break;
        case 6:
        //Output
            OUT = AC;
            cout << "Valor de saída: " << OUT << endl;
            break;
        case 7:
        //Halt
            Halted = true;
            break;
        case 8:
        //Skipcond
            if (skipValue == "0"){
                if (AC < 0){
                    PC++;
                }
            } else if (skipValue == "4"){
                if (AC == 0){
                    PC++;
                }
            } else if (skipValue == "8"){
                if (AC > 0){
                    PC++;
                }
            }
            break;
        case 9:
        //Jump
            PC = operand;
            break;
        case 10:
        //Clear
            AC = 0;
            break;
        case 11:
        //AddI
            MAR = operand;
            MBR = hexToDec(M[MAR]);
            MAR = MBR;
            MBR = hexToDec(M[MAR]);
            AC += MBR;
            break;
        case 12:
        //JumpI
            MAR = operand;
            MBR = hexToDec(M[MAR]);
            PC = MBR;
            break;
        default:
            cout << "Operação não reconhecida" << endl;
            break;
        }
        
    }

    // cout << "Memória final: " << endl;

    // for (int i = 0; i < MEMORY_SIZE; i++){
    //     cout << M[i] << endl;
    // }

    // cout << "End\n";


    return 0;
}


