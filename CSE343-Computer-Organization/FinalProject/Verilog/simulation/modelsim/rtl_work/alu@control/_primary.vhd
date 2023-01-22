library verilog;
use verilog.vl_types.all;
entity aluControl is
    port(
        func            : in     vl_logic_vector(5 downto 0);
        aluOp           : in     vl_logic_vector(2 downto 0);
        aluCtr          : out    vl_logic_vector(2 downto 0)
    );
end aluControl;
