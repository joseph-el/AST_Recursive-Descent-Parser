#include "../inc/tokenization.hpp"

const char* token[TOKEN_SIZE] = {"END", "BEGIN",  "(", ")", "0", "WSPACE", "UNK", "/", "+", "%", "-", "*", "^", "!"};
 /* Lexer */
tokenization* lexer(stringstream& prompt) {

    tokenization* token;
    char          _c = 0;
    int           _number = 0;
    token = (tokenization*)Mgr.insertAddress(new tokenization());
    if (!token)
        return nullptr;

    while (prompt.get(_c)) {

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
    TOK.push_back(make_pair(-1, END));
    return token;
}

void tokenization::expander( void ) {
    
    for (Itr it = begin(); it != end(); it++) {
        if (it->second & WSPACE) 
            erase(it);
    
        // else if (it->second & FAC) {
        //     if ((it-1)->second & RPAR) {
        //         (it-1)->second |= FAC;
        //         erase(it);
        //         continue;
        //     }
        //     Itr tmp = it;
        //     it--;
        //     int num = it->first;
        //     erase(it);
        //     tmp->first = num;
        //     it = tmp;
        // }
    }
}

Token tokenization::getToken(const char &target) {

    switch (target) {
        case '(':
            return LPAR;
        case ')':
            return RPAR;
        case '^':
            return POW;
        case '-':
            return SUB;
        case '+':
            return ADD;
        case '%':
            return MOD;
        case '/':
            return DIV;
        case '*':
            return MUL;
        case '!':
            return FAC;
    }
    return isspace(target) ? WSPACE : (isdigit(target) ? DIGIT : UNKNOWN);
}

int tokenization::consumeNumbers(stringstream &prompt, Token ret) {
    int sign = 0;
    char _c  = 0;
    string digits = "";

    getBack(prompt);
    while (ret & DIGIT && prompt.get(_c)) {
        ret = getToken(_c);
        if (ret & DIGIT && !prompt.eof())
            digits += _c;
    }
    int number = atoi(digits.c_str());
    if (ret & ~DIGIT)
        getBack(prompt);
    sign = (size() > 1) ? FindToken(end() - 2, true) : 0;
    ret  = (Token)( (size() > 1) ? back().second : UNKNOWN );
    if (ret & (SUB|ADD) && sign & (BINARY_OPR | LPAR | BEGIN))
        pop_back();      
    sign = (ret == SUB && sign & (BINARY_OPR | LPAR | BEGIN) ) ? -1 : 1;

    return number * sign;
}

void tokenization::consumeWspace(stringstream& prompt, Token ret) {
    char _c = 0;
    push_back(make_pair(-1, WSPACE));
    while (ret & WSPACE && prompt.get(_c))
        ret = getToken(_c);
    if (ret & ~(WSPACE))
        getBack(prompt);
}

void tokenization::getBack(stringstream& ss) {
    int pos = ss.tellg();
    ss.seekg(pos - 1);
}

void tokenization::error(const char *msg, const char spc) {
    cerr << msg;
    cerr << " " << spc;
    cerr << endl;
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


/*    *Math operator Syntax*    */

bool tokenization::unexpectedSyntax() {
    auto l_par = 0, r_par = 0;

    for (auto it = begin(); it != end(); it++) {
        l_par += (it->second == LPAR);
        r_par += (it->second == RPAR);
        if (it->second & UNKNOWN)
            return error(UNEXPECTED, (char)it->first), true;
    }
     
    if (l_par += r_par; (l_par % 2))
        return error("unclosed ", ')'), true;
    return !size() ? 1 : 0;
}

bool tokenization::parenthesesSyntax(Itr &current) {
    if (current->second & ~(RPAR | LPAR))
        return true;

    auto left = 0 , right = 0, sys = 0;

    right = FindToken(current + 1, false);
    left  = FindToken(current - 1, true);
    
    switch (current->second) {
        case LPAR:
            if (left != -1 && left &~ V_LPAR_LEFT)
                error(UNEXPECTED, '('), sys = true;
            else if (right != -1 && right &~ V_LPAR_RIGHT)
                error(UNEXPECTED, '('), sys = true;
            break;
    
        case RPAR:
            if (left != -1 && left &~ V_RPAR_LEFT)
                error(UNEXPECTED, ')'), sys = true;
            else if (right != -1 && right &~ V_RPAR_RIGHT)
                error(UNEXPECTED, ')'), sys = true;
            break;
        default:
            break;
    }
    // if (sys)
    //     cout << "syntax parenthese false \n";
    return !sys ? true : false;
}

bool tokenization::binarySyntax(Itr &curr) {
    if (curr->second &~ BINARY_OPR)
        return true;
    
    auto left = 0 , right = 0, sys = 0;

    right = FindToken(curr + 1, false);
    left  = FindToken(curr - 1, true);

    if (left != -1 && left &~ V_BINARY_LEFT)
            error(UNEXPECTED, GET_TOK), sys = true;
    else if (right != -1 && right &~ V_BINARY_RIGHT)
            error(UNEXPECTED, GET_TOK), sys = true;
    
    // if (sys)
    //     cout << "syntax binary false\n";

    return !sys ? true : false;
}

bool tokenization::unarySyntax(Itr &curr) {
    if (curr->second & ~(DIGIT | FAC))
        return true;
    
    auto left = 0 , right = 0, sys = 0;

    right = FindToken(curr + 1, false);
    left  = FindToken(curr - 1, true);
    
    // cout << "l: " << left << endl;
    // cout << "r: " << right << endl;
    // cout << "check right:" << token[(int)log2((int)right ) - 1] << endl;
    // cout << "check left:"  << token[(int)log2((int)left ) - 1] << endl;

    switch (curr->second) {
        case DIGIT:
            if (left != -1 && left &~ V_DIGIT_LEFT)
                error(UNEXPECTED, GET_TOK), sys = true;
            else if (right != -1 && right &~ V_DIGIT_RIGHT)
                error(UNEXPECTED, GET_TOK), sys = true;
            break;
        case FAC:
            if (left != -1 && left &~ V_FAC_LEFT)
                error(UNEXPECTED, GET_TOK), sys = true;
            else if (right != -1 && right &~ V_FAC_RIGHT)
                error(UNEXPECTED, GET_TOK), sys = true;
            break;
        default:
            break;
    }

    // if (sys)
    //     cout << "syntax unary false \n";
    return !sys ? true : false;  
}

bool tokenization::syntax() {
    if (unexpectedSyntax())
        return false;
    for (auto it = begin(); it != end(); it++) {
        bool _syntax = parenthesesSyntax(it) && \
                       unarySyntax(it) && \
                       binarySyntax(it) && \
                       binarySyntax(it);
        if (!_syntax)
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
            
            case (RPAR | FAC):
                cout << "(FAC)";
                break;

            case DIV:
                cout << " / ";
                break;

            case ADD:
                cout << " + ";
                break;

            case FAC:
                cout << " !(" << it->first << ")"; 
                break;

            case MOD:
                cout << " % ";
                break;

            case SUB:
                cout << " - ";
                break;

            case MUL:
                cout << " * ";
                break;

            case POW:
                cout << " ^ ";
                break;

            case DIGIT:
                cout << " " << it->first<< " ";
                break;

            case UNKNOWN:
                cout << UNEXPECTED << "\'" << (char)it->first << "\'";
                goto end;
                break;
            case BEGIN:
                cout << " [BEGIN] ";
                break;
            case END:
                cout << " [END] ";
        }
    }
    end: 
    cout << endl;
}



 