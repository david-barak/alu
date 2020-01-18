#include <systemc.h>
#include "barrelshift.h"
#include "alu.h"


int sc_main(int argc, char* argv[]) {

    if (strcmp(argv[0], "./alu.x") == 0 && argc == 1) {
        //make_alu();

    } else if (strcmp(argv[1], "-h") == 0) {
        cout << "Usage: ./alu.x" << endl;
        return 1;
    } else {
        cout << "For Help please enter: ./alu.x -h" << endl;
        return 1;
    }

    return 0;
}