//
// Created by matthew on 12/17/21.
//

#include "Emitter.h"
using namespace std;


Emitter::Emitter() {
}

Emitter::Emitter(std::string outputFilePath) {
    setFilepath(outputFilePath);
    createOutputFile();
}

Emitter::~Emitter() {
    closeOutputFile();
}

void Emitter::setFilepath(const std::string& outputFilePath) {
    if(outputFilePath.length() > 100){
        //filename too large
        exit(-5);
    }
    //initialize filepath from string
    strcpy(filepath, outputFilePath.c_str());
    //check access
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
    }else{
        printf ("File: %s already exists!\n", filepath);
        exit(-10);
    }
}

void Emitter::createOutputFile() {
    fd = open(filepath, O_WRONLY | O_CREAT, 0777);
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

void Emitter::emit_opcode(Opcodes op){
    switch(op){
        case OP_PUSHI:
            stringToBuffer("PUSHI ");
            rv = write(fd, bf, n);
            if(rv == -1) printOpcodeError();
            break;
        case OP_ADD:
            stringToBuffer("ADD\n");
            rv = write(fd, bf, n);
            if(rv == -1) printOpcodeError();
            break;
        case OP_MUL:
            stringToBuffer("MUL\n");
            rv = write(fd, bf, n);
            if(rv == -1) printOpcodeError();
            break;
        case OP_XCHG:
            stringToBuffer("XCHG\n");
            rv = write(fd, bf, n);
            if(rv == -1) printOpcodeError();
            break;
        case OP_CVR:
            stringToBuffer("CVR\n");
            rv = write(fd, bf, n);
            if(rv == -1) printOpcodeError();
            break;
        case OP_FMUL:
            stringToBuffer("FMUL\n");
            rv = write(fd, bf, n);
            if(rv == -1) printOpcodeError();
            break;
        case OP_FADD:
            stringToBuffer("FADD\n");
            rv = write(fd, bf, n);
            if(rv == -1) printOpcodeError();
            break;
        default:
            break;
    }
}

void Emitter::emit_int(int value){
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

void Emitter::emit_real(int index, float poolOfReals[]){
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