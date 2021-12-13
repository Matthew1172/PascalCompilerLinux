//
// Created by matthew on 11/29/21.
//

#ifndef PASCALCOMPILERLINUX_MYTOKENS_H
#define PASCALCOMPILERLINUX_MYTOKENS_H

#include <map>
using namespace std;

enum Tokens : int
{
    TK_EOF = 0,
    TK_BEGIN = 2,
    TK_END = 3,
    TK_PLUS = 40,
    TK_MINUS = 41,
    TK_MUL = 42,
    TK_DIV = 43,
    TK_MOD = 44,
    TK_EQ = 45,
    TK_NEQ = 46,
    TK_GT = 47,
    TK_LT = 48,
    TK_GTE = 49,
    TK_AND = 30,
    TK_BAND = 31,
    TK_OR = 32,
    TK_BOR = 33,
    TK_BNOT = 34,
    TK_LS = 35,
    TK_RS = 36,
    TK_LTE = 38,
    TK_NOT = 39,
    TK_COMMA = 50,
    TK_COLON = 51,
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
    TK_IF = 111,
    TK_DO = 112,
    TK_WHILE = 113,
    TK_ELSE = 114,
    TK_INT = 115,
    TK_ASSIGN = 117,
    TK_SEMICOLON = 118,
    TK_FOR = 119,
    TK_TO = 120,
    TK_RP = 121,
    TK_LP = 122,
    TK_THEN = 123,
    TK_UNKNOWN = 200
};

map<std::string , Tokens>  initSymTable(){
    std::map<std::string , Tokens> keywords;
    keywords["BEGIN"] = TK_BEGIN;
    keywords["END"] = TK_END;
    keywords["IF"] = TK_IF;
    keywords["ELSE"] = TK_ELSE;
    keywords["VAR"] = TK_VAR;
    keywords["DO"] = TK_DO;
    keywords["TO"] = TK_TO;
    keywords["WHILE"] = TK_WHILE;
    keywords["FOR"] = TK_FOR;
    keywords["INTEGER"] = TK_INT;
    keywords["THEN"] = TK_THEN;

    keywords["AND"] = TK_AND;
    keywords["OR"] = TK_OR;
    keywords["NOT"] = TK_NOT;
    return keywords;
}

void printtoken(int curtoken, int curvalue, const string& curname, string poolOfStrings[]) {
    switch (curtoken) {
        case TK_INTLIT:
            //printf("int lit %d \n", curvalue);
            cout << "Int lit " << curvalue << endl;
            break;
        case TK_REALLIT:
            //printf("real lit %f \n", (float)curvalue);
            cout << "Real lit " << curvalue << endl;
            break;
        case TK_CHARLIT:
            //printf("char lit %c \n", (char)curvalue);
            cout << "Char lit " << curvalue << endl;
            break;
        case TK_STRINGLIT:
            //printf("string lit %s \n", (char*)curvalue);
            cout << "String lit at "<< curvalue << ": \"" << poolOfStrings[curvalue] << "\"" << endl;
            break;
        case TK_BEGIN:
            cout << "Begin body token" << endl;
            break;
        case TK_END:
            cout << "End body token" << endl;
            break;
        case TK_VAR:
            cout << "Start var block token" << endl;
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
        case TK_IF:
            cout << "if token" << endl;
            break;
        case TK_ELSE:
            cout << "else token" << endl;
            break;
        case TK_TO:
            cout << "to token" << endl;
            break;
        case TK_DO:
            cout << "do token" << endl;
            break;
        case TK_RP:
            cout << "right parenthesis token" << endl;
            break;
        case TK_LP:
            cout << "left parenthesis token" << endl;
            break;
        case TK_INT:
            cout << "Integer type token" << endl;
            break;
        case TK_PLUS:
            cout << "token plus" << endl;
            break;
        case TK_MINUS:
            cout << "token minus" << endl;
            break;
        case TK_MUL:
            cout << "token multiply" << endl;
            break;
        case TK_DIV:
            cout << "token divide" << endl;
            break;
        case TK_MOD:
            cout << "token modulus" << endl;
            break;
        case TK_EQ:
            cout << "token equal" << endl;
            break;
        case TK_NEQ:
            cout << "token not equal" << endl;
            break;
        case TK_LTE:
            cout << "token less than or equal to" << endl;
            break;
        case TK_LS:
            cout << "token left shift" << endl;
            break;
        case TK_LT:
            cout << "token less than" << endl;
            break;
        case TK_GTE:
            cout << "token greater than or equal to" << endl;
            break;
        case TK_GT:
            cout << "token greater than" << endl;
            break;
        case TK_RS:
            cout << "token right shift" << endl;
            break;
        case TK_AND:
            cout << "token logical and" << endl;
            break;
        case TK_BAND:
            cout << "token binary and" << endl;
            break;
        case TK_OR:
            cout << "token logical or" << endl;
            break;
        case TK_BOR:
            cout << "token binary or" << endl;
            break;
        case TK_NOT:
            cout << "token logical not" << endl;
            break;
        case TK_BNOT:
            cout << "token binary not" << endl;
            break;
        case TK_THEN:
            cout << "token then" << endl;
            break;
        default:
            cout << "Unknown token: " << curname << endl;
            break;
    }
}

#endif //PASCALCOMPILERLINUX_MYTOKENS_H
