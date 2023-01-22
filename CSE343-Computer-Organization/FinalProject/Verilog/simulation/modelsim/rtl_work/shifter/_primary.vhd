library verilog;
use verilog.vl_types.all;
entity shifter is
    port(
        \in\            : in     vl_logic_vector(15 downto 0);
        shtA            : in     vl_logic_vector(3 downto 0);
        left            : in     vl_logic;
        \out\           : out    vl_logic_vector(15 downto 0)
    );
end shifter;
