# include "rdb_main.hpp"

int rdb_main(__unused int argc, __unused char *argv[] ) {
    tokenization* tokens;
    Parser*       parser;
    char*         prompt;  
    ast*          root;

    while (true) {
		prompt = readline(BOLDCYAN "Equation ➤ " BOLDWHITE);
        if (!prompt)
            break;
        add_history(prompt), gc_insert(prompt);
        stringstream ss(prompt);
        if (interpretCommand(ss.str()) || !(tokens = lexer(ss)) || !tokens->syntax())
            goto done;
        parser = (Parser *)gc_insert(new Parser(tokens));
        if (!parser || !(root = parser->parser())) {
            tokens->error("parser: " UNEXPECTED);
            goto done;
        }
        try {
            print_ast("", root, false);
            eval(root);
            equationResult(tokens, root);
        } catch (int) {}
        done:
            clearHeap;
    }
    clearHeap;
    exit(EXIT_SUCCESS);
}
