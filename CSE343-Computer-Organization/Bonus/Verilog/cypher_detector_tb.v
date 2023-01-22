`timescale 1ns/1ps 
module cypher_detector_tb;

	reg[15:0] cypher ;
	
	reg[31:0] test;
	
	reg[3:0] nextInput;

	reg clock = 1'b0, reset,read;
	
	wire[3:0] cypherInput;
	wire [2:0] states;
	wire [7:0] sum;
	wire result;
	wire [3:0] inputReaded;
	always begin
	#1
		clock = ~clock;
		
	end
	
	cypher_detector cp(cypher,nextInput,clock,read,reset,sum,result,cypherInput,states,inputReaded);
	
	initial begin
		cypher  = 16'b0010011000000001;
		test = 32'b00000001001100000001000001100010;
					  
		reset = 1'b1;
		read =1'b0;
		#6
		reset = 1'b0;
		
		nextInput = test[31:28];
		#1
		read = 1'b1;
 
		
		#6
		read = 1'b0;
		nextInput = test[27:24];
		
		#1
		read = 1'b1;
		
		#6
		read = 1'b0;
		nextInput = test[23:20];
		
		
		
		#1
		read = 1'b1;
		
		#6
		read = 1'b0;
		nextInput = test[19:16];
		
		
		
		#1
		read = 1'b1;
		
		#6
		read = 1'b0;
		nextInput = test[15:12];
		
		
		
		#1
		read = 1'b1;
		
		#6
		read = 1'b0;
		nextInput = test[11:8];
		
		
		#1
		read = 1'b1;
		
		#6
		read = 1'b0;
		nextInput = test[7:4];
		
		
		
		#1
		read = 1'b1;
		
		#6
		read = 1'b0;
		nextInput = test[3:0];
		
		#1
		read = 1'b1;
		
		
	end
		
	
	
	
//module cypher_detector(input [15:0]cypher, input [3:0] in, input clk, input read , output [7:0] sum , output res);


endmodule
