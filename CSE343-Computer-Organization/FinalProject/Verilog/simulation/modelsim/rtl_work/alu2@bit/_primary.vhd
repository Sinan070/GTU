library verilog;
use verilog.vl_types.all;
entity alu2Bit is
    port(
        a               : in     vl_logic_vector(1 downto 0);
        b               : in     vl_logic_vector(1 downto 0);
        p               : in     vl_logic_vector(1 downto 0);
        mul             : in     vl_logic_vector(1 downto 0);
        alu_op          : in     vl_logic_vector(2 downto 0);
        c_in            : in     vl_logic;
        c_out           : out    vl_logic;
        r               : out    vl_logic_vector(1 downto 0)
    );
end alu2Bit;
