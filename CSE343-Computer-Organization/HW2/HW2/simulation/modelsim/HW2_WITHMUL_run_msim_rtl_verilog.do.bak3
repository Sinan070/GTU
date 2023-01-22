transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/alu1Bit.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/alu1BitLsb.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/alu1BitMsb.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/halfAdder.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/fullAdder.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/mux2x1.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/mux4x1.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/mux8x1.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/alu2Bit.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/alu4Bit.v}
vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/alu32.v}

vlog -vlog01compat -work work +incdir+D:/HW2 {D:/HW2/alu32Testbench.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneiv_hssi_ver -L cycloneiv_pcie_hip_ver -L cycloneiv_ver -L rtl_work -L work -voptargs="+acc"  alu32Testbenchh

add wave *
view structure
view signals
run -all
