module halfAdder(input a,b , output s , output c_out);

and and1(c_out, a,b);
xor xor1(s,a,b);

endmodule
