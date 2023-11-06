# include "rdb_main.hpp"

bool tokenization::unexpectedSyntax() {
    auto l_par = 0, r_par = 0;

    for (auto it = begin(); it != end(); it++) {
        l_par += (it->second == LPAR);
        r_par += (it->second == RPAR);
        if (it->second & UNKNOWN)
            return error(UNEXPECTED, (char)it->first), true;
    }
     
    if (l_par += r_par; (l_par % 2))
        return error("Unclosed parenthesis detected: ", (l_par - r_par) > r_par ? ')':'('), true;
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
                error(UNEXPECTED "left of " , '('), sys = true;
            else if (right != -1 && right &~ V_LPAR_RIGHT)
                error(UNEXPECTED "right of", '('), sys = true;
            break;
    
        case RPAR:
            if (left != -1 && left &~ V_RPAR_LEFT)
                error(UNEXPECTED "left of " , ')'), sys = true;
            else if (right != -1 && right &~ V_RPAR_RIGHT)
                error(UNEXPECTED "right of ", ')'), sys = true;
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
        if (!_syntax || (it->second & BEGIN && FindToken(it + 1, false) & END))
            return false;
    }
    expander();
    return true;
}
