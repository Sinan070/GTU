library verilog;
use verilog.vl_types.all;
entity alu32 is
    port(
        a               : in     vl_logic_vector(31 downto 0);
        b               : in     vl_logic_vector(31 downto 0);
        multiplier      : in     vl_logic_vector(31 downto 0);
        multiplicand    : in     vl_logic_vector(31 downto 0);
        alu_op          : in     vl_logic_vector(2 downto 0);
        c_out           : out    vl_logic;
        r               : out    vl_logic_vector(31 downto 0)
    );
end alu32;
