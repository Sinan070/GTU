module register(input[15:0]d,input clock, output [15:0])q);
always@(posedge clk)
	begin
		q<=d;
	end
endmodule
