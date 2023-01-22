module barrelShifter(input [15:0] in, input [3:0] select , output[15:0] out);

wire[15:0] L1out,L2out,L3out,L4out;

barrelShifterL1 l1(in,select[0],L1out);
barrelShifterL2 l2(L1out,select[1],L2out);
barrelShifterL3 l3(L2out,select[2],L3out);
barrelShifterL4 l4(L3out,select[3],out);




endmodule
