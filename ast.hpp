# pragma once

# include "token.hpp"


struct ast {
    Token       typp;

    struct ast* left;
    struct ast* right;
}