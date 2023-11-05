#include <iostream>


extern "C" {
    # include <readline/history.h>
    # include <readline/readline.h>
    #include   <unistd.h>
}

using namespace std;


int main(){

while (1) {
    char *ret;

    ret = readline("HELIE: ");
    add_history(ret);
    if (string(ret) == "ex")
        exit(3);
}


}