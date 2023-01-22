library verilog;
use verilog.vl_types.all;
entity halfAdder is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        s               : out    vl_logic;
        c_out           : out    vl_logic
    );
end halfAdder;
