module mux8x1(input a,b,c,d,e,f,g,h, input [2:0]select, output s);
wire[1:0] wires;
mux4x1 mux1(a,b,c,d,select[1:0],wires[0]);
mux4x1 mux2(e,f,g,h,select[1:0],wires[1]);
mux2x1 mux3(wires[0],wires[1],select[2],s);



endmodule
