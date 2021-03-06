#define DEBUG 1
#define BINARY 1
#define EXP_PARSER 0

/*
//check symbol table, could be a variable
if(vars.find(curname) != vars.end()){
    //it is a variable in the symbol table
    curtoken = vars[curname].getTokenType();
}else{
}*/

//for transform() to turn a string to all uppercase
#include <algorithm>
//for printing tokens
#include <iostream>
//for linux syscall
#include <cstdlib>
//for opening file using linux syscall
#include <fcntl.h>
//for linux syscall
#include <unistd.h>
//for linux syscalls
#include <cerrno>
//to get file size using linux syscall
#include <sys/stat.h>
//for tokens
#include <cstring>
//symbol table for keywords and identifiers
#include <map>
//need pow for real lit
#include <cmath>
//temporary token list
#include <vector>
//the emitter
#include "cmake-build-debug/Emitter.h"
//my pascal tokens
#include "MyTokens.h"
//categories for ascii characters
#include "MyCatCodes.h"
//data types for my pascal
#include "MyTypes.h"
//pcode opcodes
#include "MyOpcodes.h"
//pcode machine
#include "MyEmulator.h"

using namespace std;

class MyVar {
private:
    string name;
    Tokens token_type;
    bool staticType = false;
    Types type;
    short size;
    size_t address;
    int flags;
    int initial = 0;
public:
    MyVar();
    MyVar(string name);
    void setAddress(size_t add);
    void setSize(short size);
    void setTokenType(Tokens t);
    void setDataType(Types t);
    string getName();
    Tokens getTokenType();
};

MyVar::MyVar(string name) {
    this->name = name;
}

void MyVar::setAddress(size_t add) {
    this->address = add;
}

void MyVar::setSize(short size) {
    this->size = size;
}

void MyVar::setTokenType(Tokens t) {
    this->token_type = t;
}

void MyVar::setDataType(Types t) {
    this->type = t;
}

MyVar::MyVar() {

}

string MyVar::getName() {
    return this->name;
}

Tokens MyVar::getTokenType() {
    return this->token_type;
}


string pascal = "";
string pcode = "";
//Emitter *MyEmitter = new Emitter(pcode, 1);
Emitter *MyEmitter = new Emitter(BINARY);

const long MAXFILEPATH = 500;

//source program
int fd;

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
const short MAXSTRINGS = 100;
string poolOfStrings[MAXSTRINGS];
int stringIndex = 0;
const short MAXREALS = 100;
float poolOfReals[MAXREALS];
int realIndex = 0;
map<string , Tokens> keywords;
map<string, MyVar> vars;
size_t address = 0;

void initialize();
void gettoken();

void compile();
void header();
void declarations();
void begin_statement();

void label_declaration();
void var_declaration();
void const_declaration();
void error();

void G();
Types E();
Types T();
Types F();

Types do_XOR(Types arg1, Types arg2);
Types do_OR(Types arg1, Types arg2);
Types do_SUB(Types arg1, Types arg2);
Types do_ADD(Types arg1, Types arg2);
Types do_MUL(Types arg1, Types arg2);
Types do_DIV(Types arg1, Types arg2);
Types do_DIVFL(Types arg1, Types arg2);
Types do_MOD(Types arg1, Types arg2);
Types do_AND(Types arg1, Types arg2);
void match(Tokens t);

void if_statement();
void while_statement();
void goto_statement();
void assignment();
void write_statement();



















int main(int argc, char** argv) {
    if(argc < 3){
        cout << "Directions for use: " << endl;
        cout << "$ ./PascalCompilerLinux <input file> <output file>" << endl;
        exit(1);
    }
    pascal = argv[1];
    pcode = argv[2];
    MyEmitter->setFilepath(pcode);

    initialize();
    gettoken();
    if(EXP_PARSER){
        G();
    }else{
        compile();
    }

    //close file
    if(close(fd) != 0){
        strerror(errno);
        exit(-555);
    }
    printf("close() source file successful! \n");

    if(BINARY){
        //Create an emulator from the pcode file we just created
        MyEmulator* emulator = new MyEmulator(pcode);
        emulator->emulate();
    }else{
        cout << "Binary flag in source code is set to false. Check the output file for human readible pcode. To emulate this code, set the BINARY flag to 1 in source code." << endl;
    }
    exit(0);
}

void error() {
    printf("\n\n\nSyntax error! line: %d", curline);
    exit(-1);
}



















/*
 *
 * BEGIN PARSER
 *
 *
 */



void compile(){
    //header();
    declarations();
    begin_statement();
    match(TK_DOT);
    MyEmitter->emit_opcode(OP_HALT);
}

void header(){
    return;
}

void declarations(){
    restart:
    switch(curtoken){
        case TK_VAR:
            var_declaration();
            goto restart;
        case TK_CONST:
            const_declaration();
            goto restart;
        case TK_LABEL:
            label_declaration();
            goto restart;
        case TK_PROC:
            break;
        case TK_FUNC:
            break;
        case TK_OBJ:
        break;
        default:
            return;
    }
}

void var_declaration(){
    match(TK_VAR);
    restart:
    if(curtoken!=TK_UNKNOWN){
        error();
        exit(-123);
    }

    vector<string> *v = new vector<string>;
    size_t tempaddr = 0;
    //parse alternating sequence of TK_UNKNOWN and TK_COMMA
    while(curtoken == TK_UNKNOWN || curtoken == TK_COMMA){
        if(curtoken == TK_UNKNOWN ){
            if(!count(v->begin(), v->end(), curname)
               && vars.find(curname) == vars.end()){
                v->push_back(curname);
                tempaddr++;
            }
        }
        gettoken();
    }
    if(curtoken != TK_COLON){
        error();
    }
    //read type declaration
    gettoken();
    //we have the data type of all the vars just declared
    //we have a 'vars' symbol table with all the names
    MyVar var;
    int i = address;
    switch(curtoken){
        case TK_INT:
            address += tempaddr*4;
            for(const string& s : *v){
                var = MyVar(s);
                var.setDataType(TP_INT);
                var.setTokenType(TK_A_VAR);
                var.setAddress(i);
                var.setSize(4);
                vars[s] = var;
                i+=4;
            }
            break;
        case TK_REAL:
            address += tempaddr*4;
            for(const string& s : *v){
                var = MyVar(s);
                var.setDataType(TP_REAL);
                var.setTokenType(TK_A_VAR);
                var.setAddress(i);
                var.setSize(4);
                vars[s] = var;
                i+=4;
            }
            break;
        case TK_BOOL:
            break;
        case TK_CHAR:
            address += tempaddr*1;
            for(const string& s : *v){
                var = MyVar(s);
                var.setDataType(TP_CHAR);
                var.setTokenType(TK_A_VAR);
                var.setAddress(i);
                var.setSize(1);
                vars[s] = var;
                i+=1;
            }
            break;
        default:
            break;
    }

    v->clear();
    gettoken();
    match(TK_SEMICOLON);
    if(curtoken == TK_UNKNOWN){
        goto restart;
    }
}

void label_declaration(){

}

void const_declaration(){

}

void begin_statement(){
    match(TK_BEGIN);
    restart:
    switch (curtoken) {
        case TK_IF:
            if_statement(); goto restart;
        case TK_WHILE:
            while_statement(); goto restart;
        case TK_GOTO:
            goto_statement(); goto restart;
        case TK_A_VAR:
            assignment(); goto restart;
        case TK_WRITE: // notice: TK_WRITE is not a keyword!
            write_statement(); goto restart;
        default:
            break;
    }
    match(TK_END);
}

void if_statement(){}
void while_statement(){}
void goto_statement(){}
void assignment(){}
void write_statement(){}

void match(Tokens t){
    if(curtoken != t){
        error();
    }
    if(DEBUG) printtoken(curtoken, curvalue, curname, poolOfStrings, poolOfReals);
    gettoken();
}


/*
E ??? E + T | E ??? T | T
T ??? T ??? F | T/F | F
F ??? eps | ??? F | (E) | LIT | VAR
*/

/*

G ??? E EOF
E ??? TE'
E' ??? +TE' | ???TE' | eps
T ??? FT'
T' ??? ???FT | /TF | eps
F ??? +F | ???F | (E) | LIT | VAR
*/

/*
G ??? E EOF
E ??? T E'
E' ??? +T [ADD] E' | ???T [SUB] E' | eps
T ??? FT'
T' ??? ???F [MUL] T | /T [DIV] F | eps
F ??? +F [NOP] | ???F [NEG] | (E) | LIT [LIT]
*/
//G ??? E EOF
void G() {
    E();
    match(TK_END);
    match(TK_DOT);
    match(TK_EOF);
    MyEmitter->emit_opcode(OP_HALT);
}

//E ??? T E'
//E' ??? +T [ADD] E' | ???T [SUB] E' | eps
Types E() {
    Types t1; // type of 1st argument
    Types t2; // type of 2nd argument
    t1=T();
    while(curtoken==TK_PLUS
    ||curtoken==TK_MINUS
    ||curtoken==TK_OR
    ||curtoken==TK_XOR) {
        switch(curtoken) {
            case TK_PLUS:
                match(TK_PLUS);
                t2=T();
                t1=do_ADD(t1,t2);
                break;
            case TK_MINUS:
                match(TK_MINUS);
                t2=T();
                t1=do_SUB(t1,t2);
                break;
            case TK_OR:
                match(TK_OR);
                t2=T();
                t1=do_OR(t1,t2);
                break;
            case TK_XOR:
                match(TK_XOR);
                t2=T();
                t1=do_XOR(t1,t2);
                break;
            default:
                break;
        }
    }
    return t1;
}

//T ??? FT'
//T' ??? ???F [MUL] T | /T [DIV] F | eps
Types T(){
    Types t1; // type of 1st argument
    Types t2; // type of 2nd argument
    t1=F();
    while(curtoken==TK_MUL
    ||curtoken==TK_DIV
    ||curtoken==TK_DIVFL
    ||curtoken==TK_AND
    ||curtoken==TK_MOD) {
        switch(curtoken) {
            case TK_MUL:
                match(TK_MUL);
                t2=T();
                t1=do_MUL(t1,t2);
                break;
            case TK_DIV:
                //real division
                match(TK_DIV);
                t2=T();
                t1=do_DIV(t1,t2);
                break;
            case TK_DIVFL:
                //floor division
                match(TK_DIVFL);
                t2=T();
                t1=do_DIVFL(t1,t2);
                break;
            case TK_AND:
                match(TK_AND);
                t2=T();
                t1=do_AND(t1,t2);
                break;
            case TK_MOD:
                match(TK_MOD);
                t2=T();
                t1=do_MOD(t1,t2);
                break;
            default:
                break;
        }
    }
    return t1;
}

//F ??? +F [NOP] | ???F [NEG] | not F [NOT] | (E) | LIT [LIT]
Types F(){
    Types expT;
    switch (curtoken) {
        case TK_PLUS:
            match(TK_PLUS);
            expT = F();
            break;
        case TK_MINUS:
            match(TK_MINUS);
            expT = F();
            //check what type we're negating
            switch(expT){
                case TP_INT:
                    MyEmitter->emit_opcode(OP_NEG);
                    break;
                case TP_REAL:
                    MyEmitter->emit_opcode(OP_FNEG);
                case TP_BOOL:
                default:
                    break;
            }
            break;
        case TK_NOT:
            //handle boolean and integer cases
            match(TK_NOT);
            expT = F();
            break;
        case TK_LP:
            match(TK_LP);
            expT = E();
            match(TK_RP);
            break;
        case TK_INTLIT:
            //we know the type. TK_INTLIT, TK_REALINT, ...
            //put it on the stack and define current type to be whatever the token tells us
            MyEmitter->emit_opcode(OP_PUSHI);
            MyEmitter->emit_int(curvalue);
            match(TK_INTLIT);
            expT = TP_INT;
            break;
        case TK_REALLIT:
            MyEmitter->emit_opcode(OP_FPUSHI);
            MyEmitter->emit_real(curvalue, poolOfReals);
            match(TK_REALLIT);
            expT = TP_REAL;
            break;
        case TK_A_VAR:
            break;
        case TK_FUNC:
            break;
        default:
            break;
    }
    return expT;
}

Types do_XOR(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT) {
        return TP_INT;
    }else if(arg1 == TP_BOOL && arg2 == TP_BOOL){
        return TP_BOOL;
    }else{
        error();
        exit(-555);
    }
}

Types do_OR(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT) {
        return TP_INT;
    }else if(arg1 == TP_BOOL && arg2 == TP_BOOL){
        return TP_BOOL;
    }else{
        error();
        exit(-555);
    }
}

Types do_SUB(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_SUB);
        return TP_INT;
    }else if(arg1 == TP_INT && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_FSUB);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_FSUB);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_FSUB);
        return TP_REAL;
    }else{
        error();
        exit(-555);
    }
}

Types do_ADD(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_ADD);
        return TP_INT;
    }else if(arg1 == TP_INT && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_FADD);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_FADD);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_FADD);
        return TP_REAL;
    }else{
        error();
        exit(-555);
    }
}

Types do_MUL(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_MUL);
        return TP_INT;
    }else if(arg1 == TP_INT && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_FMUL);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_FMUL);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_FMUL);
        return TP_REAL;
    }else{
        error();
        exit(-555);
    }
}

Types do_DIV(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_FDIV);
        return TP_REAL;
    }else if(arg1 == TP_INT && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_XCHG);
        MyEmitter->emit_opcode(OP_FDIV);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_CVR);
        MyEmitter->emit_opcode(OP_FDIV);
        return TP_REAL;
    }else if(arg1 == TP_REAL && arg2 == TP_REAL){
        MyEmitter->emit_opcode(OP_FDIV);
        return TP_REAL;
    }else{
        error();
        exit(-555);
    }
}

Types do_DIVFL(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_DIV);
        return TP_INT;
    }else{
        error();
        exit(-555);
    }
}

Types do_MOD(Types arg1, Types arg2){
    if(arg1 == TP_INT && arg2 == TP_INT){
        MyEmitter->emit_opcode(OP_MOD);
        return TP_INT;
    }else{
        error();
        exit(-555);
    }
}

Types do_AND(Types arg1, Types arg2) {
    if(arg1 == TP_INT && arg2 == TP_INT) {
        return TP_INT;
    }else if(arg1 == TP_BOOL && arg2 == TP_BOOL){
        return TP_BOOL;
    }else{
        error();
        exit(-555);
    }
}
























/*
 *
 * BEGIN SCANNER
 *
 *
 */





void gettoken() {
    char c;
    int i1;
    int i2;

    int value;
    float realvalue;
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
                case '.':
                    curtoken = TK_DOT;
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
                    curtoken = TK_COLON;
                    break;
            }
            *scanp--;
            break;
        case 'D':
            //scan ahead, and use whatever can be part of the number. Collect all digits and look for special cases like .
            //which would mean real. like letter 'e' which means real also, and perhaps something else like # to denote numbers in different bases.
            //collect number together, determine what constant you got, and return that constant.
            i1 = 0;
            value=0;
            base=10;
            while (c>='0'&&c<='9') {
                value=value*base+c-'0';
                c=*scanp++;
            }
            switch(c){
                case '.':
                    switch(catcode[c=*scanp++]){
                        case 'D':
                            //digit, so no syntax error
                            break;
                        default:
                            //next character is not a digit. SYNTAX ERROR
                            error();
                    }
                    i2 = 1;
                    realvalue = 0;
                    while (c>='0'&&c<='9') {
                        i1 = c - '0';
                        realvalue += i1*pow(10, -i2);
                        i2++;
                        c = *scanp++;
                    }
                    poolOfReals[realIndex] = value + realvalue;
                    curvalue = realIndex;
                    realIndex++;
                    curtoken = TK_REALLIT;
                    break;
                case 'e':
                case 'E':
                    //reallit
                    switch(catcode[c=*scanp++]){
                        case 'D':
                            //digit, so no syntax error
                            break;
                        default:
                            //next character is not a digit. SYNTAX ERROR
                            error();
                    }
                    //keep scanning numbers saving into i1. When we see something that's not a number we stop scanning, rollback scanner
                    //then multiply value by 10^i1 and then multiply that by curvalue and save it in curvalue
                    while (c>='0'&&c<='9') {
                        i1 = i1 * base + c - '0';
                        c = *scanp++;
                    }
                    poolOfReals[realIndex] = value * pow(10, i1);
                    curvalue = realIndex;
                    realIndex++;
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
    //source path
    char filepath[MAXFILEPATH] = "";
    //return value for syscalls
    int rv;

    if(pascal.length() > MAXFILEPATH){
        //filename too large
        exit(-5);
    }
    //initialize filepath from string
    strcpy(filepath, pascal.c_str());

    rv = access(filepath, F_OK);
    if(rv != 0){
        if(errno == ENOENT) printf("%s does not exist. \n", filepath);
        else if(errno == EACCES) printf("%s is inaccessible. \n", filepath);
        exit(1);
    }
    fd = open(filepath, O_RDONLY);
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
    curline = line;
    curcol = col;

    //initialize the keyword symbol table
    keywords = initSymTable();

}