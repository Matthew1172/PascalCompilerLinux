#define DEBUG 1
#define error() printf("There was an error!")

//for transform() to turn a string to all uppercase
#include <algorithm>

#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <sys/stat.h>
#include <cstring>
//token list
//#include <vector>
#include <list>
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

const short MAXSTRINGS = 100;
string poolOfStrings[MAXSTRINGS];
int stringIndex = 0;

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
    printtoken(curtoken, curvalue, curname, poolOfStrings);
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
    //auto* v = new std::vector<char*>;
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

    int value;
    int base;

    string curstring;
    string key;

    restart:
    switch (catcode[c = *scanp++]) {
        case 'O':
            //operator
            switch(c){
                case '+':
                    curtoken = TK_PLUS;
                    break;
                case '-':
                    curtoken = TK_MINUS;
                    break;
                case '*':
                    curtoken = TK_MUL;
                    break;
                case '/':
                    curtoken = TK_DIV;
                    break;
                case '%':
                    curtoken = TK_MOD;
                    break;
                case '=':
                    curtoken = TK_EQ;
                    break;
                case '<':
                    //Could be not equal, or less than, or less than/equal to, Left shift
                    switch(c=*scanp++){
                        case '>':
                            //not equal
                            curtoken = TK_NEQ;
                            break;
                        case '=':
                            //less than or equal to
                            curtoken = TK_LTE;
                            break;
                        case '<':
                            //Left shift
                            curtoken = TK_LS;
                            break;
                        default:
                            //strictly less than
                            curtoken = TK_LT;
                            break;
                    }
                    *scanp--;
                    break;
                case '>':
                    //Could be greater than, or greater than/equal to, or right shift
                    switch(c=*scanp++){
                        case '=':
                            //greater than or equal to
                            curtoken = TK_GTE;
                            break;
                        case '>':
                            //Right shift
                            curtoken = TK_RS;
                            break;
                        default:
                            //strictly greater than
                            curtoken = TK_GT;
                            break;
                    }
                    *scanp--;
                    break;
                case '&':
                    //binary AND
                    curtoken = TK_BAND;
                    break;
                case '|':
                    //binary OR
                    curtoken = TK_BOR;
                    break;
                case '~':
                    //binary NOT
                    curtoken = TK_BNOT;
                    break;
                default:
                    //we don't know what this is. Shouldn't get here.
                    curtoken = TK_UNKNOWN;
                    break;
            }
            break;
        case 'Q':
            //single quote
            //check if it is a char lit, aka only 1 character between single quotes like 'a' or ''''

            if(stringIndex >= MAXSTRINGS){
                cout << "Too many strings in program" << endl;
                exit(-555);
            }
            //don't handle empty strings
            //if it is a char lit, then *scanp+2 should be another single quote. If it is, then
            //make *scanp++ a charlit, save ascii value of character in curvalue, and do scanp++;
            r3:
            switch(catcode[c = *scanp++]){
                case 'Q':
                    //check if next character after it is a single quote, if it is then it is an escape
                    c = *scanp++;
                    if(c != '\'' && curstring.length() == 1){
                        //this is not an escape sequence, could be a charlit
                            //don't take into account ''' character
                            //this is a character
                            curtoken = TK_CHARLIT;
                            curvalue = (unsigned char) curstring[0];
                            curstring = "";
                            return;
                    }else if(c != '\''){
                            //this is not an escape sequence, set the string and curtoken and return
                            poolOfStrings[stringIndex] = curstring;
                            curvalue = stringIndex;
                            stringIndex++;
                            curtoken = TK_STRINGLIT;
                            *scanp--;
                            curstring = "";
                            return;
                    }
                default:
                    curstring += c;
                    goto r3;
            }
            break;
        case 'P':
            //right or left parenthesis
            if(c == '('){
                curtoken = TK_LP;
            }else{
                curtoken = TK_RP;
            }
            break;
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
        case 'D':
            //scan ahead, and use whatever can be part of the number. Collect all digits and look for special cases like .
            //which would mean real. like letter 'e' which means real also, and perhaps something else like # to denote numbers in different bases.
            //collect number together, determine what constatnt you got, and return that constant.

            value=0;
            base=10;
            while (c>='0'&&c<='9') {
                value=value*base+c-'0';
                c=*scanp++;
            }
            switch(c){
                case '.':
                case 'E':
                    //reallit
                    curtoken = TK_REALLIT;
                    break;
                default:
                    //end of number, intlit
                    curvalue = value;
                    curtoken = TK_INTLIT;
                    break;
            }
            *scanp--;
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

                default:
                    //we saw a token that wasn't a letter underscore or digit.
                    //check the keyword symbol table for curname as key
                    key = curname;
                    transform(key.begin(), key.end(),key.begin(), ::toupper);
                    if(keywords[key] == 0){
                        //unknown token, and cannot be EOF
                        curtoken = TK_UNKNOWN;
                    }else {
                        //token is a keyword
                        curtoken = keywords[key];
                    }
                    *scanp--;
                    break;
            }
            break;
        case 'S':
            //space
            goto restart;
        case 'N':
            //new line
            curline++;
            goto restart;
        case 0:
            curtoken = TK_EOF;
            break;
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
    keywords = initSymTable();

}

