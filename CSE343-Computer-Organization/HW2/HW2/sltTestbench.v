
`timescale 1ns/1ps 
module sltTestbench;


	reg [31:0] a,b;
	reg [2:0] alu_op;
	wire c_out;
	wire [31:0] s;
	alu32 test(a,b,a,b,alu_op,c_out,s);
	

	initial begin	
			alu_op = 3'b110;
			
			a = 32'h00000014;
			b = 32'h00000013;
			
			#10;
			
			a = 32'h00000a40;
			b = 32'h00000f13;
			#10;
			
		
			
			a = 32'hf0000c14;
			b = 32'h00000d13;

			#10;
			
		
			$stop;
			$finish;
	end

endmodule