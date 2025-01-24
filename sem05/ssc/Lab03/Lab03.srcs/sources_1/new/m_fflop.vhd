library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity m_fflop is
port (clk: in std_logic;
        d: in std_logic;
        q: out std_logic);
end m_fflop;

architecture Behavioral of m_fflop is

begin
    process (clk) begin
        if rising_edge(clk) then
            q <= d;
        end if;
    end process;

end Behavioral;
