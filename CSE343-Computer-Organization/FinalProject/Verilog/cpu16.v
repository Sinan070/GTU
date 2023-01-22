module shifter(input [15:0] in , input [3:0] select , input left , output [15:0] out);

barrelShifter bs(in , select , out);



endmodule
