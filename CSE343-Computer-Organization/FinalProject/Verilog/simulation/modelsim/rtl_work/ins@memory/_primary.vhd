library verilog;
use verilog.vl_types.all;
entity insMemory is
    port(
        clock           : in     vl_logic;
        pc              : in     vl_logic_vector(15 downto 0);
        instruction     : out    vl_logic_vector(31 downto 0)
    );
end insMemory;
