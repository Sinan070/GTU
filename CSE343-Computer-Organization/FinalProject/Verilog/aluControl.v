module aluControl(input [5:0] func, input [2:0] aluOp, output reg [2:0] aluCtr);



always@(*)begin
	case(aluOp)
	
	3'b0 :	begin
				aluCtr = 3'b0;
	end
	
	3'b001 :	begin
				aluCtr = 3'b001;
	end
	
	3'b010 : begin
				aluCtr = 3'b110;
	end
				
	3'b011 : begin
				aluCtr = 3'b100;
	end
	
	3'b100 :	begin
			case(func)
			
				6'b100000 :	begin
								aluCtr = 3'b0;
				end
				6'b100001 :	begin
								aluCtr = 3'b001;
				end
				6'b100101 :	begin
								aluCtr = 3'b110;
				end
				6'b100011 :	begin
								aluCtr = 3'b100;
				end
				6'b110000:	begin
								aluCtr = 3'b101;
				end
				6'h00:			begin
								aluCtr = 3'b111;
				end
				6'h02:			begin
								aluCtr = 3'b111;
				end

			
			endcase
	
	end
	
	3'b101 : begin
				aluCtr = 3'b101;
	end
	
	
	endcase
	
	
	
end







endmodule
