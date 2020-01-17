

#ifndef ALU_H
#define ALU_H

#include <systemc.h>

void make_alu();

SC_MODULE(alu) {
    sc_in<bool> clk;
    sc_in<bool> op;
    sc_in<sc_int<8>> a_in;
    sc_in<sc_int<8>> b_in;

    void alu_method();

    SC_CTOR(alu) {
        SC_METHOD(alu_method);
        dont_intialize();
        sensitive << clk.pos();
    } 
}
#endif