library verilog;
use verilog.vl_types.all;
entity alu1BitMsb is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        p0              : in     vl_logic;
        mul0            : in     vl_logic;
        less            : in     vl_logic;
        alu_op          : in     vl_logic_vector(2 downto 0);
        c_in            : in     vl_logic;
        c_out           : out    vl_logic;
        v               : out    vl_logic;
        set             : out    vl_logic;
        r               : out    vl_logic
    );
end alu1BitMsb;
