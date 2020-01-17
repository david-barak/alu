#include "alu.h"

void alu :: alu_method() {
    sc_int<8> a_in, b_in;

    if (enable.read() == 0) {
        cout <<" A Data = " data.to_string(SC_BIN)
    } else {
        cout << "Not Enabled" << endl;
    }
}