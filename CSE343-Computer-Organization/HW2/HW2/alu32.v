module alu32(input[31:0] a, b,multiplier,multiplicand,input [2:0] alu_op ,output c_out, output [31:0]r);

wire wireSET;
wire wireV;
wire [8:0] local_carries;

reg[63:0] p;



alu1BitLsb alu1(a[0],b[0],p[32],multiplicand[0],wireSET,alu_op,local_carries[0],r[0]);
alu4Bit alu2(a[4:1],b[4:1],p[35:32],multiplicand[4:1],alu_op,local_carries[0],local_carries[1],r[4:1]);
alu4Bit alu3(a[8:5],b[8:5],p[39:36],multiplicand[8:5],alu_op,local_carries[1],local_carries[2],r[8:5]);
alu4Bit alu4(a[12:9],b[12:9],p[43:40],multiplicand[12:9],alu_op,local_carries[2],local_carries[3],r[12:9]);
alu4Bit alu5(a[16:13],b[16:13],p[47:44],multiplicand[16:13],alu_op,local_carries[3],local_carries[4],r[16:13]);
alu4Bit alu6(a[20:17],b[20:17],p[51:48],multiplicand[20:17],alu_op,local_carries[4],local_carries[5],r[20:17]);
alu4Bit alu7(a[24:21],b[24:21],p[55:52],multiplicand[24:21],alu_op,local_carries[5],local_carries[6],r[24:21]);
alu4Bit alu8(a[28:25],b[28:25],p[59:56],multiplicand[28:25],alu_op,local_carries[6],local_carries[7],r[28:25]);
alu2Bit alu9(a[30:29],b[30:29],p[63:60],multiplicand[30:29],alu_op,local_carries[7],local_carries[8],r[30:29]);
alu1BitMsb alu10(a[31],b[31],p[31],multiplicand[31],1'b0,alu_op,local_carries[8],c_out,wireV,wireSET,r[31]);



endmodule
