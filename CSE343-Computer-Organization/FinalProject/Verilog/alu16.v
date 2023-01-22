module alu16(input[15:0] a, b,multiplier,multiplicand,input [2:0] alu_op , output [15:0]r ,output equal);
wire wireSET;
wire wireV;
wire [4:0] local_carries;
reg[31:0] p;
wire c_out;




alu1BitLsb alu1(a[0],b[0],p[16],multiplicand[0],wireSET,alu_op,local_carries[0],r[0]);
alu4Bit alu2(a[4:1],b[4:1],p[20:17],multiplicand[4:1],alu_op,local_carries[0],local_carries[1],r[4:1]);
alu4Bit alu3(a[8:5],b[8:5],p[24:21],multiplicand[8:5],alu_op,local_carries[1],local_carries[2],r[8:5]);
alu4Bit alu4(a[12:9],b[12:9],p[28:25],multiplicand[12:9],alu_op,local_carries[2],local_carries[3],r[12:9]);
alu2Bit alu9(a[14:13],b[14:13],p[30:29],multiplicand[14:13],alu_op,local_carries[3],local_carries[4],r[14:13]);
alu1BitMsb alu10(a[15],b[15],p[31],multiplicand[15],1'b0,alu_op,local_carries[4],c_out,wireV,wireSET,r[15]);


assign equal = (r == 16'b0);



endmodule
