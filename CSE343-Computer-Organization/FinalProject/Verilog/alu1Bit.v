module alu1Bit(input a , b, p0, mul0, less, input [2:0] alu_op , input c_in , output c_out ,r);



wire wireOR;
wire wireAND;
wire wireADD;
wire wireSLT;
wire wireSUB;
wire wireMUL;


wire wireMulSelect;




wire in1,in2;

wire wireNOTALU0;
wire wireNOTALU1;
wire wireNOTALU2;

wire [3:0] wiresFlip;


not notAlu0(wireNOTALU0,alu_op[0]);
not notAlu1(wireNOTALU1,alu_op[1]);
not notAlu2(wireNOTALU2,alu_op[2]);

and andFlip1(wiresFlip[0],wireNOTALU2,wireNOTALU1,alu_op[0]);
and andFlip2(wiresFlip[1],alu_op[2],alu_op[1],wireNOTALU0);
or orFlip(wiresFlip[2],wiresFlip[0],wiresFlip[1]);

and andMulSelect(wireMulSelect, wireNOTALU2, alu_op[1], wireNOTALU0);

mux2x1 mux1(a,p0,wireMulSelect,in1);
mux2x1 mux2(b,mul0,wireMulSelect,in2);


xor xorFlip(wiresFlip[3],in2,wiresFlip[2]);


fullAdder fulladder1(in1,wiresFlip[3],c_in,wireADD,c_out);

and andOp(wireAND, wiresFlip[3],in1);
or orOp(wireOR, wiresFlip[3],in1);


and subOP(wireSUB,wiresFlip[0],wireADD);

//and mulOP(wireMUL,a,notc,alu_op[1],notA);

mux8x1 mux(wireADD,wireSUB, wireMUL,1'b0,wireAND,wireOR,less ,1'b0, alu_op[2:0],r);




endmodule
