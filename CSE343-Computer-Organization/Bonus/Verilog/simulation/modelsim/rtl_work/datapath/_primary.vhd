library verilog;
use verilog.vl_types.all;
entity datapath is
    port(
        clock           : in     vl_logic;
        reset           : in     vl_logic;
        cypher          : in     vl_logic_vector(15 downto 0);
        nextInput       : in     vl_logic_vector(3 downto 0);
        wr_sum          : in     vl_logic;
        wr_index        : in     vl_logic;
        wr_read         : in     vl_logic;
        wr_found        : in     vl_logic;
        found           : out    vl_logic;
        success         : out    vl_logic;
        cypherInput     : out    vl_logic_vector(3 downto 0);
        sum             : out    vl_logic_vector(7 downto 0);
        temp            : out    vl_logic_vector(3 downto 0)
    );
end datapath;
