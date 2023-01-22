module mainControl(input [5:0] opcode, 
output reg regDst,
branch,
memRead,
memtoReg,
memWrite,
aluSrc,
regWrite,
bneSignal,
shift,
sll,
j,
jal,
output reg [2:0] aluOp
);



localparam RTYPE = 6'h0;

localparam ADDI = 6'h8, LW= 6'h23, SW= 6'h2b, BEQ= 6'h4 , 
			  BNE= 6'h5, SLTI = 6'ha, JUMP = 6'h2 , JAL = 6'h3 , 
			  ANDI = 6'hc , ORI = 6'hd, LI = 6'hf , SRL = 6'h6 ,SLL=6'h7 ;
			  
			  
always@(*)begin

	case(opcode)
	
		RTYPE : begin
					regDst = 1'b1;
					aluSrc = 1'b0;
					memtoReg = 1'b0;
					regWrite = 1'b1;
					memRead = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					bneSignal = 1'b0;
					shift = 1'b0;
					aluOp = 3'b100;
					j = 1'b0;
					jal = 1'b0;
		end
		ADDI: 	begin	
					regDst = 1'b0;
					aluSrc = 1'b1;
					memtoReg = 1'b0;
					regWrite = 1'b1;
					memRead = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					shift = 1'b0;
					aluOp = 3'b0;
					j = 1'b0;
					jal = 1'b0;
		end
		LW:	 	begin
					regDst = 1'b0;
					aluSrc = 1'b1;
					memtoReg = 1'b1;
					regWrite = 1'b1;
					memRead = 1'b1;
					memWrite = 1'b0;
					branch = 1'b0;
					shift = 1'b0;
					aluOp = 3'b0;
					j = 1'b0;
					jal = 1'b0;
		end
		
		SW :		begin
					
					aluSrc = 1'b1;
					regWrite = 1'b0;
					memRead = 1'b0;
					memWrite = 1'b1;
					branch = 1'b0;
					shift = 1'b0;
					aluOp = 3'b0;
					memtoReg = 1'b0;
					regDst = 1'b0;
					j = 1'b0;
					jal = 1'b0;
					
		end
		BEQ :		begin
					aluSrc = 1'b0;
					regWrite = 1'b0;
					memRead = 1'b0;
					memWrite = 1'b0;
					branch = 1'b1;
					shift = 1'b0;
					aluOp = 3'b001;
					bneSignal = 1'b0;
					jal = 1'b0;
					j = 1'b0;
		end
		BNE :		begin
					aluSrc = 1'b0;
					regWrite = 1'b0;
					memRead = 1'b0;
					memWrite = 1'b0;
					branch = 1'b1;
					bneSignal = 1'b1;
					shift = 1'b0;
					j = 1'b0;
					jal = 1'b0;
					aluOp = 3'b001;
		end
		
		SLTI:		begin
					regDst = 1'b0;
					aluSrc = 1'b1;
					branch = 1'b0;
					memRead = 1'b0;
					memtoReg = 1'b0;
					memWrite = 1'b0;
					regWrite = 1'b1;
					aluOp = 3'b010;
					shift = 1'b0;
					jal = 1'b0;
					j = 1'b0;
		end
		
		ANDI :	begin
					regDst = 1'b0;
					aluSrc = 1'b1;
					regWrite = 1'b1;
					memRead = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					aluOp = 3'b011;
					shift = 1'b0;
					jal = 1'b0;
					j = 1'b0;
					
		end
		
		ORI :		begin
					regDst = 1'b0;
					aluSrc = 1'b1;
					regWrite = 1'b1;
					memRead = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					aluOp = 3'b101;
					shift = 1'b0;
					jal = 1'b0;
					j = 1'b0;
		
		end
		LI :		begin
					regDst = 1'b0;
					memRead = 1'b0;
					memtoReg = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					regWrite = 1'b1;
					aluOp = 3'b111;
					shift = 1'b0;
					jal = 1'b0;
					j = 1'b0;
		end
		SRL :		begin
					regDst = 1'b1;
					memRead = 1'b0;
					memtoReg = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					regWrite = 1'b1;
					shift = 1'b1;
					sll = 1'b0;
					j = 1'b0;
					jal = 1'b0;
					aluOp = 3'b111;
		end
		SLL :		begin
					regDst = 1'b1;
					memRead = 1'b0;
					memtoReg = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					regWrite = 1'b1;
					shift = 1'b1;
					sll = 1'b1;
					j = 1'b0;
					jal = 1'b0;
					aluOp = 3'b111;
		end
		
		JUMP:		begin
					regDst = 1'b0;
					memRead = 1'b0;
					memtoReg = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					regWrite = 1'b0;
					shift = 1'b0;
					sll = 1'b0;
					aluOp = 3'b111;
					j = 1'b1;
					jal = 1'b0;
		end
		
		JAL:		begin
					regDst = 1'b0;
					memRead = 1'b0;
					memtoReg = 1'b0;
					memWrite = 1'b0;
					branch = 1'b0;
					regWrite = 1'b0;
					shift = 1'b0;
					sll = 1'b0;
					aluOp = 3'b111;
					j = 1'b1;
					jal = 1'b1;
		end
				
		
	endcase
end





endmodule




