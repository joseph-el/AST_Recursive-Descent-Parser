# include "rdb_main.hpp"

void print_ast(const string& prefix, const ast* root, bool isLeft)
{
    if(!root)
        return ;

    cout << GREEN << prefix;
    cout << (isLeft ? "├──" : "└──" );
    cout << WHITE;
    
    if (root->token & DIGIT)
        cout << " " <<  root->val << endl;
    else
        cout << " " <<  tokenType[(int)log2((int)root->token) - 1] << endl;
    
    print_ast( prefix + (isLeft ? "│   " : "    "), root->left,  true);
    print_ast( prefix + (isLeft ? "│   " : "    "), root->right, false);
    
}

void equationResult(tokenization* tokens, ast*root) {
    Itr it;

    cout << endl << "Equation :";
    for (it = tokens->begin(); it != tokens->end(); it++) {
        if (it->second & (BEGIN | END))
            continue;
        cout << " " << (it->second & DIGIT ? to_string(it->first) : tokenType[(int)log2(it->second) - 1]);
    }
    cout << endl << "Result   : " << root->val << endl << endl;
}