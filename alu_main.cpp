#include "alu_main.h"


int sc_main(int argc, char* argv[]) {

    if (strcmp(argv[0], "./alu.x") == 0 && argc == 1) {
        //make_barrel();
        //make_alu();
        startALU();

    } else if (strcmp(argv[1], "-h") == 0) {
        cout << "Usage: ./alu.x" << endl;
        return 1;

    } else {
        cout << "For Help please enter: ./alu.x -h" << endl;
        return 1;

    }

    return 0;
}


void startALU() {
    sc_trace_file  *tf; // Declare Trace File Variable

    sc_signal<sc_int<8>> a, b, result; // Declare ALU Signals
    sc_signal<bool> op;

    sc_signal<bool> en, left_right;
	sc_signal<sc_uint<3>> shift; 
	sc_signal<sc_int<8>> data_in, data_out;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    alu alu("alu");
    barrel_shift barrel("barrelshift");

    barrel.shift_amt(shift);
   	barrel.clk(clk);
	barrel.enable(en);
	barrel.din(data_in);
    barrel.left_right(left_right);
	barrel.dout(data_out);

    alu.a_in(a); // Map ALU Signals
    alu.b_in(b);
    alu.op_in(op);
    alu.clk(clk);
    alu.result_out(result);

    tf = sc_create_vcd_trace_file("alu_main_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, en, "Enable");
	sc_trace(tf, data_in, "Data_In");
	sc_trace(tf, left_right, "Left_Right");
	sc_trace(tf, shift, "Shift_Amount");
	sc_trace(tf, data_out, "Data_Out");
    sc_trace(tf, a, "A");
    sc_trace(tf, b, "B");
    sc_trace(tf, op, "OP");
    sc_trace(tf, result, "Result");

    cout << "Beginning Test of the Arithmetic Logic Unit Implementation..." << endl;

    // Case 1: Subtraction with No Shifting
    cout << "Case 1: Subtraction with No Shifting" << endl;
    en.write(0);
	shift.write(1);
	left_right.write(0);
	data_in.write(2);
    sc_start(10, SC_NS);

    a.write(4);
    b.write(data_out);
    op.write(0);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 2: Addition with No Shifting
    cout << "Case 2: Addition with No Shifting" << endl;
    en.write(0);
	shift.write(1);
	left_right.write(0);
	data_in.write(10);
    sc_start(10, SC_NS);

    a.write(2);
    b.write(data_out);
    op.write(1);
    sc_start(10, SC_NS);
    cout << endl;
    

    sc_close_vcd_trace_file(tf);
}
