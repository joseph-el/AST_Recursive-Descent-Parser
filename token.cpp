#include "token.hpp"


Token tokenization::getToken(const char &target) {

    switch (target) {
        case '(':
            return LPAR;
        case ')':
            return RPAR;
        case '^':
            return Factorial;
        case ''





    }


    return isspace(target) ? WSPACE : UNKNOWN;
}



tokenization* lexter(stringstream& prompt) {

    tokenization* token;
    char          _c = 0;
    token = (tokenization*)Mgr.insertAddress(new tokenization());
    if (!token)
        return nullptr;
    while (!prompt.eof() and _c != 10) {
        prompt.get(_c);

    }



}