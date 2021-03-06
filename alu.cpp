#include "alu.h"

void alu :: alu_method() {
    sc_int<8> a, b, result;
    a = a_in.read();
    cout << "First Number          = " << a.to_string() << endl;
    b = b_in.read();
    cout << "Second Number         = " << b.to_string() << endl;

    switch(op_in.read()) {
        case 0: result = a-b;
                cout << "Result of Subtraction = " << result.to_string() << endl;
                break;
        case 1: result = a+b;
                cout << "Result of Addition    = " << result.to_string() << endl;
                break;
    }

    cout << endl;
    result_out.write(result);
}

void make_alu() {
    sc_trace_file  *tf;
    sc_signal<sc_int<8>> a, b, result;
    sc_signal<bool> op;

    sc_clock clk("clk", 10, SC_NS, 0.5);

    alu alu("alu");

    alu.a_in(a);
    alu.b_in(b);
    alu.op_in(op);
    alu.clk(clk);
    alu.result_out(result);

    tf = sc_create_vcd_trace_file("alu_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, a, "A");
    sc_trace(tf, b, "B");
    sc_trace(tf, op, "OP");
    sc_trace(tf, result, "Result");

    cout << "Beginning Test of the Arithmetic Logic Unit Implementation..." << endl;

    // Case 1: Subtraction
    a.write(2);
    b.write(2);
    op.write(0);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 2: Addition
    a.write(5);
    b.write(5);
    op.write(1);
    sc_start(10, SC_NS);
    cout << endl;

    // Case 3: Subtraction Resulting in Negative Number
    a.write(5);
    b.write(10);
    op.write(0);
    sc_start(10, SC_NS);
    cout << endl;

}