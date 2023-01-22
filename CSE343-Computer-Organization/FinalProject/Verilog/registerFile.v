module registerFile(input clock,input [3:0]readReg1 , readReg2, writeRegister,input[15:0] writeData, input regWrite, output [15:0]readData1,readData2);


reg[15:0] regFile[15:0];


initial begin
	regFile[0] = 16'b0;
end
assign readData1 = regFile[readReg1];
assign readData2 = regFile[readReg2];


always @(negedge clock )begin
  if(regWrite == 1'b1 && writeRegister != 4'b0)begin
	regFile[writeRegister] <= writeData;
  end
end

endmodule

	