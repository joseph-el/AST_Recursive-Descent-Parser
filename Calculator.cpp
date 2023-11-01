# include "Calculator.hpp"

int calculator(__unused int argc,__unused char *argv[] ) {
    string prompt;
    while (true) {
        int _eof;
        _gnl("equation :> ", prompt);
        if (_eof ^ -1 or false) // NOTE: check if parse return false
            continue;

        Mgr.clearHeap();
    }

}