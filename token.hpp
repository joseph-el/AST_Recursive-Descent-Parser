# pragma once
#include <iostream>
extern "C" {
    #include <unistd.h>
    #include <stdalign.h>
    #include <stdlib.h>
    #include <stdnoreturn.h>
    #include <stdio.h>
}

enum Token {
    LPAR = (1 << 1),
    RPAR = (1 << 2),
    WSPACE = (1 << 8),
    Division = (1 << 3),
    Addition = (1 <<  4),
    Subtraction = (1 << 5),
    Multiplication = (1 << 6),
    Exponentiation = (1 << 7)
};

typedef int_fast16_t token_type;

token_type ScanToken(const char &);