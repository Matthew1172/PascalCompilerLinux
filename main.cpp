#define DEBUG 1
#define error() printf("There was an error!")

//#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

//for toupper();
//#include <ctype.h>
//for memset();
//#include <memory.h>
//for strcmp();
#include <string.h>
#include <malloc.h>

//token list
#include <vector>
#include "MyVariable.h"
//symbol table
#include <map>

void initialize();
void initCharArray();
void gettoken();
void printtoken();


int curtoken;
int curvalue;
const short MAXNAME = 31;
//char curname[MAXNAME];
std::string curname;
int curfile; // file index
int curline; // current line number
int curcol; // current column number

char* scanp;
int line;
int col;

char catcode[256] = {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        'N', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, 'S', NULL, NULL, NULL, NULL, NULL, 'O', NULL, NULL, NULL, 'O', 'O', 'C', 'O', 'O', 'O', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
        'A', NULL, 'O', 'O', 'O', NULL, NULL, 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L',
        NULL, NULL, NULL, NULL, 'L', NULL,
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', NULL, NULL, NULL, NULL, NULL
};


std::map<std::string , int> keywords;

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
    printtoken();
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
        case 'L':
            //letter
            /*
            copy characters that may occur in an identifier to curname, truncating
            those beyond MAXNAME, while advancing scanp; at the end of this step
            scanp should point to the first character beyond the identifier.
            */
            i1 = 0;
            //memset(curname, 0, sizeof curname);
            curname.clear();
            //curname[i1++] = c;
            curname += c;
            i1++;
        r2:
            switch (catcode[c = *scanp++]) {
                case 'L':
                    //letter

                case 'D':
                    //digit
                    if (i1 <= MAXNAME) {
                        //curname[i1++] = c;
                        curname += c;
                        i1++;
                    }
                    goto r2;
                case 'C':
                    //comma
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



                    //check the keyword symbol table
/*                    if (curname == "BEGIN") {
                        curtoken = TK_BEGIN;
                    }
                    else if (curname == "END") {
                        curtoken = TK_END;
                    }else if (strcmp(curname, "VAR") == 0){
                        //now we expect a code block to follow
                        curtoken = TK_VAR;
                    }
                    else {
                        curtoken = TK_UNKNOWN;
                    }
                    */
                    //assign token from keyword symbol table to curtoken
                    //curtoken = keywords.at(curname);
                    curtoken = keywords[curname];


                    //printf("the token is: %s", curname);
                    //printf("the token is: %d \n", curtoken);
                    return;
                case 0:
                    curtoken = TK_EOF;
                default:
                    //don't know what this token is
                    curtoken = TK_UNKNOWN;
                    return;
            }
        case 'S':
            //space
            //goto restart;
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


    keywords["IF"] = TK_IF;
    keywords["ELSE"] = TK_IF;
    keywords["VAR"] = TK_VAR;


}

void printtoken() {
    switch (curtoken) {
        case TK_INTLIT:
            printf("int lit %d \n", curvalue);
            break;
        case TK_REALLIT:
            printf("real lit %f \n", (float)curvalue);
            break;
        case TK_CHARLIT:
            printf("char lit %c \n", (char)curvalue);
            break;
        case TK_STRINGLIT:
            printf("string lit %s \n", (char*)curvalue);
            break;
        case TK_BEGIN:
            printf("begin, begin \n");
            break;
        case TK_END:
            printf("end, end \n");
            break;
        case TK_EOF:
            printf("End of file \n");
            break;
    }
}