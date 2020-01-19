#include "alu_main.h"


int sc_main(int argc, char* argv[]) {

    if (strcmp(argv[0], "./alu.x") == 0 && argc == 1) {
        //make_barrel();
        make_alu();
        //startALU();

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

    sc_signal<bool> en, left_right; // Declare Barrel Shifter Signals
	sc_signal<sc_uint<3>> shift; 
	sc_signal<sc_int<8>> data_in, data_out;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    alu alu("alu");
    barrel_shift barrel("barrelshift");

    barrel.shift_amt(shift); // Map Barrel Shifter Signals
   	barrel.clk(clk);
	barrel.enable(en);
	barrel.din(data_in);
    barrel.left_right(left_right);
	barrel.dout(data_out);

    alu.a_in(a); // Map ALU Signals
    alu.b_in(data_out);
    alu.op_in(op);
    alu.clk(clk);
    alu.result_out(result);

    tf = sc_create_vcd_trace_file("alu_main_trace"); // Map Trace Signals
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clk, "Clock");
    sc_trace(tf, en, "Enable");
	sc_trace(tf, data_in, "Data_In");
	sc_trace(tf, left_right, "Left_Right");
	sc_trace(tf, shift, "Shift_Amount");
	sc_trace(tf, data_out, "Data_Out");
    sc_trace(tf, a, "A");
    sc_trace(tf, data_out, "B");
    sc_trace(tf, op, "OP");
    sc_trace(tf, result, "Result");

    // Testing the ALU for Various Test Cases
    cout << "Beginning Test of the Arithmetic Logic Unit Implementation..." << endl;
    cout << endl;

    // Case 1: Subtraction with No Shifting
    cout << "Case 1: Subtraction with No Shifting" << endl;
    cout << "------------------------------------" << endl;
    en.write(0);
	shift.write(1);
	left_right.write(0);
	data_in.write(2);
    a.write(4);
    op.write(0);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 2: Addition with No Shifting
    cout << "Case 2:    Addition with No Shifting" << endl;
    cout << "------------------------------------" << endl;
    en.write(0);
	shift.write(1);
	left_right.write(0);
	data_in.write(10);
    a.write(2);
    op.write(1);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 3: Subtraction with Left Shifting
    cout << "Case 3:  Subtraction with Left Shift" << endl;
    cout << "------------------------------------" << endl;
    en.write(1);
    shift.write(2);
    left_right.write(0);
    data_in.write(2);
    a.write(10);
    op.write(0);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 4: Subtraction with Right Shift
    cout << "Case 4: Subtraction with Right Shift" << endl;
    cout << "------------------------------------" << endl;
    en.write(1);
    shift.write(1);
    left_right.write(1);
    data_in.write(2);
    a.write(10);
    op.write(0);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 5: Addition with Left Shift
    cout << "Case 5:     Addition with Left Shift" << endl;
    cout << "------------------------------------" << endl;
    en.write(1);
    shift.write(2);
    left_right.write(0);
    data_in.write(2);
    a.write(10);
    op.write(1);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 6: Addition with Right Shift
    cout << "Case 6:    Addition with Right Shift" << endl;
    cout << "------------------------------------" << endl;
    en.write(1);
    shift.write(2);
    left_right.write(1);
    data_in.write(16);
    a.write(10);
    op.write(1);
    sc_start(10, SC_NS);
    cout << endl;

    sc_close_vcd_trace_file(tf);
}
