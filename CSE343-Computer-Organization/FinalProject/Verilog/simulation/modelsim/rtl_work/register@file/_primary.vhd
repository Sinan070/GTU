library verilog;
use verilog.vl_types.all;
entity registerFile is
    port(
        clock           : in     vl_logic;
        readReg1        : in     vl_logic_vector(3 downto 0);
        readReg2        : in     vl_logic_vector(3 downto 0);
        writeRegister   : in     vl_logic_vector(3 downto 0);
        writeData       : in     vl_logic_vector(15 downto 0);
        regWrite        : in     vl_logic;
        readData1       : out    vl_logic_vector(15 downto 0);
        readData2       : out    vl_logic_vector(15 downto 0)
    );
end registerFile;
