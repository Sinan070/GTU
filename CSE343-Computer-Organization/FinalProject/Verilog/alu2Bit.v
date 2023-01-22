module alu2Bit(input [1:0]a, b ,p,mul,input [2:0] alu_op ,input c_in,output c_out, output [1:0]r);


wire local_c_out;
alu1Bit alu1(a[0],b[0],p[0],mul[0],1'b0,alu_op,c_in,local_c_out,r[0]);
alu1Bit alu2(a[1],b[1],p[1],mul[1],1'b0,alu_op,local_c_out,c_out,r[1]);





endmodule