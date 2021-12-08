//
// Created by matthew on 11/29/21.
//

#ifndef PASCALCOMPILERLINUX_MYTOKENS_H
#define PASCALCOMPILERLINUX_MYTOKENS_H
using namespace std;

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
    TK_COLON = 116,
    TK_ASSIGN = 117,
    TK_SEMICOLON = 118,
    TK_FOR = 119,
    TK_UNKNOWN = 200
};

void printtoken(int curtoken, int curvalue, const string& curname) {
    switch (curtoken) {
        case TK_INTLIT:
            //printf("int lit %d \n", curvalue);
            cout << "Int lit" << curvalue << endl;
            break;
        case TK_REALLIT:
            //printf("real lit %f \n", (float)curvalue);
            cout << "Real lit" << curvalue << endl;
            break;
        case TK_CHARLIT:
            //printf("char lit %c \n", (char)curvalue);
            cout << "Char lit" << curvalue << endl;
            break;
        case TK_STRINGLIT:
            //printf("string lit %s \n", (char*)curvalue);
            cout << "String lit" << curvalue << endl;
            break;
        case TK_BEGIN:
            cout << "Begin body" << endl;
            break;
        case TK_END:
            cout << "End body" << endl;
            break;
        case TK_VAR:
            cout << "Starting var block" << endl;
            break;
        case TK_EOF:
            cout << "End of file" << endl;
            break;
        case TK_COMMA:
            cout << "Comma token" << endl;
            break;
        case TK_COLON:
            cout << "Colon token" << endl;
            break;
        case TK_ASSIGN:
            cout << "Assignment token" << endl;
            break;
        case TK_SEMICOLON:
            cout << "Semicolon token" << endl;
            break;
        case TK_FOR:
            cout << "for token" << endl;
            break;
        default:
            cout << "Unknown token: " << curname << endl;
            break;
    }
}

#endif //PASCALCOMPILERLINUX_MYTOKENS_H
