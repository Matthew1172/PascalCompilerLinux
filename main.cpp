#define DEBUG 1
#define error() printf("There was an error!")

#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <sys/stat.h>
#include <cstring>
//token list
#include <vector>
#include "MyTokens.h"
#include "MyVariable.h"
#include "MyCatCodes.h"
//symbol table
#include <map>

using namespace std;

void initialize();
void gettoken();
//void printtoken();


int curtoken;
int curvalue;
const short MAXNAME = 31;
std::string curname;
int curfile; // file index
int curline; // current line number
int curcol; // current column number

char* scanp;
int line;
int col;


std::map<std::string , Tokens> keywords;

void compile();
void header();
void declarations();
void begin_statement();
void match(Tokens t);
void emit_opcode(Tokens t);

void label_declaration();
void var_declaration();
void const_declaration();

void varList();

int main() {
/*
    initialize();
    gettoken();
    compile();
*/
    initialize();
do {
    gettoken();
    printtoken(curtoken, curvalue, curname);
} while (curtoken != TK_EOF);

}

void compile(){
    //header();
    declarations();
    //begin_statement();
    //match(TK_DOT);
    //emit_opcode(OP_HALT);
}

void declarations(){
    restart:
    switch(curtoken){
        case TK_LABEL:
            label_declaration(); goto restart;
        case TK_VAR:
            var_declaration(); goto restart;
        case TK_CONST:
            const_declaration(); goto restart;
        default:
            return;
    }
}

void var_declaration(){
    match(TK_VAR);
    restart:
    if(curtoken!=TK_UNKNOWN){
        //error();
        return;
    }
    auto* v = new std::vector<char*>;
    //v->push_back(curname);

    varList();

    if(DEBUG) printf("We have an unknown token");

    if(curtoken == TK_UNKNOWN) goto restart;
}

void varList(){
    match(TK_UNKNOWN);

}

void match(Tokens t){
    if(curtoken != t){
        error();
        return;
    }
    if(DEBUG) printf("match");
    gettoken();
}

void label_declaration(){

}

void const_declaration(){

}

void gettoken() {
    char c;
    int i1;
    restart:
    switch (catcode[c = *scanp++]) {
        case 'C':
            //comma
            curtoken = TK_COMMA;
            break;
        case 'I':
            //semicolon
            curtoken = TK_SEMICOLON;
            break;
        case 'A':
            //we see a colon. Could either be assigning type or assigning value to a variable
            //check the next byte to see if it is a space or an equal sign
            switch(c = *scanp++){
                case ' ':
                    //it is assigning a type to a variable
                    curtoken = TK_COLON;
                    break;
                case '=':
                    curtoken = TK_ASSIGN;
                    break;
                default:
                    break;
            }
            break;
        case 'L':
            //letter
            /*
            copy characters that may occur in an identifier to curname, truncating
            those beyond MAXNAME, while advancing scanp; at the end of this step
            scanp should point to the first character beyond the identifier.
            */
            i1 = 0;
            curname.clear();
            curname += c;
            i1++;
        r2:
            switch (catcode[c = *scanp++]) {
                //if it is not a letter, digit, or underscore
                //then stop scanning, check keyword symbol table, check variable symbol table
                //assign token, rollback scanp by 1 byte, return to main loop
                case 'L':
                    //letter
                case 'D':
                    //digit
                    if (i1 <= MAXNAME) {
                        curname += c;
                        i1++;
                    }
                    goto r2;
                case 'A':
                    //we see a colon. Could either be assigning type or assigning value to a variable
                    //check the next byte to see if it is a space or an equal sign

                    switch(c = *scanp++){
                        case ' ':
                            //it is assigning a type to a variable
                            curtoken = TK_COLON;
                            break;
                        case '=':
                            curtoken = TK_ASSIGN;
                            break;
                        default:
                            break;
                    }
                    break;
                case 'I':
                    //semicolon
                    curtoken = TK_SEMICOLON;
                    //break;
                case 'C':
                    //comma
                    curtoken = TK_COMMA;
                    //break;
                case 'S':
                    //space
                    /*
                    we know that this is the end of the token, so
                    print the token and then return from gettoken(), but before that
                    check if curname is equal to "BEGIN" or "END" or "IF" or "WHILE"
                    if it is, set the appropriate curtoken value, and if it isnt then
                    set current token to unknown
                    */
                case 'N':
                    //new line
                    /*
                    we know that this is the end of the token, so
                    print the token and then return from gettoken(), but before that
                    check if curname is equal to "BEGIN" or "END" or "IF" or "WHILE"
                    if it is, set the appropriate curtoken value, and if it isnt then
                    set current token to unknown
                    */
                    //check the keyword symbol table for curname as key
                    if(keywords[curname] == 0){
                        //unknown token, and cannot be EOF
                        curtoken = TK_UNKNOWN;
                    }else {
                        //token is a keyword
                        curtoken = keywords[curname];
                    }
                    return;
                case 0:
                    curtoken = TK_EOF;
                default:
                    //don't know what this token is
                    curtoken = TK_UNKNOWN;
                    return;
            }
            break;
        case 'S':
            //space
        case 'N':
            //new line
            goto restart;
        case 0:
            curtoken = TK_EOF;
    }

}

void initialize() {
    char filepath[] = "PascalTest2.txt";
    int rv;
    rv = access(filepath, F_OK);
    if(rv != 0){
        if(errno == ENOENT) printf("%s does not exist. \n", filepath);
        else if(errno == EACCES) printf("%s is inaccessible. \n", filepath);
        exit(1);
    }
    int fd = open(filepath, O_RDONLY);
    if(fd == -1){
        printf("open() failed with error [%s]\n", strerror(errno));
        exit(2);
    }
    if(DEBUG) printf("open() successful! \n");
    struct stat stbuf{};
    stat(filepath, &stbuf);
    const unsigned long filesize = stbuf.st_size;
    if(DEBUG) printf("Filesize is: %lu \n", filesize);
    auto* bf = (char*) calloc(filesize, 1);
    long sz = read(fd, bf, filesize);

    bf[sz] = '\n';
    scanp = bf;
    line = 1;
    col = 1;


    //initialize the keyword symbol table

    keywords["BEGIN"] = TK_BEGIN;
    keywords["END"] = TK_END;
    keywords["IF"] = TK_IF;
    keywords["ELSE"] = TK_ELSE;
    keywords["VAR"] = TK_VAR;
    keywords["DO"] = TK_DO;
    keywords["WHILE"] = TK_WHILE;

}

