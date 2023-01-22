module mux4x1(input a ,b ,c ,d , input[1:0] select, output s );

wire[1:0] wires;
mux2x1 mux1(a, b,select[0],wires[0]);
mux2x1 mux2(c , d, select[0], wires[1]);
mux2x1 mux3(wires[0],wires[1],select[1],s);

endmodule