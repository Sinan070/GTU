library verilog;
use verilog.vl_types.all;
entity mux4x1 is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        c               : in     vl_logic;
        d               : in     vl_logic;
        \select\        : in     vl_logic_vector(1 downto 0);
        s               : out    vl_logic
    );
end mux4x1;
