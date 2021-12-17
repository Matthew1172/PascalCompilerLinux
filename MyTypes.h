//
// Created by matthew on 12/17/21.
//

#ifndef PASCALCOMPILERLINUX_MYTYPES_H
#define PASCALCOMPILERLINUX_MYTYPES_H
enum Types : int
{
    TP_INT = 0,
    TP_CHAR = 1,
    TP_BOOL = 2,
    TP_ENUM = 3,
    TP_REAL = 4,
    TP_ARR = 5,
    TP_STR = 6,
    TP_PTR = 7,
    TP_REC = 8,
    TP_SET = 9,
    TP_PROC = 10,
    TP_FUNC = 11,
    TP_FILE = 12,
    TP_CLASS = 13
};
Types do_XOR(Types types, Types types1);
Types do_OR(Types types, Types types1);
Types do_SUB(Types types, Types types1);
Types do_ADD(Types types, Types types1);
Types do_MUL(Types types, Types types1);
Types do_DIV(Types types, Types types1);
Types do_AND(Types types, Types types1);

Types do_XOR(Types types, Types types1) {
    return TP_INT;
}

Types do_OR(Types types, Types types1) {
    return TP_INT;
}

Types do_SUB(Types types, Types types1) {
    return TP_INT;
}

Types do_ADD(Types types, Types types1) {
    return TP_INT;
}

Types do_MUL(Types types, Types types1) {
    return TP_INT;
}

Types do_DIV(Types types, Types types1) {
    return TP_INT;
}

Types do_AND(Types types, Types types1) {
    return TP_INT;
}

#endif //PASCALCOMPILERLINUX_MYTYPES_H
