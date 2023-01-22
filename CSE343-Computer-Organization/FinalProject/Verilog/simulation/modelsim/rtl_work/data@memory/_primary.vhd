library verilog;
use verilog.vl_types.all;
entity dataMemory is
    port(
        clock           : in     vl_logic;
        memWrite        : in     vl_logic;
        memRead         : in     vl_logic;
        adress          : in     vl_logic_vector(15 downto 0);
        writeData       : in     vl_logic_vector(15 downto 0);
        readData        : out    vl_logic_vector(15 downto 0)
    );
end dataMemory;
