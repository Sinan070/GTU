`timescale 1ns/1ps 
module alu32Testbench;

	reg [31:0] a,b;
	reg [2:0] alu_op;
	wire c_out;
	wire [31:0] s;
	alu32 test(a,b,a,b,alu_op,c_out,s);
	

	initial begin	
			
			a = 32'h00000014;
			b = 32'h00000013;
			
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
