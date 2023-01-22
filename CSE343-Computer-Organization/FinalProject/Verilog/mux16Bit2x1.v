module mux16Bit2x1(input[15:0] in1,in2, input select, output reg[15:0] out);


 always @* begin
    if (select) begin
      out <= in1;
    end else begin
      out <= in2;
    end
  end

endmodule



