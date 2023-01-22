module cypher_detector(
input [15:0]cypher,
input [3:0] nextInput, 
input clock, read , reset,
output [7:0] sum , 
output res,output [3:0] cypherInput,
output [2:0] states,output[3:0] inputReaded);

wire wr_sum,wr_index,wr_found;

wire success,found;
assign res = success;


assign t_found = found;
control ctrl(clock,reset,read,found,success,states,wr_sum,wr_index,wr_found);
datapath dtp(clock,reset,cypher,nextInput,wr_sum,wr_index,read,wr_found,found,success,cypherInput,sum,inputReaded);


endmodule
