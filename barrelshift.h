// COE838 - Lab1 SystemC Intro
// BarrelFlop Unit Tutorial. 
//////////////////////////////////

#ifndef BARRELSHIFT_H   
#define BARRELSHIFT_H

#include <systemc.h>       
const int data_length = 8;

void make_barrel();
                                
SC_MODULE(barrel_shift) {
	sc_in<bool > clk;
	sc_in<bool> enable;
	sc_in<bool> left_right;
    sc_in<sc_uint<3>> shift_amt;
	sc_in<sc_int<8>> din;
    sc_out<sc_int<8>> dout;
 
	void barrel_method();   
 
    SC_CTOR(barrel_shift) {
        SC_METHOD(barrel_method);
		dont_initialize();
        sensitive << clk.pos(); //edge sensitive
		
    }

};
#endif 
