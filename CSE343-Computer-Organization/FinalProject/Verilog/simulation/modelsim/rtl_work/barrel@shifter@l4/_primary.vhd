library verilog;
use verilog.vl_types.all;
entity barrelShifterL4 is
    port(
        \in\            : in     vl_logic_vector(15 downto 0);
        \select\        : in     vl_logic;
        \out\           : out    vl_logic_vector(15 downto 0)
    );
end barrelShifterL4;
