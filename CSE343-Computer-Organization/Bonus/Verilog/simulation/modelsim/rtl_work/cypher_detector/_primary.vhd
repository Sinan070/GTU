library verilog;
use verilog.vl_types.all;
entity cypher_detector is
    port(
        cypher          : in     vl_logic_vector(15 downto 0);
        nextInput       : in     vl_logic_vector(3 downto 0);
        clock           : in     vl_logic;
        read            : in     vl_logic;
        reset           : in     vl_logic;
        sum             : out    vl_logic_vector(7 downto 0);
        res             : out    vl_logic;
        cypherInput     : out    vl_logic_vector(3 downto 0);
        states          : out    vl_logic_vector(2 downto 0);
        inputReaded     : out    vl_logic_vector(3 downto 0)
    );
end cypher_detector;
