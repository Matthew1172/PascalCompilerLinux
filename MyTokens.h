//
// Created by matthew on 11/29/21.
//

#ifndef PASCALCOMPILERLINUX_MYTOKENS_H
#define PASCALCOMPILERLINUX_MYTOKENS_H
enum Tokens : int
{
    TK_EOF = 0,
    TK_BEGIN = 2,
    TK_END = 3,
    TK_INTLIT = 100,
    TK_CHARLIT = 101,
    TK_REALLIT = 102,
    TK_STRINGLIT = 103,
    TK_DOT = 104,
    OP_HALT = 105,
    TK_LABEL = 106,
    TK_VAR = 107,
    TK_CONST = 108,
    TK_A_VAR = 109,
    TK_COMMA = 110,
    TK_IF = 111,
    TK_DO = 112,
    TK_WHILE = 113,
    TK_ELSE = 114,
    TK_INT = 115,
    TK_UNKNOWN = 200
};
#endif //PASCALCOMPILERLINUX_MYTOKENS_H
