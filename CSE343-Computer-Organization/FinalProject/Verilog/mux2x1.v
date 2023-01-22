module mux2x1(input a,b, select, output s);
wire[2:0] wires;

not not1(wires[0],select);
and and1(wires[1],a,wires[0]);
and and2(wires[2],b,select);
or or1(s,wires[1],wires[2]);




endmodule	