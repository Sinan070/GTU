`timescale 1ns/1ps 
module barrelShifterTest;

	reg [15:0] a;
	reg[3:0] select;
	wire [15:0] s;
	barrelShifter shifter(a,select,s);


	initial begin	
			
			
			a = 16'b0011001100110011;
			select = 4'b0011;
			#10;
			
			$stop;
			$finish;
	end



endmodule
