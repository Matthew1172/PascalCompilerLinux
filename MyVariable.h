//
// Created by matthew on 11/29/21.
//

#ifndef PASCALCOMPILERLINUX_MYVARIABLE_H
#define PASCALCOMPILERLINUX_MYVARIABLE_H


#include "MyTokens.h"

class MyVariable {
public:
    Tokens token_type;
    bool flag = true;
    Tokens type;
    int size;
    int address;
    char name[];
};


#endif //PASCALCOMPILERLINUX_MYVARIABLE_H
