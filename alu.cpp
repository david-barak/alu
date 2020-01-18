#include "alu.h"

void alu :: alu_method() {
    sc_int<8> a, b;
    a = a_in.read();
    b = b_in.read();

    switch(op.read()) {
        case 0: result.write(a-b);
                break;
        case 1: result.write(a+b);
                break;
    }
}