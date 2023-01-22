`timescale 1ns/1ps 
module alu16Testbench;

	reg [15:0] a,b;
	reg [2:0] alu_op;
	wire c_out;
	wire [15:0] s;
	alu16 test(a,b,a,b,alu_op,s);
	

	initial begin	
			
			a = 16'h0014;
			b = 16'h0013;
			
			alu_op = 3'b000;
			#10;
			
			alu_op = 3'b001;
			#10;
			
			alu_op = 3'b010;
			#10;
			
			alu_op = 3'b011;
			#10;
			
			alu_op = 3'b100;
			#10;
			
			alu_op = 3'b101;
			#10;
			
			alu_op = 3'b110;
			#10;
			
			alu_op = 3'b111;
			#10;
			
		
			$stop;
			$finish;
	end

endmodule
