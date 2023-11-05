#ifndef __RDB_H__
#define __RDB_H__

extern "C" {
    # include <readline/history.h>
    # include <readline/readline.h>
    # include   <unistd.h>
}

#include  "manageHeap.hpp"
#include  "syntax.hpp"
#include  "tokenization.hpp"
#include  "ast.hpp"

#define rdb_main main

#define left_value    root->left->val
#define right_value   root->right->val
#define current_value root->val

/* Terminal Color */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[0m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

void print_ast(const string&, const ast*, bool);
void equationResult(tokenization*, ast*);
void eval(ast*);

template <typename StringType>
bool interpretCommand(const StringType& str) {
    if (str == "clear")
        return system("clear"), true;
    if (str == "exit")
        exit(EXIT_SUCCESS);
    if (str == "reset")
        return system("reset"), true;
    return false;
}

#endif