transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/mux2x1.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/alu1Bit.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/alu1BitLsb.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/alu1BitMsb.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/alu2Bit.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/alu4Bit.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/alu16.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/fullAdder.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/halfAdder.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/mux4x1.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/mux8x1.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/barrelShifter.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/barrelShifterL1.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/barrelShifterL2.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/barrelShifterL3.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/barrelShifterL4.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/mirror.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/mux16Bit2x1.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/shifter.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/registerFile.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/dataMemory.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/mips16.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/insMemory.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/mainControl.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/aluControl.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/FinalProject/Verilog {D:/org/CSE343-Computer-Organization/FinalProject/Verilog/pc.v}

