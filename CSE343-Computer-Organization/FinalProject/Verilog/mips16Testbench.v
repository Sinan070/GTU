`timescale 1ns/1ps 

module mips16Testbench();

//reg [31:0]instruction;
reg clock;
reg reset;

reg [31:0] halt  = 32'hffff;

initial begin
	//reset = 1'b;
	//add ins
	//instruction = 32'b00100000100001000000000000011100;
	clock = 1'b0;
	
	$readmemb("..//../sample_inst_memory.txt", mips.instructionMemory.memory);
	$readmemh("..//../sample_data_memory.txt", mips.datamemory.memory);
	
	
	mips.instructionMemory.memory[120] = 8'b11111111;
	mips.instructionMemory.memory[121] = 8'b11111111;
	mips.instructionMemory.memory[122] = 8'b11111111;
	mips.instructionMemory.memory[123] = 8'b11111111;
	
	
end



always begin
	#10
	clock = ~ clock;
end

mips16 mips(clock);
//wire [31:0] testInst;
//assign testInst = mips.instructionMemory.tempInstruction;
reg [31:0] testInst;

always@(posedge clock)begin
	testInst  = mips.instructionMemory.tempInstruction;
	if(mips.wPc == halt)begin
	
		$writememb("..\\..\\registerMemoryAfter.txt", mips.registerfile.regFile);
		$writememb("..\\..\\dataMemoryAfter.txt", mips.datamemory.memory);
		$stop;
	end
	
	case(testInst[31:26])
	6'b0	:  begin
		if(testInst[9:4] == 6'b100000)begin
			$monitor("add %d %d %d\n", testInst[17:14],testInst[25:22],testInst[21:18]); 

		end
		else if(testInst[9:4] == 6'b100001)begin
			$monitor("sub %d %d %d\n", testInst[17:14],testInst[25:22],testInst[21:18]);
		end
		else if(testInst[9:4] == 6'b100101)begin
			$monitor("slt %d %d %d\n", testInst[17:14],testInst[25:22],testInst[21:18]);
		end
		else if(testInst[9:4] == 6'b100011)begin
			$monitor("and %d %d %d\n", testInst[17:14],testInst[25:22],testInst[21:18]);
		end
		else if(testInst[9:4] == 6'b110000)begin
			$monitor("or %d %d %d\n", testInst[17:14],testInst[25:22],testInst[21:18]);
		end
		
	end
	
	6'h8 : 	begin
		$monitor("addi %d %d %d\n", testInst[21:18],testInst[25:22],testInst[17:2]);   
	end
	
	6'h23 :	begin
		$monitor("lw %d (%d)%d\n", testInst[21:18],testInst[17:2],testInst[25:22]);
	
	end
	
	6'h2b	:	begin
		$monitor("sw %d (%d)%d\n", testInst[21:18],testInst[17:2],testInst[25:22]);
	end
	
	6'h4	:	begin
		$monitor("beg %d %d %d\n", testInst[21:18],testInst[25:22],testInst[17:2]);   
	end
	
	6'h5	:	begin
		$monitor("bne %d %d %d\n", testInst[21:18],testInst[25:22],testInst[17:2]);   
	end
	
	
	6'ha	:	begin
		$monitor("slti %d %d %d\n", testInst[21:18],testInst[25:22],testInst[17:2]);   
	end
	
	
	6'hc	:	begin
		$monitor("andi %d %d %d\n", testInst[21:18],testInst[25:22],testInst[17:2]);   
	end
	
	6'hd	:	begin
		$monitor("ori %d %d %d\n", testInst[21:18],testInst[25:22],testInst[17:2]);   
	end
	
	6'h6	:	begin
		$monitor("srl %d %d %d\n", testInst[17:14],testInst[21:18],testInst[17:14]);
	end
	
	6'h7	:	begin
		$monitor("sll %d %d %d\n", testInst[17:14],testInst[21:18],testInst[17:14]);  
	end
	
	6'hf	:	begin
		$monitor("li %d %d\n", testInst[21:18],testInst[17:2]);
	end
	
	6'h2	:	begin
		$monitor("j %d\n", testInst[25:10]);
	end
	
	6'h3	:	begin
		$monitor("jal %d\n", testInst[25:10]);
	end
	
	endcase
end




endmodule
