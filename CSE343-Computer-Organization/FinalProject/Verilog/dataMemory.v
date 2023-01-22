module dataMemory(input clock,memWrite, memRead,input [15:0] adress , writeData, output reg[15:0] readData);

reg[7:0] memory[100:0];

always @(negedge clock)begin
	if(memWrite == 1'b1)begin
		memory[adress] <= writeData[15:8];
		memory[adress+ 16'b1] <= writeData[7:0];
	end
	
end




always@ (*) begin
	if(memRead == 1'b1)begin
		readData[7:0] <= memory[adress+16'b1] ; 
		readData[15:8] <= memory[adress] ;
	end
	else begin
		readData <= 16'b0;
	end
end



endmodule
