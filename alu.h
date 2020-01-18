#ifndef ALU_H
#define ALU_H

#include <systemc.h>

void make_alu();

SC_MODULE(alu) {
    sc_in<bool> clk;
    sc_in<bool> op_in;
    sc_in<sc_int<8>> a_in;
    sc_in<sc_int<8>> b_in;
    sc_out<sc_int<8>> result_out;

    void alu_method();

    SC_CTOR(alu) {
        SC_METHOD(alu_method);
        dont_initialize();
        sensitive << clk.pos();
    } 
};
#endif