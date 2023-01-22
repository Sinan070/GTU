library verilog;
use verilog.vl_types.all;
entity barrelShifter is
    port(
        \in\            : in     vl_logic_vector(15 downto 0);
        \select\        : in     vl_logic_vector(3 downto 0);
        \out\           : out    vl_logic_vector(15 downto 0)
    );
end barrelShifter;
