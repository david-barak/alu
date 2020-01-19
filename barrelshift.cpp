#include "barrelshift.h"

void barrel_shift :: barrel_method(){
	sc_int<8> data = din.read();
	int i;
	cout << "Data In: " << data.to_string() << endl;

	if(enable.read() == 1){
		sc_uint<3> shift = shift_amt.read();

		switch (left_right.read()) {
			// Left Shift
			case 0:	
				cout << "Arithmetic Shift Left by " << shift << " bits" << endl;
				for (int shifts = shift_amt.read(); shifts > 0; shifts--) {
					for (int i = 7; i > 0; i--) {
						data[i] = data[i-1];
					}
				}

				data[0] = 0;
				break;

			// Right Shift
			case 1:
				cout << "Arithmetic Shift Right by " << shift << " bits" << endl;
				for (int shifts = shift_amt.read(); shifts > 0; shifts--) {
					for (int i = 0; i < 7; i++) {
						data[i] = data[i+1];
					}	
				}

				break; 
		} 

	} else {
		cout << "Barrel Shifter Disabled." << endl;
		
	} 

	cout << "Data Out: " << data.to_string() << endl;
	dout.write(data);
	cout << endl;
}


void make_barrel(){
 	sc_trace_file *tf;                  // Create VCD file for tracing
	sc_signal<bool> en, left_right;
	sc_signal<sc_uint<3>> shift; 
	sc_signal<sc_int<8>> data_in, data_out;

	sc_clock clk("clk",10,SC_NS,0.5);   //Create a clock signal
	
 	barrel_shift barrel("barrelshift");            //Create testbench Device Under Test (DUT)

   	barrel.shift_amt(shift);
   	barrel.clk(clk);
	barrel.enable(en);
	barrel.din(data_in);
    barrel.left_right(left_right);
	barrel.dout(data_out);

    // Create wave file and trace the signals executing
	tf = sc_create_vcd_trace_file("barrel_trace");
    tf->set_time_unit(1, SC_NS);

	// Set Sensitivity List
	sc_trace(tf, en, "Enable");
	sc_trace(tf, data_in, "Data_In");
	sc_trace(tf, left_right, "Left_Right");
	sc_trace(tf, shift, "Shift_Amount");
	sc_trace(tf, data_out, "Data_Out");

	// Case 1: Disabled Barrel Shift
	en.write(0);
	shift.write(1);
	left_right.write(0);
	data_in.write(8);
	sc_start(10, SC_NS);
	cout << endl;

	// Case 2: Shift Left by 1
	en.write(1);
	shift.write(1);
	left_right.write(0);
	data_in.write(8);
	sc_start(10, SC_NS);
	cout << endl;

	// Case 3: Shift Right by 1
	en.write(1);
	shift.write(1);
	left_right.write(1);
	data_in.write(8);
	sc_start(10, SC_NS);
	cout << endl;

	// Case 4: Shift Right by 1 and Retain MSB for Signed Numbers
	en.write(1);
	shift.write(1);
	left_right.write(1);
	data_in.write(128);
	sc_start(10, SC_NS);
	cout << endl;

	// Case 5: Left Shift All Data Out
	en.write(1);
	shift.write(7);
	left_right.write(1);
	data_in.write(127);
	sc_start(10, SC_NS);
	cout << endl;

   	sc_close_vcd_trace_file(tf);
}
