# include "rdb_main.hpp"

#define left_value  root->left->val
#define right_value root->right->val
#define current_value root->val

double _plus(double X, double Y) {
    return X + Y;
}

double _minus(double X, double Y) {
    return X - Y;
}

double _multiply(double X, double Y) {
    return X * Y;
}

double _divide(double X, double Y) {
    if (!Y) {
        cerr << "parser: " << "Division by zero is not allowed\n";
        throw -1;
    }
    return X / Y;
}

double _modulus(double X, double Y) {
    return (int)X % (int)Y;
}

double _exponentiation(double X, double Y) {
    return pow(X, Y);
}

double _factorial(double X) {
    if( X > 1)
        return X * _factorial(X - 1);
    return 1;
}

void eval(ast* root) {
    if (!root)
        return ;
    eval(root->right);
    eval(root->left);

    switch (root->token) {
        case ADD:
            current_value = _plus(left_value, right_value); break;
        case SUB:
            current_value = _minus(left_value, right_value); break;
        
        case MOD:
            current_value = _modulus(left_value, right_value); break;
        case DIV:
            current_value = _divide(left_value, right_value); break;
        case MUL:
            current_value = _multiply(left_value, right_value); break;

        case POW:
            current_value = _exponentiation(left_value, right_value); break;
        
        case FAC:
            current_value = _factorial(left_value); break;
        default: break;
    }

}