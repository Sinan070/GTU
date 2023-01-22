`timescale 1ns/1ps 
module mipsTest;

wire[31:0] pc;
reg clk,reset;
wire[15:0] result;


mips16 mips(clk,reset,result,pc);
initial begin  
     clk = 1'b0; 
	   reset = 1'b0; 
           forever #10 clk = ~clk;  
      end  
      


endmodule
