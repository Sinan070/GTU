library verilog;
use verilog.vl_types.all;
entity fullAdder is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        c_in            : in     vl_logic;
        s               : out    vl_logic;
        c_out           : out    vl_logic
    );
end fullAdder;
