//
// Created by matthew on 12/17/21.
//

#ifndef PASCALCOMPILERLINUX_EMITTER_H
#define PASCALCOMPILERLINUX_EMITTER_H
//for linux syscall
#include <cstdlib>
//for opening file using linux syscall
#include <fcntl.h>
//for linux syscall
#include <unistd.h>
//for linux syscalls
#include <cerrno>
//for printing tokens
#include <iostream>
//for strerror
#include <cstring>
//for OPCODES
#include "../MyOpcodes.h"
//for Types
#include "../MyTypes.h"

class Emitter {
private:
    int fd;
    ssize_t rv;
    char bf[15];
    size_t n;
    char filepath[100];
public:
    Emitter();
    explicit Emitter(std::string outputFilePath);
    ~Emitter();
    void setFilepath(const std::string& outputFilePath);
    void createOutputFile();
    void closeOutputFile();
    void checkOutputFileAccess();
    void emit_opcode(Opcodes op);
    void emit_int(int value);
    void emit_real(int index, float poolOfReals[]);
    void stringToBuffer(std::string code);
    void printOpcodeError();
};


#endif //PASCALCOMPILERLINUX_EMITTER_H
