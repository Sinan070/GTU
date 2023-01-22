module insMemory(input clock,input [15:0]pc, output reg [31:0] instruction);

reg[7:0] memory[4096:0];

wire [11:0]w_pc = {2'b0,pc[9:0] };
reg [31:0] tempInstruction;
always@ (*) begin
	
	instruction[31:24] <= memory[w_pc] ; 
	instruction[23:16] <= memory[w_pc+ 12'b1] ;
	instruction[15:8] <= memory[w_pc+ 12'b10] ;
	instruction[7:0] <= memory[w_pc+ 12'b11] ;
	
end

always@(*)begin
	tempInstruction = instruction;
end







endmodule

