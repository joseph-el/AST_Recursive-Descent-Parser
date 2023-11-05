#ifndef __MAIN_H__
#define __MAIN_H__

#include  "manageHeap.hpp"
#include  "syntax.hpp"
#include  "tokenization.hpp"
#include  "ast.hpp"

# define _gnl(obj, input) cout << obj; getline(cin, input); if(cin.eof()) exit(1);

#define rdb_main main

#endif