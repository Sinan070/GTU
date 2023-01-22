module control(
input clk,reset,read,
input found , success,
output[2:0] state,
output reg wr_sum, wr_index,wr_found
);




reg[2:0] currentState, nextState;

localparam START = 3'b000, READ = 3'b001 , CHECK = 3'b010 , UPDATE = 3'b011, END = 3'b100;

assign state = currentState;



always @(posedge clk) begin
	if(reset == 1'b1)begin
		currentState <= START;
	end
	else begin
		currentState <= nextState;
	end
end
wire out;


always @ (*)begin
	case (currentState)
		START :	begin
				nextState <= READ;
		end
		READ :	begin
			if(read == 1'b1)begin
				nextState <= CHECK;
			end
			if(read == 1'b0) begin
				nextState <= READ;
			end
		end
		CHECK :	begin
			if(found == 1'b1)begin
				nextState <= UPDATE;
			end
			else begin
				nextState <= START;
			end
			
		
		end
		
		UPDATE :	begin
			if(success == 1'b1)begin
				nextState <= END;
			end
			else begin
				nextState <= READ;
			end
		end
		END :	begin
			if(reset == 1'b1)begin
				nextState <= START;
			end
			else begin
				nextState <= END;
			end
		end
	endcase

end
		

always @ (*)begin
	
	case (currentState)
		START :	begin
			wr_index <= 1'b0;
			wr_sum <= 1'b0;
		end
		READ :	begin
			wr_index <= 1'b0;
			wr_sum <= 1'b0;
			wr_found <=1'b1;
		end
		CHECK :	begin
			wr_sum <= 1'b1;
			wr_index <= 1'b1;
			wr_found <= 1'b0;
			
		end
		
		UPDATE :	begin
			wr_sum <= 1'b0;
			wr_index <= 1'b0;
			wr_found <= 1'b0;
		end
		END :	begin
			wr_sum <=1'b0;
			wr_index <= 1'b0;
		end
	endcase

end


endmodule
