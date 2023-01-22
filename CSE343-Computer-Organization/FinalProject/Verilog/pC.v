module pc(input clock, input[15:0] in, output[15:0] out);


reg [15:0] pCounter;
initial begin
	pCounter <= 16'b1111111111111100;
end
assign out = pCounter;
always@(posedge clock)begin
	pCounter <= in;
end



endmodule
