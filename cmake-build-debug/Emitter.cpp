//
// Created by matthew on 12/17/21.
//

#include "Emitter.h"
using namespace std;


Emitter::Emitter(bool binaryFlag) {
    if(binaryFlag != 1 && binaryFlag != 0) exit(-1);
    this->binary = binaryFlag;
}

Emitter::Emitter(std::string outputFilePath, bool binaryFlag) {
    if(binaryFlag != 1 && binaryFlag != 0) exit(-1);
    this->binary = binaryFlag;
    setFilepath(outputFilePath);
    createOutputFile();
}

Emitter::~Emitter() {
    closeOutputFile();
}

void Emitter::setFilepath(const std::string& outputFilePath) {
    if(outputFilePath.length() > MAXFILEPATH){
        //filename too large
        exit(-5);
    }
    //initialize filepath from string
    strcpy(filepath, outputFilePath.c_str());
    createOutputFile();
    checkOutputFileAccess();
}

void Emitter::checkOutputFileAccess(){
    // Check file existence
    /* Check read access. */
    /* Check write access. */
    rv = access(filepath, R_OK | W_OK);
    if(rv != 0){
        if (errno == EACCES){
            printf("File: %s is not accessible\n", filepath);
            exit(2);
        }
        if (errno == EROFS) {
            printf("%s is not writable (read-only filesystem)\n", filepath);
            exit(2);
        }
        printf("ACCESS() FROM EMITTER failed with error [%s]\n", strerror(errno));
        exit(2);
    }
}

void Emitter::createOutputFile() {
    fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if(fd == -1){
        printf("open() FROM EMITTER failed with error [%s]\n", strerror(errno));
        exit(2);
    }
    printf("open() FROM EMITTER successful! \n");
}

void Emitter::closeOutputFile() {
    //close file
    if(close(fd) != 0){
        strerror(errno);
        exit(-555);
    }
    printf("close() FROM EMITTER successful! \n");
}

void Emitter::stringToBuffer(std::string code) {
    n = code.length();
    strcpy(bf, code.c_str());
}

void Emitter::printOpcodeError() {
    printf("write in emit opcode failed with error [%s]\n", strerror(errno));
    exit(4);
}

void Emitter::writePcode(std::string opcode) {
    stringToBuffer(opcode);
    rv = write(fd, bf, n);
    if(rv == -1) printOpcodeError();
}

void Emitter::writePcodeBinary(Opcodes opcode) {
    char c[1];
    c[0] = (char) opcode;
    //c[1] = 'a';
    //sprintf(c, "%c", opcode);
    rv = write(fd, c, 1);
    if(rv == -1) printOpcodeError();
}

void Emitter::emit_opcode(Opcodes op){
    switch(op){
        case OP_HALT:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_HALT);
            }else{
                //write human readible pcode
                writePcode("HALT\n");
            }
            break;
        case OP_PUSHI:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_PUSHI);
            }else{
                //write human readible pcode
                writePcode("PUSHI ");
            }
            break;
        case OP_FPUSHI:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_FPUSHI);
            }else{
                //write human readible pcode
                writePcode("FPUSHI ");
            }
            break;
        case OP_MUL:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_MUL);
            }else{
                //write human readible pcode
                writePcode("MUL\n");
            }
            break;
        case OP_DIV:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_DIV);
            }else{
                //write human readible pcode
                writePcode("DIV\n");
            }
            break;
        case OP_ADD:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_ADD);
            }else{
                //write human readible pcode
                writePcode("ADD\n");
            }
            break;
        case OP_SUB:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_SUB);
            }else{
                //write human readible pcode
                writePcode("SUB\n");
            }
            break;
        case OP_FMUL:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_FMUL);
            }else{
                //write human readible pcode
                writePcode("FMUL\n");
            }
            break;
        case OP_FDIV:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_FDIV);
            }else{
                //write human readible pcode
                writePcode("FDIV\n");
            }
            break;
        case OP_FADD:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_FADD);
            }else{
                //write human readible pcode
                writePcode("FADD\n");
            }
            break;
        case OP_FSUB:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_FSUB);
            }else{
                //write human readible pcode
                writePcode("FSUB\n");
            }
            break;
        case OP_MOD:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_MOD);
            }else{
                //write human readible pcode
                writePcode("MOD\n");
            }
            break;
        case OP_XCHG:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_XCHG);
            }else{
                //write human readible pcode
                writePcode("XCHG\n");
            }
            break;
        case OP_CVR:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_CVR);
            }else{
                //write human readible pcode
                writePcode("CVR\n");
            }
            break;
        case OP_CVI:
            if(this->binary){
                //write binary pcode
                writePcodeBinary(OP_CVI);
            }else{
                //write human readible pcode
                writePcode("CVI\n");
            }
            break;
        default:
            break;
    }
}

void Emitter::emit_int(int value){
    if(this->binary){
        //write binary int
        int i[1];
        i[0] = value;
        rv = write(fd, i, 4);
        if(rv == -1){
            printf("write in emit int failed with error [%s]\n", strerror(errno));
            exit(4);
        }
    }else{
        //write human readible int
        n = sprintf(bf, "%d\n", value);
        if(n == -1){
            exit(3);
        }
        rv = write(fd, bf, n);
        if(rv == -1){
            printf("write in emit int failed with error [%s]\n", strerror(errno));
            exit(4);
        }
    }
}

void Emitter::emit_real(int index, float poolOfReals[]){
    if(this->binary){
        //write binary real
        float i[1];
        i[0] = poolOfReals[index];
        rv = write(fd, i, 4);
        if(rv == -1){
            printf("write in emit real failed with error [%s]\n", strerror(errno));
            exit(4);
        }
    }else{
        //write human readible real
        n = sprintf(bf, "%f\n", poolOfReals[index]);
        if(n == -1){
            exit(3);
        }
        rv = write(fd, bf, n);
        if(rv == -1){
            printf("write in emit real failed with error [%s]\n", strerror(errno));
            exit(4);
        }
    }
}
