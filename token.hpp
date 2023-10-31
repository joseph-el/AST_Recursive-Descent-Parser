# pragma once
#include <iostream>
#include <iterator>
#include <deque>
#include <list>
#include <set>
using namespace std;

extern "C" {
    #include <unistd.h>
    #include <stdalign.h>
    #include <stdlib.h>
    #include <stdnoreturn.h>
    #include <stdio.h>
}

enum Token {
    LPAR = (1<<1),
    RPAR = (1<<2),
    WSPACE = (1<<3),
    UNKNOWN = (1<<4),
    Division = (1<<5),
    Addition = (1<<6),
    Subtraction = (1<<7),
    Multiplication = (1<<8),
    Exponentiation = (1<<9)
};

typedef int_fast16_t token_type;

token_type ScanToken(const char &);