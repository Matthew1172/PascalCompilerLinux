//
// Created by matthew on 12/18/21.
//
#include "MyEmulator.h"
using namespace std;

MyEmulator::MyEmulator() {

}

MyEmulator::MyEmulator(string fp) {
    setFilepath(fp);
    readPcodeFile();
}

MyEmulator::~MyEmulator() {
    closePcodeFile();
}

void MyEmulator::setFilepath(string fp) {
    if(fp.length() > MAXFILEPATH){
        //filename too large
        exit(-5);
    }
    //initialize filepath from string
    strcpy(this->fp, fp.c_str());
    //check access
    //checkOutputFileAccess();
}

void MyEmulator::readPcodeFile() {
    rv = access(fp, F_OK);
    if(rv != 0){
        if(errno == ENOENT) printf("%s does not exist. \n", fp);
        else if(errno == EACCES) printf("%s is inaccessible. \n", fp);
        exit(1);
    }
    fd = open(fp, O_RDONLY);
    if(fd == -1){
        printf("open() FROM EMULATOR failed with error [%s]\n", strerror(errno));
        exit(2);
    }
    //if(DEBUG) printf("open() successful! \n");
    struct stat stbuf{};
    stat(fp, &stbuf);
    MAXCODE = stbuf.st_size;
    //if(DEBUG) printf("Filesize is: %lu \n", filesize);
    CODE = static_cast<byte *>(calloc(MAXCODE, 1));
    read(fd, CODE, MAXCODE);
}

void MyEmulator::closePcodeFile() {
    //close file
    if(close(fd) != 0){
        strerror(errno);
        exit(-555);
    }
    printf("close() FROM EMULATOR successful! \n");
}

void MyEmulator::printStack() {
    for(byte b = 0x00; b < SP; b+=0x01){
        cout << *(STACK+b) << endl;
    }
}

void MyEmulator::emulate() {
    IP = 0;
    flags = 0x00000000;
    int temp;
    float ftemp;
    float ftemp2;
    int itemp;
    int itemp2;
    int ians;
    float fans;
    while (1) {
        switch (opcode = CODE[IP++]) {
            case OP_PUSH:
                temp=*(int *)(CODE+IP); IP+=sizeof(int); // address
                temp=*(int *)(DATA+temp);
                // value of the variable;
                *(int *)(STACK+SP)=temp; SP+=sizeof(int); // push
            case OP_PUSHI:
                //immediate integer
                itemp = *(int*)(CODE+IP);
                IP+=sizeof(int);
                *(int *)(STACK+SP)=itemp; SP+=sizeof(int); // push
                break;
            case OP_FPUSHI:
                //immediate real (float)
                ftemp = *(float*)(CODE+IP);
                IP+=sizeof(float);
                *(float *)(STACK+SP)=ftemp;
                SP+=sizeof(float); // push
                break;
            case OP_XCHG:
                //single real and int are same #of bytes,
                //we will always exchange size of int
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                SP -= sizeof(int);
                itemp2 = *(int*)(STACK+SP);
                *(int *)(STACK+SP)=itemp; SP+=sizeof(int); // push
                *(int *)(STACK+SP)=itemp2; SP+=sizeof(int); // push
                break;
            case OP_ADD:
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                SP -= sizeof(int);
                itemp2 = *(int*)(STACK+SP);
                ians = itemp2 + itemp;
                *(int *)(STACK+SP)=ians; SP+=sizeof(int); // push
                cout << ians << endl;
                break;
            case OP_SUB:
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                SP -= sizeof(int);
                itemp2 = *(int*)(STACK+SP);
                ians = itemp2 - itemp;
                *(int *)(STACK+SP)=ians; SP+=sizeof(int); // push
                cout << ians << endl;
                break;
            case OP_MUL:
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                SP -= sizeof(int);
                itemp2 = *(int*)(STACK+SP);
                ians = itemp2 * itemp;
                *(int *)(STACK+SP)=ians; SP+=sizeof(int); // push
                cout << ians << endl;
                break;
            case OP_DIV:
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                SP -= sizeof(int);
                itemp2 = *(int*)(STACK+SP);
                ians = itemp2 / itemp;
                *(int *)(STACK+SP)=ians; SP+=sizeof(int); // push
                cout << ians << endl;
                break;
            case OP_MOD:
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                SP -= sizeof(int);
                itemp2 = *(int*)(STACK+SP);
                ians = itemp2 % itemp;
                *(int *)(STACK+SP)=ians; SP+=sizeof(int); // push
                cout << ians << endl;
                break;
            case OP_FADD:
                SP -= sizeof(float);
                ftemp = *(float*)(STACK+SP);
                SP -= sizeof(float);
                ftemp2 = *(float*)(STACK+SP);
                fans = ftemp2 + ftemp;
                *(float *)(STACK+SP)=fans; SP+=sizeof(float); // push
                cout << fans << endl;
                break;
            case OP_FSUB:
                SP -= sizeof(float);
                ftemp = *(float*)(STACK+SP);
                SP -= sizeof(float);
                ftemp2 = *(float*)(STACK+SP);
                fans = ftemp2 - ftemp;
                *(float *)(STACK+SP)=fans; SP+=sizeof(float); // push
                cout << fans << endl;
                break;
            case OP_FMUL:
                SP -= sizeof(float);
                ftemp = *(float*)(STACK+SP);
                SP -= sizeof(float);
                ftemp2 = *(float*)(STACK+SP);
                fans = ftemp2 * ftemp;
                *(float *)(STACK+SP)=fans; SP+=sizeof(float); // push
                cout << fans << endl;
                break;
            case OP_FDIV:
                SP -= sizeof(float);
                ftemp = *(float*)(STACK+SP);
                SP -= sizeof(float);
                ftemp2 = *(float*)(STACK+SP);
                fans = ftemp2 / ftemp;
                *(float *)(STACK+SP)=fans; SP+=sizeof(float); // push
                cout << fans << endl;
                break;
            case OP_NEQ:
                break;
            case OP_EQL:
                break;
            case OP_AND:
                break;
            case OP_OR:
                break;
            case OP_GTR:
                break;
            case OP_LSS:
                break;
            case OP_GEQ:
                break;
            case OP_LEQ:
                break;
            case OP_CVI:
                SP -= sizeof(float);
                ftemp = *(float*)(STACK+SP);
                itemp = (int)floorf(ftemp);
                *(int *)(STACK+SP)=itemp; SP+=sizeof(int); // push
                break;
            case OP_CVR:
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                ftemp = (float)itemp;
                *(float *)(STACK+SP)=ftemp; SP+=sizeof(float); // push
                break;
            case OP_NEG:
                SP -= sizeof(int);
                itemp = *(int*)(STACK+SP);
                ians= -itemp;
                *(int *)(STACK+SP)=ians; SP+=sizeof(int); // push
                cout << ians << endl;
                break;
            case OP_FNEG:
                SP -= sizeof(float);
                ftemp = *(float*)(STACK+SP);
                fans= -ftemp;
                *(float *)(STACK+SP)=fans; SP+=sizeof(float); // push
                cout << fans << endl;
                break;
            case OP_NOT:
                break;
            case OP_JTAB:
                break;
            case OP_CALL:
                break;
            case OP_RET:
                break;
            case OP_JMP:
                break;
            case OP_JTRUE:
                break;
            case OP_JFALSE:
                break;
            case OP_HALT:
                exit(0);
            case OP_PRINTINT:
                break;
            case OP_PRINTCHR:
                break;
            case OP_PRINTLN:
                break;
            case OP_MALLOC:
                break;
            case OP_FREE:
                break;
            default:
                cout << "Unrecognized opcode: " << opcode << endl;
                exit(-555);
        }
        //doesn't really work
        //printStack();
    }
}
