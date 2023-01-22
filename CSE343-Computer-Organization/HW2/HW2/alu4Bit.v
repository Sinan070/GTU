module alu4Bit(input [3:0]a, b ,p,mul,input [2:0] alu_op ,input c_in,output c_out, output [3:0]r);
wire local_carry;
alu2Bit alu1(a[1:0],b[1:0],p[1:0],mul[1:0],alu_op,c_in,local_carry,r[1:0]);
alu2Bit alu2(a[3:2],b[3:2],p[3:2],mul[3:2],alu_op,local_carry,c_out,r[3:2]);

endmodule
