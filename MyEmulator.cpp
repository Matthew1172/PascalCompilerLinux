//
// Created by matthew on 12/18/21.
//

#include "MyEmulator.h"

void MyEmulator::readPcodeFile() {
    rv = access(fp, F_OK);
    if(rv != 0){
        if(errno == ENOENT) printf("%s does not exist. \n", fp);
        else if(errno == EACCES) printf("%s is inaccessible. \n", fp);
        exit(1);
    }
    fd = open(fp, O_RDONLY);
    if(fd == -1){
        printf("open() FROM EMULATOR failed with error [%s]\n", strerror(errno));
        exit(2);
    }
    //if(DEBUG) printf("open() successful! \n");
    struct stat stbuf{};
    stat(fp, &stbuf);
    MAXCODE = stbuf.st_size;
    //if(DEBUG) printf("Filesize is: %lu \n", filesize);
    CODE = static_cast<byte *>(calloc(MAXCODE, 1));
    read(fd, CODE, MAXCODE);
}

void MyEmulator::closePcodeFile() {

}

void MyEmulator::emulate() {
    IP = 0;
    flags = 0x00000000;
    while (1) {
        switch (opcode = CODE[IP++]) {
            case OP_HALT:
                exit(0);
            case OP_PUSH:
                int temp;
                temp=*(int *)(CODE+IP); IP+=sizeof(int); // address
                temp=*(int *)(DATA+temp);
                // value of the variable;
                *(int *)(STACK+SP)=temp; SP+=sizeof(int); // push
            default:
                //error
                break;
        }
        //dumpRegisters();
    }
}

MyEmulator::MyEmulator() {

}

MyEmulator::MyEmulator(string fp) {
    setFilepath(fp);
    readPcodeFile();
}

void MyEmulator::setFilepath(string fp) {
        if(fp.length() > 100){
            //filename too large
            exit(-5);
        }
        //initialize filepath from string
        strcpy(this->fp, fp.c_str());
        //check access
        //checkOutputFileAccess();
}
