library verilog;
use verilog.vl_types.all;
entity alu1BitLsb is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        p0              : in     vl_logic;
        mul0            : in     vl_logic;
        less            : in     vl_logic;
        alu_op          : in     vl_logic_vector(2 downto 0);
        c_out           : out    vl_logic;
        r               : out    vl_logic
    );
end alu1BitLsb;
