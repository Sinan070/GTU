module barrelShifterL3(input[15:0] in , input select, output [15:0] out);

mux2x1 m1(in[0],in[4],select,out[0]);
mux2x1 m2(in[1],in[5],select,out[1]);
mux2x1 m3(in[2],in[6],select,out[2]);
mux2x1 m4(in[3],in[7],select,out[3]);
mux2x1 m5(in[4],in[8],select,out[4]);
mux2x1 m6(in[5],in[9],select,out[5]);
mux2x1 m7(in[6],in[10],select,out[6]);
mux2x1 m8(in[7],in[11],select,out[7]);
mux2x1 m9(in[8],in[12],select,out[8]);
mux2x1 m10(in[9],in[13],select,out[9]);
mux2x1 m11(in[10],in[14],select,out[10]);
mux2x1 m12(in[11],in[15],select,out[11]);
mux2x1 m13(in[12],1'b0,select,out[12]);
mux2x1 m14(in[13],1'b0,select,out[13]);
mux2x1 m15(in[14],1'b0,select,out[14]);
mux2x1 m16(in[15],1'b0,select,out[15]);


endmodule
