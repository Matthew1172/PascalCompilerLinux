//
// Created by matthew on 12/18/21.
//

#ifndef PASCALCOMPILERLINUX_MYEMULATOR_H
#define PASCALCOMPILERLINUX_MYEMULATOR_H
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
//to get file size using linux syscall
#include <sys/stat.h>
//for OPCODES
#include "MyOpcodes.h"

//#define MAXCODE 0x100000
using namespace std;

class MyEmulator {
private:
    char fp[100];
    int fd;
    ssize_t rv;
    unsigned long MAXCODE;

    typedef unsigned char byte;
    typedef unsigned short word;

    word SP = 0x0000, BP = 0x0000, SI = 0x0000, DI = 0x0000;
    word flags = 0x0000, IP = 0x0000, ES = 0x0000, SS = 0x0000, DS = 0x0000, CS = 0x0000;

    byte opcode = 0x00;
    byte* CODE;
    byte* STACK;
    byte* DATA;

public:
    MyEmulator();
    explicit MyEmulator(string fp);
    void setFilepath(string fp);
    void readPcodeFile();
    void closePcodeFile();
    void emulate();

};


#endif //PASCALCOMPILERLINUX_MYEMULATOR_H
