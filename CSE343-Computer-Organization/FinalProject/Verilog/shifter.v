module shifter(input [15:0] in, input [3:0] shtA ,input left, output [15:0] out);

wire[15:0] outMirror;
wire[15:0] outMux;
wire[15:0] outBarrel;
wire[15:0] outMirror2;

mirror miror1(in, outMirror);

mux16Bit2x1 mux1(outMirror,in,left,outMux);

barrelShifter bshifter(outMux,shtA,outBarrel);

mirror mirror2(outBarrel,outMirror2);

mux16Bit2x1 mux2(outMirror2,outBarrel,left,out);




endmodule
