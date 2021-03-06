//
// Created by matthew on 11/29/21.
//

#ifndef PASCALCOMPILERLINUX_MYTOKENS_H
#define PASCALCOMPILERLINUX_MYTOKENS_H

#include <map>
#include <iostream>
using namespace std;

enum Tokens : int
{
    TK_EOF = 0,
    TK_BEGIN = 2,
    TK_END = 3,
    TK_DIVFL = 4,
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
    TK_XOR = 37,
    TK_LTE = 38,
    TK_NOT = 39,
    TK_COMMA = 50,
    TK_COLON = 51,
    TK_INTLIT = 100,
    TK_CHARLIT = 101,
    TK_REALLIT = 102,
    TK_STRINGLIT = 103,
    TK_DOT = 104,
    TK_LABEL = 106,
    TK_VAR = 107,
    TK_CONST = 108,
    TK_A_VAR = 109,
    TK_IF = 111,
    TK_DO = 112,
    TK_WHILE = 113,
    TK_ELSE = 114,
    TK_INT = 115,
    TK_REAL = 116,
    TK_ASSIGN = 117,
    TK_SEMICOLON = 118,
    TK_FOR = 119,
    TK_TO = 120,
    TK_RP = 121,
    TK_LP = 122,
    TK_THEN = 123,
    TK_FUNC = 124,
    TK_PROC = 125,
    TK_OBJ = 126,
    TK_BOOL = 127,
    TK_CHAR = 128,
    TK_GOTO = 129,
    TK_WRITE = 130,
    TK_UNKNOWN = 200
};

map<std::string , Tokens>  initSymTable(){
    std::map<std::string , Tokens> keywords;
    keywords["IF"] = TK_IF;
    keywords["THEN"] = TK_THEN;
    keywords["ELSE"] = TK_ELSE;
    keywords["WHILE"] = TK_WHILE;
    keywords["FOR"] = TK_FOR;
    keywords["DO"] = TK_DO;
    keywords["TO"] = TK_TO;
    keywords["GOTO"] = TK_GOTO;

    keywords["INTEGER"] = TK_INT;
    keywords["REAL"] = TK_REAL;
    keywords["BOOL"] = TK_BOOL;
    keywords["CHAR"] = TK_CHAR;

    keywords["BEGIN"] = TK_BEGIN;
    keywords["END"] = TK_END;

    keywords["VAR"] = TK_VAR;
    keywords["PROCEDURE"] = TK_PROC;
    keywords["FUNCTION"] = TK_FUNC;
    keywords["LABEL"] = TK_LABEL;
    keywords["CONST"] = TK_CONST;

    keywords["WRITE"] = TK_WRITE;

    keywords["AND"] = TK_AND;
    keywords["OR"] = TK_OR;
    keywords["NOT"] = TK_NOT;
    keywords["DIV"] = TK_DIVFL;
    return keywords;
}

void printtoken(int curtoken, int curvalue, const string& curname, string poolOfStrings[], float poolOfReals[]) {
    switch (curtoken) {
        case TK_INTLIT:
            //printf("int lit %d \n", curvalue);
            cout << "Int lit " << curvalue << endl;
            break;
        case TK_REALLIT:
            //printf("real lit %f \n", (float)curvalue);
            cout << "Real lit at "<< curvalue << ": " << poolOfReals[curvalue] << endl;
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
        case TK_DIVFL:
            cout << "token floor divide" << endl;
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
        case TK_DOT:
            cout << "DOT token" << endl;
            break;
        case TK_FUNC:
            cout << "Function declaration token" << endl;
            break;
        case TK_PROC:
            cout << "Procedure declaration token" << endl;
            break;
        case TK_OBJ:
            cout << "Object declaration token" << endl;
            break;
        case TK_LABEL:
            cout << "Label declaration token" << endl;
            break;
        case TK_CONST:
            cout << "Constant declaration token" << endl;
            break;
        case TK_GOTO:
            cout << "GOTO token" << endl;
            break;
        case TK_WRITE:
            cout << "Write token" << endl;
            break;
        default:
            cout << "Unknown token: " << curname << endl;
            break;
    }
}

#endif //PASCALCOMPILERLINUX_MYTOKENS_H
