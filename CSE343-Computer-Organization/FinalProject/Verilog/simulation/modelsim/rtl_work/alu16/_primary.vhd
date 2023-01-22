library verilog;
use verilog.vl_types.all;
entity alu16 is
    port(
        a               : in     vl_logic_vector(15 downto 0);
        b               : in     vl_logic_vector(15 downto 0);
        multiplier      : in     vl_logic_vector(15 downto 0);
        multiplicand    : in     vl_logic_vector(15 downto 0);
        alu_op          : in     vl_logic_vector(2 downto 0);
        r               : out    vl_logic_vector(15 downto 0);
        equal           : out    vl_logic
    );
end alu16;
