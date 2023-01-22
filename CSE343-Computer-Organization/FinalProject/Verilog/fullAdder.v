module fullAdder(input a, b, input c_in, output s, output c_out);

wire[2:0] wires;
halfAdder ad1(a,b,wires[0],wires[1]);
halfAdder ad2(c_in, wires[0],s,wires[2]);
or or1(c_out,wires[1],wires[2]);


endmodule