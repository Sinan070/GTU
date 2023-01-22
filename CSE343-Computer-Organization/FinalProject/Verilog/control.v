module control(input reset,input [5:0] opcode, output reg [1:0]aluOp, 
output reg regDst,
branch,
memRead,
memWrite,
aluSrc,
regWrite
);


always @ (*)begin
	//r type
	if(opcode == 5'b0)begin
		
	end

end



endmodule
