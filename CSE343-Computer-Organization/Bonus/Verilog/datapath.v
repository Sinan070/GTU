module datapath(input clock,reset,input [15:0]cypher,input [3:0] nextInput,input wr_sum,wr_index,wr_read,wr_found,
output found,success,output [3:0] cypherInput,output [7:0] sum,output [3:0] temp);

reg [2:0]reg_index;

wire [2:0] w_index;

reg [7:0] reg_sum;

wire [7:0] w_sum;

reg[3:0] nextCypherInput;


reg[3:0] reg_readReg;

reg reg_found;
wire w_found;
initial begin

	reg_sum = 8'b0;
	reg_index = 3'b0;
	reg_readReg = 4'b0;
end
assign temp = reg_readReg;
assign w_index = (reg_found == 1'b1) ? (reg_index + 3'd1): 3'd0;
assign w_sum  = reg_sum + {4'd0 ,reg_readReg};
assign sum = (reset == 1'b1) ? 8'd0 : reg_sum;
assign found = reg_found;


always@(posedge wr_read)begin
	reg_readReg <= nextInput;
end



always @(*)begin
	if(reg_index == 3'b0)begin
		nextCypherInput= cypher[3:0];
	end
	if(reg_index == 3'b001)begin
		nextCypherInput= cypher[7:4];
	end
	if(reg_index == 3'b010)begin
		nextCypherInput = cypher[11:8];
	end
	if(reg_index == 3'b011)begin
		nextCypherInput = cypher[15:12];
	end
end

assign w_found = (nextCypherInput == reg_readReg);

assign success = (reg_index == 3'b100);

assign cypherInput = nextCypherInput;
always@(posedge clock)begin
	if(wr_index) begin
		reg_index <= w_index;
	end
	if(wr_sum) begin
		reg_sum <= w_sum;
	end
	if(wr_found) begin
		reg_found <= w_found;
	end
	
end








endmodule
