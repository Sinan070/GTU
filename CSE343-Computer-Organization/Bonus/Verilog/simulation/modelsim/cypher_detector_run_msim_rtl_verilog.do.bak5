transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/Bonus {D:/org/CSE343-Computer-Organization/Bonus/control.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/Bonus {D:/org/CSE343-Computer-Organization/Bonus/datapath.v}
vlog -vlog01compat -work work +incdir+D:/org/CSE343-Computer-Organization/Bonus {D:/org/CSE343-Computer-Organization/Bonus/cypher_detector.v}

