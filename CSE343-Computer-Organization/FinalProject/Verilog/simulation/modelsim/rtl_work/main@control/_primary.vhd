library verilog;
use verilog.vl_types.all;
entity mainControl is
    port(
        opcode          : in     vl_logic_vector(5 downto 0);
        regDst          : out    vl_logic;
        branch          : out    vl_logic;
        memRead         : out    vl_logic;
        memtoReg        : out    vl_logic;
        memWrite        : out    vl_logic;
        aluSrc          : out    vl_logic;
        regWrite        : out    vl_logic;
        bneSignal       : out    vl_logic;
        shift           : out    vl_logic;
        \sll\           : out    vl_logic;
        j               : out    vl_logic;
        jal             : out    vl_logic;
        aluOp           : out    vl_logic_vector(2 downto 0)
    );
end mainControl;
