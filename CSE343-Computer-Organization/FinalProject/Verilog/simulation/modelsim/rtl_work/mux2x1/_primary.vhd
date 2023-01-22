library verilog;
use verilog.vl_types.all;
entity mux2x1 is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        \select\        : in     vl_logic;
        s               : out    vl_logic
    );
end mux2x1;
