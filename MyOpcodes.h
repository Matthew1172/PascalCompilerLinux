//
// Created by matthew on 12/17/21.
//

#ifndef PASCALCOMPILERLINUX_MYOPCODES_H
#define PASCALCOMPILERLINUX_MYOPCODES_H

enum Opcodes : int
{
    OP_PUSH = 0,
    OP_POP = 1,
    OP_PUSHI = 2,
    OP_DUP = 3,
    OP_XCHG = 4,
    OP_PUT = 5,
    OP_GET = 6,
    OP_ADD = 7,
    OP_SUB = 8,
    OP_MUL = 9,
    OP_DIV = 10,
    OP_OR = 11,
    OP_AND = 12,
    OP_EQL = 13,
    OP_NEQ = 14,
    OP_GTR = 15,
    OP_LSS = 16,
    OP_GEQ = 17,
    OP_LEQ = 18,
    OP_FDIV = 98,
    OP_FMUL = 99,
    OP_FADD = 100,
    OP_FSUB = 101,
    OP_NEG = 102,
    OP_NOT = 103,
    OP_FNEG = 104,
    OP_CVR = 105,
    OP_CVI = 106,
    OP_HALT = 107,
    OP_JMP = 108,
    OP_JFALSE = 109,
    OP_JTRUE = 110,
    OP_JTAB = 111,
    OP_CALL = 112,
    OP_RET = 113,
    OP_PRINTINT = 114,
    OP_PRINTCHR = 115,
    OP_PRINTLN = 116,
    OP_MALLOC = 117,
    OP_FREE = 118
};

#endif //PASCALCOMPILERLINUX_MYOPCODES_H
