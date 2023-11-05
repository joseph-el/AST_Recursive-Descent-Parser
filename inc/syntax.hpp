#ifndef  __SYNTAX_H__
# define __SYNTAX_H__

# include "rdb_main.hpp"

                /*  /     +      %     -     *     ^ */
#define BINARY_OPR (DIV | ADD | MOD | SUB | MUL | POW)

#define V_LPAR_LEFT (BEGIN | DIGIT | BINARY_OPR | RPAR) // ( left
#define V_LPAR_RIGHT (DIGIT | LPAR) // ( right

#define V_RPAR_LEFT (RPAR | DIGIT | FAC) //  RPAR left
#define V_RPAR_RIGHT (BINARY_OPR | LPAR | RPAR | FAC | DIGIT | END) // RPAR right

#define V_FAC_LEFT (RPAR | DIGIT) // ! left
#define V_FAC_RIGHT (BINARY_OPR | END | RPAR) // ! right

#define V_DIGIT_LEFT (BEGIN | BINARY_OPR | LPAR | RPAR) //  digit left
#define V_DIGIT_RIGHT (END | FAC | BINARY_OPR | LPAR | RPAR) // digit right

#define V_BINARY_LEFT (DIGIT | RPAR | FAC) // binary left
#define V_BINARY_RIGHT (LPAR | DIGIT) // binary right

#define UNEXPECTED "syntax error near unexpected token "

#endif