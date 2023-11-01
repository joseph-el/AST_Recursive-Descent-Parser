#include "token.hpp"

Token tokenization::getToken(const char &target) {

    switch (target) {
        case '(':
            return LPAR;
        case ')':
            return RPAR;
        case '^':
            return Exponentiation;
        case '-':
            return Subtraction;
        case '+':
            return Addition;
        case '%':
            return Modulation;
        case '/':
            return Division;
        case '*':
            return Multiplication;
        case '!':
            return Factorial;
    }
    return isspace(target) ? WSPACE : (isdigit(target) ? DIGIT : UNKNOWN);
}

int tokenization::consumeNumbers(stringstream &prompt, Token ret) {
    int sign = 0;
    char _c  = 0;
    string digits = "";

    getBack(prompt);
    while (!prompt.eof() and ret & DIGIT) {
        prompt.get(_c);
        ret = getToken(_c);
        if (ret & DIGIT && !prompt.eof())
            digits += _c;
    }
    int number = atoi(digits.c_str());
    if (ret & ~DIGIT)
        getBack(prompt);
    ret = (size() > 0) ? back().second : UNKNOWN;        
    sign = (ret == Subtraction) ? -1 : 1;
    return number * sign;
}

void tokenization::consumeWspace(stringstream& prompt, Token ret) {
    char _c = 0;
    push_back(make_pair(-1, WSPACE));
    while (!prompt.eof() and ret & WSPACE) {
        prompt.get(_c);
        ret = getToken(_c);
    }
    if (ret & ~(WSPACE))
        getBack(prompt);
}

tokenization* lexer(stringstream& prompt) {

    tokenization* token;
    char          _c = 0;
    int           _number = 0;
    token = (tokenization*)Mgr.insertAddress(new tokenization());
    if (!token)
        return nullptr;
    while (!prompt.eof()) {
        prompt.get(_c);
        Token ret = TOK.getToken(_c);
        if (ret & WSPACE) 
            TOK.consumeWspace(prompt);
        else if (ret & ~(DIGIT | WSPACE | UNKNOWN))
            TOK.push_back(make_pair(-1, ret));
        else if (ret & DIGIT) {
            _number = TOK.consumeNumbers(prompt);
            TOK.push_back(make_pair(_number, DIGIT));
        } else if (ret & UNKNOWN) {
            TOK.push_back(make_pair(_c, UNKNOWN));
            return token;
        }
    }
    return token;
}

void tokenization::getBack(stringstream& ss) {
    int pos = ss.tellg();
    ss.seekg(pos - 1);
}

void error(const char *msg, const char spc) {
    cerr << msg << endl;
    cerr << spc << endl;
}

int tokenization::FindToken(Itr curr, bool mode) {
   if (mode)
        goto leftnode;
    while (curr != end() && curr->second & WSPACE)
        curr++;
    return (curr != end() ? curr->second : -1);
    leftnode:
    while (curr != begin() && curr->second & WSPACE)
        curr --;
    return ( (curr == begin() && curr->second == WSPACE) ? -1 :  curr->second);
}


#define V_LPAR_LEFT  ( DIGIT | Addition | Factorial | Subtraction | Multiplication | Exponentiation | BEGIN)
#define V_LPAR_RIGHT (LPAR | DIGIT | Factorial | Subtraction | Addition)

#define V_RPAR_LEFT  (RPAR | DIGIT)
#define V_RPAR_RIGHT (END | LPAR)


bool tokenization::parenthesesSyntax(Itr &curr, bool mode) {
    int left, right;
    int l_par, r_par;

    l_par = r_par = 0;
    if (mode) {
        for (auto it = begin(); it != end(); it++)
            l_par += (it->second == LPAR),
            r_par += (it->second == RPAR);
        l_par += r_par;
        if (!(l_par % 2))
            return error(UNEXPECTED, '('), false;
        return true;
    }
    if (curr->second & ~(RPAR | LPAR))
        return true;
    left = FindToken(curr - 1, true);
    right = FindToken(curr + 1, false);
    
    if ((curr->second & LPAR) && (left & ~(V_LPAR_LEFT) || right & ~(V_LPAR_RIGHT)))
        return error(UNEXPECTED, '('), false;

    if ((curr->second & RPAR) && (left & ~(V_RPAR_LEFT) || right & ~(V_RPAR_RIGHT)))
        return error(UNEXPECTED, '('), false;
    return true;
}

bool tokenization::unarySyntax(Itr &curr) {

    Token left, right;




    return true;

}

bool tokenization::unknownSyntax() {
    for (auto it = begin();it != end(); it++) {
        if (it->second & UNKNOWN) {
            error(UNEXPECTED, (char)it->first);
            return true;
        }
    }
    return false;
}

bool tokenization::syntax( void ) {
    Token left, right;
    if (unknownSyntax())
        return false;
    for (auto it = begin();it != end(); it++) {
        if (it->second & UNKNOWN) {
            error(UNEXPECTED, (char)it->first);
            return false;
        }
        if (!unarySyntax(it) or !parenthesesSyntax(it, false))
            return false;
    }
    return true;
}



void tokenization::printTokens(void) {
    for (auto it = begin(); it != end(); it++) {
        int ret = it->second;
        switch(ret) {
            case WSPACE:
                cout << " [SP] ";
                break;
            case LPAR:
                cout << "( ";
                break;

            case RPAR:
                cout << " )";
                break;

            case Division:
                cout << " / ";
                break;

            case Addition:
                cout << " + ";
                break;

            case Factorial:
                cout << " ! ";
                break;

            case Modulation:
                cout << " % ";
                break;

            case Subtraction:
                cout << " - ";
                break;

            case Multiplication:
                cout << " * ";
                break;

            case Exponentiation:
                cout << " ^ ";
                break;

            case DIGIT:
                cout << " " << it->first<< " ";
                break;

            case UNKNOWN:
                cout << UNEXPECTED << "\'" << (char)it->first << "\'";
                goto end;
                break;
        }
    }
    end: 
    cout << endl;
}