module mips16(input clock);



wire[31:0] instruction;


//controller wires


// control wires
wire regDst;
wire branch;
wire memRead;
wire memtoReg;
wire [2:0]aluOp;
wire memWrite;
wire aluSrc;
wire regWrite;
wire bne;
wire shift;
wire sll;
wire li;
wire j;
wire jal;
wire jr;

// register file wires

reg [3:0] writeRegister;
wire [15:0] writeDataRegFile;
wire [15:0]  readData1, readData2;
wire [15:0] wWriteData;

//alu wires
wire [15:0]readData2Alu;

wire [2:0] aluCtr;
wire [15:0] aluResult;
wire [15:0] wAluResult;
//alu branch wires

wire wEqual;
wire wBranch;

//data memory wires
wire [15:0]memReadData;

// pc counter wires and regs

reg [15:0]rPc_in;
wire [15:0]wPc;
reg [15:0]rPc_in1;

//shifter wires

wire [15:0]wShifter;


// jump wires

reg[15:0] wJump;
reg[15:0] wJalWriteData;
reg [3:0] wJalWriteRegister;
//wire [3:0] wjalWriteRegister;



always@(*)begin
	rPc_in1 <= wPc + 32'b100;
	if(branch == 1'b1 && wBranch== 1'b1)begin
		rPc_in <= rPc_in1 + instruction[17:2];
	end
	else begin
		rPc_in <= rPc_in1;
	end
end

pc programCounter(clock,wJump,wPc);

insMemory instructionMemory(clock,wPc,instruction);

mainControl maincontroller(instruction[31:26],regDst,branch,memRead,memtoReg,memWrite,aluSrc,regWrite,bne,shift,sll,j,jal,aluOp);


always@(*)begin
	if(regDst==1'b1)begin
		writeRegister <= instruction[17:14];
	end
	else begin
		writeRegister <= instruction[21:18];
	end
end


registerFile registerfile(clock,instruction[25:22],instruction[21:18],wJalWriteRegister,wJalWriteData,regWrite,readData1,readData2);

aluControl alucontrolller(instruction[9:4],aluOp,aluCtr);

assign readData2Alu = (aluSrc == 1'b1) ? instruction[17:2] : readData2; 

alu16 alu(readData1,readData2Alu,16'b0,16'b0,aluCtr,aluResult,wEqual);

shifter shtr(readData2, instruction[13:10],sll,wShifter);

mux16Bit2x1 muxShifter(wShifter,aluResult,shift,wAluResult);

dataMemory datamemory(clock,memWrite,memRead,wAluResult,readData2,memReadData);

assign writeDataRegFile = (memtoReg == 1'b1) ? memReadData : wAluResult;

mux16Bit2x1 muxLi(instruction[17:2],writeDataRegFile,li,wWriteData);
//mux16Bit2x1 muxLi(instruction[17:2],wJal,li,wWriteData);

not notEq(wnotEqual,wEqual);

mux2x1 muxBranch(wEqual,wnotEqual,bne,wBranch);


//assign wJal = (jal == 1'b1) ?  rPc_in : writeDataRegFile;

//assign wJalWriteRegister = (jal == 1'b1) ? 4'b1111 : writeRegister;

//assign wJump = (j == 1'b1) ? instruction[25:10] : rPc_in;


always@(*)begin
	wJump = rPc_in;
	if(j == 1'b1) begin
		wJump = instruction[25:10] ;
	end
end

always@(*)begin
		wJalWriteData = (jal == 1'b1) ? instruction[25:10] : wWriteData;
end

always@(*)begin
	wJalWriteRegister = (jal == 1'b1) ? 4'b1111 : writeRegister;
end



endmodule
