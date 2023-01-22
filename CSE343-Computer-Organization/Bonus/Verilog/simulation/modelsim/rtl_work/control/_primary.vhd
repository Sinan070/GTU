library verilog;
use verilog.vl_types.all;
entity control is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        read            : in     vl_logic;
        found           : in     vl_logic;
        success         : in     vl_logic;
        state           : out    vl_logic_vector(2 downto 0);
        wr_sum          : out    vl_logic;
        wr_index        : out    vl_logic;
        wr_found        : out    vl_logic
    );
end control;
