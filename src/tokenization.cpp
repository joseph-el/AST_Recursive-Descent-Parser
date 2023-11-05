# include "rdb_main.hpp"

const char* tokenType[TOKEN_SIZE] = {"END", "BEGIN",  "(", ")", "0", "WSPACE", "UNK", "/", "+", "%", "-", "*", "^", "!"};
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

/* expand WSPACE | () () == () * () | () 2 == () * 2 | 2() == 2 * () */
void tokenization::expander( void ) {
    for (Itr it = begin(); it != end(); it++) {
        if (it->second & WSPACE)
            erase(it);
    }
    for (Itr it = begin(); it != end(); it++) {
        switch (it->second)  {
            case RPAR:
                if ((it+1)!= end() && ( (it+1)->second & (DIGIT | LPAR) )) 
                    insert(it + 1, make_pair(-1, MUL));
                break;
            case DIGIT:
                if ((it+1) != end() && (it+1)->second  & LPAR ) 
                    insert(it + 1, make_pair(-1, MUL));
                break;
            default:
                break;
        }
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

# ifndef DEBUG
    # define DEBUG
/*   Print Toknes in deque  */
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

# endif

 