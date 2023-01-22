
module controller(input[2:0] s , input p0, go ,is_less ,output write, add, sr, output[2:0] n);
/*
assign n[0] = (~s[2]& ~s[1] & ~s[0] & go) | (~s[2] & ~s[1] & s[0] & ~p0) | (~s[2]& s[1] ~s[0]) | (s[2]& ~s[1] ~s[0] & is_less);
assign n[1] = (~s[2]& ~s[1] & s[0]) | (~s[2]& s[1] & ~s[0]);
assign n[2] = (~s[2]& s[1] & s[0]) ;


assign write = (~s[2]& ~s[1] & s[0]) | (s[2]& ~s[1] & ~s[0] & is_less);  
assign add = (~s[2]& ~s[1] & s[0] & ~p0);
assign sr = (~s[2]& ~s[1] & s[0] & p0) | (~s[2]& s[1] & ~s[0] & go);
*/


endmodule



