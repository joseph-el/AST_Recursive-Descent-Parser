# include "../inc/RDB.hpp"

int rdb_main(__unused int argc, __unused char *argv[] ) {
    tokenization* tokens;
    Parser*       parser;
    char*         prompt;  
    ast*          root;

    while (true) {
		prompt = readline(GREEN "equation> " WHITE);
        if (!prompt)
            break;
        gc_insert(prompt);
        stringstream ss(string(prompt));
        tokens = lexer(ss);
        if (!tokens || !tokens->syntax())
            goto done;
        parser = gc_insert(new Parser(tokens));
        if (!parser || !(root = parser->parser())) {
            tokens->error("", "");
            goto done;
        }
        print_ast("", root, false);
        equationResult(root);
        print_equationResult(tokens, root);
        done:
            clearHeap;
    }
    clearHeap;
    exit(EXIT_SUCCESS);
}